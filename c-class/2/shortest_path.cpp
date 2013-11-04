#include <cassert>
#include <iostream>
#include <vector>
#include <queue>
#include "graph.h"
#include "priority_queue.h"
#include "shortest_path.h"


using std::priority_queue;
using std::cout;
using std::endl;


/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
bool is_closeset_contains(NodeList* p_closeset, Node& node)
{
    NodeList::iterator iter;
    Node node_in_list;
    bool b_found = false;

    for (iter = p_closeset->begin();
         iter != p_closeset->end();
         iter++) {

        node_in_list = *iter;
        if (node_in_list.index_of_vertices_ == node.index_of_vertices_) {
            b_found = true;
            break;
        }
    }

    return b_found;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void dump_closeset(NodeList* p_closeset)
{
    NodeList::iterator iter;

    for (iter = p_closeset->begin();
         iter != p_closeset->end();
         iter++) {
        cout << *iter << endl;
    }
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
int ShortestPath::update_openset(NodeList* p_closeset, PriorityQueue* p_openset)
{
    int vertices = p_graph_->GetNumberOfVertices();
    int* p_neighbor_list = new int [vertices];
    int* p_neighbor_list_top = p_neighbor_list;
    int neighbor_num;
    int vertex_index;
    Node node;
    bool b_exist;

    NodeList::iterator iter = (*p_closeset).begin();

    // for all closeset
    //
    while (iter != (*p_closeset).end()) {
        node = *iter;

        cout << "neighbor check for " << endl;
        cout << node << endl;

        // find neighbors
        //
        vertex_index = node.index_of_vertices_;
        neighbor_num = p_graph_->Neighbors(vertex_index, p_neighbor_list_top);
        cout << "neighbor_num = " << neighbor_num << endl;

        // add to openset
        //
        p_neighbor_list = p_neighbor_list_top;

        for (int i = 0; i < neighbor_num; i++) {
            int index_of_neighbor = *p_neighbor_list;
            ST_EDGE* p_edge = p_graph_->GetEdgeValue(vertex_index, index_of_neighbor);
            assert(p_edge->b_connect);

            Node neighbor_node;
            neighbor_node.index_of_vertices_ = index_of_neighbor;
            neighbor_node.vertex_from_ = vertex_index;
            neighbor_node.distance_from_start_ =
                node.distance_from_start_ + p_edge->distance;

            // if node has already existed in close_set, omit
            //
            b_exist = is_closeset_contains(p_closeset, neighbor_node);
            if (b_exist) {
                p_neighbor_list++;
                continue;
            }

            Node node_contain;
            b_exist = p_openset->Contains(neighbor_node, node_contain);

            // if node has already existed, check distance
            //
            if (b_exist) {
                if (neighbor_node.distance_from_start_ < node_contain.distance_from_start_) {
                    p_openset->ChangePriority(neighbor_node);
                }
            } else {
                p_openset->Insert(neighbor_node);
            }

            p_neighbor_list++;
        }

        ++iter;
    }

    cout << endl;
    cout << "open_set" << endl;
    p_openset->Dump();

    delete [] p_neighbor_list_top;
    return p_openset->Size();
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
bool ShortestPath::update_closeset(NodeList* p_closeset, PriorityQueue* p_openset, int end)
{
    Node next;
    bool b_finish;

    next = p_openset->Top();
    p_closeset->push_back(next);

    p_openset->MinPriority();

    if (next.index_of_vertices_ == end) {
        b_finish = true;
    } else {
        b_finish = false;
    }

    cout << "close_set: b_finis = " << b_finish << endl;
    dump_closeset(p_closeset);
    cout << endl;

    return b_finish;
}



// interface



/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
bool ShortestPath::Path(int start, int end, NodeList* p_result_list)
{
    NodeList*      p_closeset;
    PriorityQueue* p_openset;
    Node           node;
    int openset_node_num;
    bool b_finish;
    int count;

    p_closeset = new NodeList;
    p_openset = new PriorityQueue;

    // first close_set;
    node.index_of_vertices_ = start;
    node.vertex_from_ = start;
    node.distance_from_start_ = 0.0;
    (*p_closeset).push_back(node);

    count = 0;

    do {
        cout << "try: " << count << " ---------------" << endl;

        // update openset
        openset_node_num = update_openset(p_closeset, p_openset);
        if (0 == openset_node_num) {
            b_finish = false;
            goto EXIT;
        }

        // update closeset
        b_finish = update_closeset(p_closeset, p_openset, end);
        if (b_finish) {
            *p_result_list = *p_closeset;
        }

        ++count;

    } while (!b_finish);

EXIT:
    // clean up
    //
    delete p_closeset;
    delete p_openset;

    return b_finish;
}

// EOF
