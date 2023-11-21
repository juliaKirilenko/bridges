
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime> 
#include <fstream>
#include <string>
#include <sstream>
#include "GraphStructure.hpp"
#include "DetermBridge.hpp"
#include "RandomBridge.hpp"
#include "StressTest.hpp"

std::vector<std::vector<size_t>> generateGraph(size_t nodes, double edges, bool sparse) {
	std::vector<std::vector<size_t>> generated_graph;
	generated_graph.resize(nodes);

	size_t all_edges;
	if (sparse) {
		all_edges = std::round(edges * nodes);
	}
	else {
		all_edges = std::round(std::pow(nodes, 2) / edges);
	}

	std::vector<std::pair<size_t, size_t>> unused_nodes_pairs;
	for (size_t node_first = 0; node_first < nodes; ++node_first) {
		for (size_t node_second = node_first + 1; node_second < nodes; ++node_second) {
			unused_nodes_pairs.push_back({ node_first , node_second });
		}
	}

	size_t rand_position;
	for (size_t edge = 0; edge < all_edges; ++edge) {
		rand_position = std::rand() % unused_nodes_pairs.size();
		std::pair<size_t, size_t>& random_pair = unused_nodes_pairs[rand_position];
		generated_graph[random_pair.first].push_back(random_pair.second);
		generated_graph[random_pair.second].push_back(random_pair.first);
		unused_nodes_pairs.erase(unused_nodes_pairs.begin() + rand_position);
	}

	return generated_graph;
}


int main() {
	/*
	size_t nodes = 1000;
	std::vector<std::vector<size_t>> new_graph;
	new_graph.resize(nodes);
	size_t vvod;
	std::string line;
	std::ifstream inF("C://Users/Юлия/source/repos/gnm_1000_0_7_2.txt");
	if (!inF)
	{
		std::cout << "Error !";
	}
	size_t counter = 0;
	std::cout << "Open !";
	getline(inF, line);
	getline(inF, line);
	getline(inF, line);
	while (getline(inF, line))
	{
		std::istringstream iss(line);
		while (iss >> vvod) {
			if (counter == vvod) {
				continue;
			}
			new_graph[counter].push_back(vvod);
			new_graph[vvod].push_back(counter);
		}
		counter++;
		if (counter == nodes) {
			break;
		}
	}
	inF.close();
	*/
	
	std::vector<std::vector<size_t>> new_graph = {
		{ 1, 11 },
		{ 0, 2, 10 },
		{ 1, 3, 10 },
		{ 2, 4, 10 },
		{ 3, 5, 9, 11 },
		{ 4, 6, 7, 8 },
		{ 5, 7 },
		{ 5, 6, 8},
		{ 5, 7 },
		{ 4, 10, 11 },
		{ 1, 2, 3, 9 },
		{ 0, 4, 9}
	};
	
	//std::vector<std::vector<size_t>> new_graph = generateGraph(20,7, true);
	
	SimpleGraph g(new_graph);
	auto grahp_generate = std::clock();
	std::cout << "grahp generate = " << grahp_generate << "\n";
	
	DetermBridge db(g);
	std::vector< std::pair<size_t, size_t>> bridges = db.findBridgesWithDFS();
	auto det_time = std::clock();
	std::cout << "DetermBridge = " << det_time - grahp_generate << "\n";

	RandomBridge rb_one(g);
	std::vector< std::pair<size_t, size_t>> bridges2 = rb_one.findOneBridgesWithRand();
	auto rand_time = std::clock();
	std::cout << "RandomOneBridge = " << rand_time - det_time << "\n";

	size_t type_of_sort = 0;
	std::vector< std::pair<size_t, size_t>> bridges3 = rb_one.findTwoBridgesWithRand(type_of_sort);

	auto std_sort = std::clock();
	std::cout << "std sort = " << std_sort - rand_time << "\n";

	type_of_sort = 1;
	std::vector< std::pair<size_t, size_t>> bridges4 = rb_one.findTwoBridgesWithRand(type_of_sort);

	auto radix = std::clock();
	std::cout << "radix = " << radix - std_sort << "\n";
	
	type_of_sort = 2;
	std::vector< std::pair<size_t, size_t>> bridges5 = rb_one.findTwoBridgesWithRand(type_of_sort);

	auto bucket = std::clock();
	std::cout << "bucket = " << bucket - radix << "\n";

}






