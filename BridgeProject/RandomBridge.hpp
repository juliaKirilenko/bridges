#pragma once

#include "GraphStructure.hpp"

class RandomBridge {
private:
	SimpleGraph random_graph;
	std::vector<bool> visited;
	std::vector< std::pair<size_t, size_t>> bridges;
	struct Edge;
	void recurRandDFS(size_t& current_node, size_t& parent);
	void setWeights();
	void getSortEdgeWithRadixSort(std::vector<std::pair<size_t, size_t>>& not_sorted);
	void CountingSortWithBucketSort(std::vector<std::pair<size_t, size_t>>& not_sorted, std::vector<std::pair<size_t, size_t>>& bed, size_t& multiple, size_t& divider);
	void getSortEdgeWithBucketSort(std::vector<std::pair<size_t, size_t>>& not_sorted);
	void getOneStepRadixSort(std::vector<std::pair<size_t, size_t>>& edges, size_t& mask, size_t& to_begin);

public:
	RandomBridge(SimpleGraph& graph);

	std::vector<std::pair<size_t, size_t>>& findOneBridgesWithRand();
	std::vector<std::pair<size_t, size_t>> findTwoBridgesWithRand(size_t& type_of_sort);
};


