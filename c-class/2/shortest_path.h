#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H


/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
class ShortestPath {
public:
    ShortestPath(Graph* p_graph) : p_graph_(p_graph) {}
    bool Path(int start, int end, NodeList* p_result_list, double& distance);
    void DumpPath(bool b_found, NodeList* p_result_list, double distance);
    
private:
    Graph* p_graph_;
    static const bool debug_ = false;
    
    int update_openset(NodeList* p_closeset, PriorityQueue* p_openset);
    bool update_closeset(NodeList* p_closeset, PriorityQueue* p_openset, int end);
    void calc_closeset(int start, int end, NodeList* p_result_list);
};

#endif // #ifndef SHORTEST_PATH_H

// EOF
