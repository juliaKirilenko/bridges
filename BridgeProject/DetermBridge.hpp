
#include "GraphStructure.hpp"

class DetermBridge {
private:
	SimpleGraph determ_graph;
	int time_point;
	std::vector<size_t> time_in_node;
	std::vector<size_t> f_up;
	std::vector< std::pair<size_t, size_t>> bridges;
	std::vector<bool> visited;
	void recurDFS(size_t& current_node,size_t& parent);

public:
	DetermBridge(SimpleGraph& graph);
	std::vector<std::pair<size_t, size_t>>& findBridgesWithDFS();

};