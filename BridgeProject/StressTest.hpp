#pragma once

class StressTest {
private:
	std::vector<std::vector<size_t>> test_graph;
	float accuracy;
	std::vector<bool> visited;
	void dfs(size_t& current_node, size_t& parent);
	double compOfConnect();

public:
	StressTest(std::vector<std::vector<size_t>>& graph);
	float& getAccuracyFromStressTest(std::vector<std::vector< std::pair<size_t, size_t>>>& bridges);

};