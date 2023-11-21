#pragma once
#include <unordered_map>
class SimpleGraph
{
public:
	SimpleGraph(std::vector<std::vector<size_t>>& graph);
	SimpleGraph();
	std::vector<size_t>& getAllNeighbours(size_t& node);
	std::vector<std::pair<size_t, size_t>>& getAllEdges();
	size_t& getEdge(size_t& node_from,size_t& node_to);
	size_t& getSizeOfGraph();
	size_t& getEdgeCount();
	void fullEdges();

private:
	std::vector<std::vector<size_t>> s_graph;
	size_t size_of_graph;
	size_t edge_count;
	std::vector<std::pair<size_t, size_t>> edges;
	std::unordered_map<size_t, std::unordered_map<size_t, size_t>> value_edges;
};