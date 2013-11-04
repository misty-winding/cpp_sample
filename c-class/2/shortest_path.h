/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
class ShortestPath {
public:
    ShortestPath(Graph* p_graph) : p_graph_(p_graph) {}
    bool Path(int start, int end, NodeList* p_result_list);

private:
    Graph* p_graph_;

    int update_openset(NodeList* p_closeset, PriorityQueue* p_openset);
        int update_closeset(int end, NodeList* p_closeset, PriorityQueue* p_openset);
        bool update_closeset(NodeList* p_closeset, PriorityQueue* p_openset, int end);
};

// EOF
