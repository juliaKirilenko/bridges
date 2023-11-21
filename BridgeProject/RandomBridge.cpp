#include <iostream>
#include <vector>
#include <algorithm>
#include "RandomBridge.hpp"

RandomBridge::RandomBridge(SimpleGraph& graph) {
	random_graph = graph;
}

struct RandomBridge::Edge
{
	size_t node_from;
	size_t node_to;
	size_t value;
};


void RandomBridge::recurRandDFS(size_t& current_node, size_t& parent) {
	visited[current_node] = true;
	size_t sum_of_edges = 0;
	for (size_t& neighbour : random_graph.getAllNeighbours(current_node)) {
		if (neighbour == parent) { continue; }
		if (!visited[neighbour]) {
			recurRandDFS(neighbour, current_node);
		}
		current_node < neighbour ? sum_of_edges ^= random_graph.getEdge(current_node, neighbour) : sum_of_edges ^= random_graph.getEdge(neighbour, current_node);
	}
	parent < current_node ? random_graph.getEdge(parent, current_node) = sum_of_edges : random_graph.getEdge(current_node,parent) = sum_of_edges;
	if (sum_of_edges==0&&parent!=-1) {
		bridges.push_back({ parent, current_node });
	}
}


void RandomBridge::setWeights() {
	visited.resize(random_graph.getSizeOfGraph());
	for (size_t node = 0; node < random_graph.getSizeOfGraph(); ++node) {
		if (!visited[node]) {
			size_t no_parent = -1;
			recurRandDFS(node, no_parent);
		}
	}
}

std::vector<std::pair<size_t, size_t>>& RandomBridge::findOneBridgesWithRand() {
	setWeights();
	return bridges;
}

void RandomBridge::getOneStepRadixSort(std::vector<std::pair<size_t, size_t>>& edges, size_t& mask, size_t& to_begin) {
	std::vector<std::pair<size_t, size_t>> new_edges(edges.size());
	std::vector<size_t> count_massive((mask >> to_begin) + 1);
	for (std::pair<size_t, size_t>& edge : edges) {
		++count_massive[(random_graph.getEdge(edge.first,edge.second) & mask) >> to_begin];
	}
	
	for (size_t i = 1; i < count_massive.size(); ++i) {
		count_massive[i] += count_massive[i - 1];
	}

	for (size_t i = edges.size(); i > 0; --i) {
		size_t index_count_mas = (random_graph.getEdge(edges[i-1].first, edges[i-1].second) & mask) >> to_begin;
		--count_massive[index_count_mas];
		new_edges[count_massive[index_count_mas]] = edges[i-1];
	}
	edges = new_edges;
}

void RandomBridge::getSortEdgeWithRadixSort(std::vector<std::pair<size_t, size_t>>& not_sorted) {
	size_t low_mask = 0xff;
	size_t to_start = 0;
	size_t next_mask = 8;
	for (size_t i = 0; i < 32 / next_mask; ++i) {
		getOneStepRadixSort(not_sorted, low_mask, to_start);
		to_start += next_mask;
		low_mask <<= next_mask;
	}
}

void RandomBridge::CountingSortWithBucketSort(std::vector<std::pair<size_t, size_t>>& not_sorted, std::vector<std::pair<size_t, size_t>>& bed, size_t& ind_sorted, size_t& divider) {
	std::vector<size_t> count_massive(divider);

	for (std::pair<size_t, size_t>& edge : bed) {
		++count_massive[random_graph.getEdge(edge.first, edge.second) % divider];
	}

	for (size_t i = 1; i < count_massive.size(); ++i) {
		count_massive[i] += count_massive[i - 1];
	}

	for (size_t i = bed.size(); i > 0; --i) {
		size_t index_count_mas = random_graph.getEdge(bed[i-1].first, bed[i-1].second) % divider;
		not_sorted[--count_massive[index_count_mas] + ind_sorted] = bed[i-1];
	}
}

void RandomBridge::getSortEdgeWithBucketSort(std::vector<std::pair<size_t, size_t>>& not_sorted) {
	size_t max_value = 0;

	for (std::pair<size_t, size_t>& edge : not_sorted) {
		if (random_graph.getEdge(edge.first, edge.second) > max_value) {
			max_value = random_graph.getEdge(edge.first, edge.second);
		}
	}

	size_t number_of_buckets = 8;
	std::vector<std::vector<std::pair<size_t, size_t>>> buckets_edges(number_of_buckets);

	size_t divider = (max_value / number_of_buckets) + 1;
	for (std::pair<size_t, size_t>& edge : not_sorted) {
		buckets_edges[random_graph.getEdge(edge.first, edge.second) / divider].push_back(edge);
	}
	
	size_t ind_sorted = 0;
	for (std::vector<std::pair<size_t, size_t>>& bed : buckets_edges) {
		CountingSortWithBucketSort(not_sorted, bed, ind_sorted, divider);
		ind_sorted += bed.size();
	}
}


std::vector<std::pair<size_t, size_t>> RandomBridge::findTwoBridgesWithRand(size_t& type_of_sort) {
	//setWeights();

	std::vector< std::pair<size_t, size_t>> sorted_edges = random_graph.getAllEdges();
	std::vector< std::pair<size_t, size_t>> bridges_two;

	switch (type_of_sort) {
	case 1:
		getSortEdgeWithRadixSort(sorted_edges);
		break;
	case 2:
		getSortEdgeWithBucketSort(sorted_edges);
		break;
	default:
		std::sort(sorted_edges.begin(), sorted_edges.end(), [&](std::pair<size_t, size_t>& a, std::pair<size_t, size_t>& b) -> bool
			{
				return random_graph.getEdge(a.first, a.second) < random_graph.getEdge(b.first, b.second);
			});
		break;
	}
	
	std::pair<size_t, size_t>& previos_edge = sorted_edges[0];
	size_t index = 0;
	for (std::pair<size_t, size_t>& edge : sorted_edges) {
		if (index == 0) { index++; continue; }
		std::pair<size_t, size_t>& next_edge = edge;
		if ((random_graph.getEdge(previos_edge.first, previos_edge.second) == random_graph.getEdge(next_edge.first, next_edge.second))
			&&( random_graph.getEdge(previos_edge.first, previos_edge.second)!=0)) {
			bridges_two.push_back({ previos_edge.first, previos_edge.second });
			bridges_two.push_back({ next_edge.first, next_edge.second });
		}
		previos_edge = edge;
	}
	
	return bridges_two;
}
