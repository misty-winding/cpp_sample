
using std::ostream;
using std::vector;


typedef struct {
    bool   b_connect;
    double distance;
} ST_EDGE;


typedef struct {
    int row;
    int col;
} ST_POINT;


class Graph {
public:
    Graph(int vertices, double density, double distance_min, double distance_max);
    ~Graph() { delete p_matrix_; }

    int GetNumberOfVertices(void) { return vertices_; }
    int GetNumberOfEdges(void) { return edges_; }
    bool Adjance(int vertex_index_x, int vertex_index_y);
    int Neighbors(int vertex_index, int* p_neighbor_list);
    void Add(int vertex_index_x, int vertex_index_y, double distance);
    ST_EDGE* GetEdgeValue(int vertex_index_x, int vertex_index_y);

    friend ostream& operator<< (ostream& out, Graph& graph);


private:
    int vertices_;
    int edges_;
    double density_;
    double distance_min_;
    double distance_max_;

    vector<ST_EDGE>* p_matrix_;

    inline int get_index_in_matrix(const ST_POINT &point)
    {
        assert(point.row < vertices_);
        assert(point.col < vertices_);

        return point.row * vertices_ + point.col;
    }

    inline int get_index_in_matrix(int vertex_index)
    {
        assert(vertex_index < vertices_);

        return vertex_index * vertices_;
    }

    inline void get_point_in_matrix(int index, ST_POINT &point)
    {
        assert(index < vertices_ * vertices_);

        point.row = index / vertices_;
        point.col = index % vertices_;
    }

    inline ST_EDGE* get_edge_info(int index)
    {
        assert(index < vertices_ * vertices_);

        return &(*p_matrix_)[index];
    }

    inline ST_EDGE* get_edge_info(const ST_POINT &point)
    {
        int index = get_index_in_matrix(point);
        return &(*p_matrix_)[index];
    }

    inline ST_EDGE* get_row_first_edge_info(int vertex_index)
    {
        int index = get_index_in_matrix(vertex_index);
        ST_EDGE* p_edge = get_edge_info(index);

        return p_edge;
    }

    void set_edge_info(const ST_POINT &point, const ST_EDGE edge);
    void create_edge(void);
};
