#!/usr/bin/env python3
import argparse
import re

import pydot

PRIVATE = [
    'init_from_cstr',
    'assign_from_cstr',
    'ensure_capacity',
    'to_size',
    'check_index',
    'check_index_inclusive',
    'append_cstr',
    'insert_cstr',
    'replace_impl',
    'find_impl',
    'find_aho',
    'index_from_iterator',
]

ITERATOR_METHODS = (
    'begin',
    'end',
    'cbegin',
    'cend',
    'rbegin',
    'rend',
    'rcbegin',
    'rcend',
)

SKIP = (
    'std::',
    'operator new',
    'operator delete',
    '__clang',
    'llvm.',
    'basic_',
    'char_traits',
)

SKIP_NODE_SUFFIXES = (
    '::iterator::iterator',
    '::const_iterator::const_iterator',
    '::reverse_iterator::reverse_iterator',
    '::const_reverse_iterator::const_reverse_iterator',
    '::iterator',
    '::const',
    '::reverse',
)


def canonical(label: str) -> str:
    label = label.strip('"')
    for name in PRIVATE:
        if name in label:
            return name
    if 'AhoCorasickAutomaton' in label or 'AhoCorasick' in label:
        match = re.search(r'AhoCorasick(?:Automaton)?::?(\w+)', label.replace('__', '::'))
        return 'AhoCorasick::' + (match.group(1) if match else 'method')

    normalized = label.replace('__', '::')
    for suffix in SKIP_NODE_SUFFIXES:
        if normalized.endswith(suffix) or suffix + ':' in normalized:
            return ''

    for method in ITERATOR_METHODS:
        if re.search(rf'MyString::{method}::?', normalized):
            return f'MyString::{method}'

    match = re.search(r'MyString::([A-Za-z_]+)', normalized)
    if match:
        return 'MyString::' + match.group(1)
    return ''


def should_skip(label: str) -> bool:
    return any(token in label for token in SKIP)


def build_graph(input_dot: str, output_dot: str, output_png: str) -> None:
    graph = pydot.graph_from_dot_file(input_dot)[0]

    kept = {}
    for node in graph.get_nodes():
        raw = node.get_label()
        if not raw or raw in ('node', 'graph') or should_skip(raw):
            continue
        name = canonical(raw)
        if name:
            kept[node.get_name()] = name

    edges = set()
    for edge in graph.get_edges():
        source = edge.get_source()
        target = edge.get_destination()
        if source not in kept or target not in kept:
            continue
        src_name = kept[source]
        dst_name = kept[target]
        if src_name == dst_name:
            continue
        edges.add((src_name, dst_name))

    subgraph = pydot.Dot(
        graph_type='digraph',
        rankdir='LR',
        splines='true',
        overlap='false',
        concentrate='true',
        fontsize='8',
        nodesep='0.2',
        ranksep='0.5',
        dpi='96',
    )

    node_ids = {}
    for name in sorted({item for pair in edges for item in pair}):
        node_id = re.sub(r'[^A-Za-z0-9_]', '_', name)
        node_ids[name] = node_id
        subgraph.add_node(
            pydot.Node(
                node_id,
                label=name,
                shape='box',
                fontsize='8',
                style='rounded',
            )
        )

    for source, target in sorted(edges):
        subgraph.add_edge(pydot.Edge(node_ids[source], node_ids[target]))

    subgraph.write_dot(output_dot)
    subgraph.write_png(output_png)
    print(f'[+] nodes: {len(subgraph.get_nodes())}, edges: {len(edges)}')
    print(f'[+] saved: {output_dot}')
    print(f'[+] saved: {output_png}')


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--input', required=True)
    parser.add_argument('-d', '--dot', required=True)
    parser.add_argument('-p', '--png', required=True)
    args = parser.parse_args()
    build_graph(args.input, args.dot, args.png)


if __name__ == '__main__':
    main()
