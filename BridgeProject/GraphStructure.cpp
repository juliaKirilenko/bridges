#include <iostream>
#include <vector>
#include <unordered_map>
#include "GraphStructure.hpp"


SimpleGraph::SimpleGraph(std::vector<std::vector<size_t>>& graph) {
	s_graph = graph;
	size_of_graph = s_graph.size();
	edge_count = 0;
	fullEdges();
}

SimpleGraph::SimpleGraph() {
}

std::vector<size_t>& SimpleGraph::getAllNeighbours(size_t& node) {
	return s_graph[node];
}

void SimpleGraph::fullEdges() {
	size_t node_from = 0;
	for (auto &nodes : s_graph) {
		for (auto& node_to : nodes) {
			if (node_from < node_to) {
				edges.push_back({ node_from, node_to });
				value_edges[node_from][node_to] = std::rand();
				edge_count++;
			}
		}
		node_from++;
	}
}

std::vector<std::pair<size_t, size_t>>& SimpleGraph::getAllEdges() {
	return edges;
}

size_t& SimpleGraph::getEdge(size_t& node_from,size_t& node_to) {
	return value_edges[node_from][node_to];
}

size_t& SimpleGraph::getEdgeCount() {
	return edge_count;
}

size_t& SimpleGraph::getSizeOfGraph() {
	return size_of_graph;
}




