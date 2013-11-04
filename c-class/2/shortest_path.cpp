#include <cassert>
#include <iostream>
#include <vector>
#include <queue>
#include "graph.h"
#include "priority_queue.h"


using std::priority_queue;


/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
class ShortestPath {
public:
	ShortestPath(Graph* p_graph) : p_graph_(p_graph) {}
	void Path(int start, int end, CLOSE_LIST* p_result_list);

private:
	Graph* p_graph_;

	typedef priority_queue<NODE> OPEN_LIST;

	int update_openset(CLOSE_LIST* p_closeset, OPEN_LIST* p_openset);
};

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
int ShortestPath::update_openset(CLOSE_LIST* p_closeset, OPEN_LIST* p_openset)
{
	int vertics = p_graph_->GetNumberOfVertices();
	int* p_neighbor_list = new int [vertics];
	int neighbor_num;
	int vertex_index;
	NODE node;

	NODE::iterator iter = (*p_closeset).begin();

	// for all closeset
	//
	while (iter != (*p_closeset).end()) {
		node = *iter;

		// find neighbors
		//
		vertex_index = node.index_of_vertics;
		neighbor_num = p_graph_->Neighbors(vertex_index, p_neighbor_list);

		// add to openset
		//
		for (int i = 0; i < neighbor_num; i++) {
			int index_of_neighbor = *p_neighbor_list;
			ST_EDGE* p_edge = p_graph_->GetEdgeValue(vertex_index, index_of_neighbor);

			p_neighbor_list++;
		}

		++iter;
	}

	delete [] p_neighbor_list;

	return 0;
}



// interface



/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void ShortestPath::Path(int start, int end, CLOSE_LIST* p_result_list)
{
	CLOSE_LIST* p_closeset;
	OPEN_LIST*  p_openset;
	NODE        node;

	p_closeset = new CLOSE_LIST;
    p_openset = new OPEN_LIST;

	// first close_set;
	node.index_of_vertics = start;
	node.vertex_from = start;
	node.distance_from_start = 0.0;
	(*p_closeset).push_back(node);

	// update openset

	// update closeset


	// clean
	delete p_closeset;
	delete p_openset;
}

// EOF
