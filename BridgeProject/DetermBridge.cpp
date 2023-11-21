
#include <vector>
#include <algorithm>

#include "DetermBridge.hpp"

DetermBridge::DetermBridge(SimpleGraph& graph) {
	determ_graph = graph;
	time_point = 0;
}

void DetermBridge::recurDFS(size_t& current_node, size_t& parent) {
	visited[current_node] = true;
	time_in_node[current_node] = f_up[current_node] = time_point++;
	for (size_t& neighbour : determ_graph.getAllNeighbours(current_node)) {
		if (neighbour == parent) { continue; }
		if (visited[neighbour]) { f_up[current_node] = std::min(f_up[current_node], time_in_node[neighbour]); }
		else {
			recurDFS(neighbour, current_node);
			f_up[current_node] = std::min(f_up[current_node], f_up[neighbour]);
			if (f_up[neighbour] > time_in_node[current_node]) {
				std::pair<size_t, size_t> pair;
				current_node < neighbour ? pair = { current_node, neighbour } : pair = { neighbour, current_node };
				bridges.push_back(pair);
			}
		}
	}
}


std::vector<std::pair<size_t, size_t>>& DetermBridge::findBridgesWithDFS() {
	time_in_node.resize(determ_graph.getSizeOfGraph());
	f_up.resize(determ_graph.getSizeOfGraph());

	for (size_t node = 0; node < determ_graph.getSizeOfGraph(); ++node) {
		visited.push_back(false);
	}

	for (size_t node = 0; node < determ_graph.getSizeOfGraph(); ++node) {
		if (!visited[node]) {
			size_t no_parent = -1;
			recurDFS(node, no_parent);
		}
	}
	return bridges;
}
