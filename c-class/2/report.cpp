#include <cassert>
#include <iostream>
#include <vector>
#include <queue>
#include "graph.h"
#include "priority_queue.h"
#include "shortest_path.h"
#include "report.h"


using std::cout;
using std::endl;


/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void Report::exec(double density)
{
    Graph* p_graph;
	int vertices = 50;
	double distance_min = 1.0;
	double distance_max = 10.0;

	p_graph = new Graph(vertices, density, distance_min, distance_max);
	if (debug_) {
		cout << *p_graph;
	}

    int start = 0;
    int end;
	int found_num = 0;
	double total_distance = 0.0;
	
	for (end = 1; end < vertices; end++) {
		ShortestPath shortest_path(p_graph);
		NodeList* p_node_list = new NodeList;
		bool b_found;
		double distance;

		b_found = shortest_path.Path(start, end, p_node_list, distance);
		if (debug_) {
			shortest_path.DumpPath(b_found, p_node_list, distance);
		}
		
		if (b_found) {
			++found_num;
			total_distance += distance;
		}
		
		delete p_node_list;
	}
	
	delete p_graph;

	cout << " ** average **" << endl;
	cout << " found_num = " << found_num << endl;
	
	if (0 != found_num) {
		cout << " ave = " << total_distance / found_num << endl;
	}

	cout << endl;
}

// EOF
