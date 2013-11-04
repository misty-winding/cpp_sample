/*
    Graphs Implementation
      - edge lists
        or
      - matrices


     Basic problem:
       Write a set of constructors for declaring and initializing a graph.
       An edge will have a positive cost that is its distance.
       Have a procedure that produces a randomly generated set of edges with positive distances.
       Assume the graphs are undirected.
       The random graph procedure should have
           edge density as a parameter and
           distance range as a parameter.
           So a graph whose density is 0.1 would have 10% of its edges picked at random and
           its edge distance would be selected at random from the distance range.
       The procedure should run through all possible undirected edges,
           say (i,j) and place the edge in the graph
           if a random probability calculation is less than the density.
           Compute for a set of randomly generated graphs an average shortest path.


     Turn in:
       Printout of program, 200 words on what you learned, and
       output showing the average path length calculation.
         Use densities: 20% and 40% on a graph of 50 nodes with a distance range of 1.0 to 10.0.
         To get an average path length, compute the 49 paths:

         1 to 2, 1 to 3, 1 to 4, …, 1 to 50.

        [In an instance where there is no path between 1 and n,
         omit that value from the average.
         This should be very rare for the chosen density and size in this homework.]


*/

#include <cassert>
#include <iostream>
#include <vector>
#include <queue>
#include "graph.h"
#include "priority_queue.h"
#include "shortest_path.h"


using std::cout;
using std::endl;


extern void TestGraph(void);
extern void PriorityQueueTest(void);


/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void algo_test(void)
{
    int vertices = 6;
    double density = 0;
    double distance_min = 1.0;
    double distance_max = 10.0;

    Graph* p_graph = new Graph(vertices, density, distance_max, distance_min);

    p_graph->Add(0, 1, 2.0);
    p_graph->Add(0, 2, 5.0);
    p_graph->Add(0, 3, 4.0);

    p_graph->Add(1, 3, 3.0);
    p_graph->Add(1, 4, 6.0);

    p_graph->Add(2, 3, 2.0);
    p_graph->Add(2, 5, 6.0);

    p_graph->Add(3, 4, 2.0);

    p_graph->Add(4, 5, 4.0);

    cout << *p_graph;

    ShortestPath* p_short_path = new ShortestPath(p_graph);

    int start = 0;
    int end = 5;
    NodeList* p_node_list = new NodeList;

    p_short_path->Path(start, end, p_node_list);

    delete p_short_path;
    delete p_graph;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
int main(int argc, char** argv)
{
    if (0 == argc) {

    }
    if (NULL == argv) {

    }

    // TestGraph();
    // PriorityQueueTest();
    algo_test();

    return 0;
}

// EOF
