#include <cassert>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>


using std::vector;
using std::cout;
using std::endl;
using std::ostream;


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
    bool Adjance(int row, int col);
    int Neighbors(int vertex_index, int* p_neighbor_list);
    void Add(int vertex_index_x, int vertex_index_y, double distance);

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

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void Graph::set_edge_info(const ST_POINT &point, const ST_EDGE edge)
{
    ST_EDGE* p_edge;

    if (point.row == point.col) {
        return;
    }

    p_edge = get_edge_info(point);
    *p_edge = edge;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
double get_random_val(double max, double min)
{
    double random_val;
    double range = max - min;

    assert(min < max);

    random_val = ((double)random() / ((double)RAND_MAX + 1)) * range + min;
    return random_val;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
#if 1
void Graph::create_edge(void)
{
    double  random_val;
    double  distance;

    for (int row = 0; row < vertices_; row++) {
        for (int col = 0; col < vertices_; col++) {
            if (row <= col) {
                continue;
            }

            random_val = get_random_val(1.0, 0.0);
            if (random_val < density_) {
                distance = get_random_val(distance_max_, distance_min_);
                Add(col, row, distance);
            }
        }
    }
}

#else

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void Graph::create_edge(void)
{
    ST_POINT point;
    double  distance;
    bool b_connect;
    int edge_num = (vertices_ * (vertices_ - 1) / 2) * density_;
    int random_value;
    int index_max_in_matrix = vertices_ * vertices_ - 1;

    do {
        random_value = get_random_val(index_max_in_matrix, 0);
        get_point_in_matrix(random_value, point);
        b_connect = Adjance(point.row, point.col);
        if (!b_connect) {
            distance = get_random_val(distance_max_, distance_min_);
            Add(point.col, point.row, distance);
            edge_num--;
        }
    } while (0 < edge_num);
}

#endif



// interface



/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
Graph::Graph(int vertices, double density, double distance_min, double distance_max)
        : vertices_(vertices),
          density_(density),
          distance_min_(distance_min),
          distance_max_(distance_max)
{
    assert(0 != vertices_);

    ST_EDGE edge;

    int element_num = vertices_ * vertices_;
    p_matrix_ = new vector<ST_EDGE>(element_num);

    edge.b_connect = false;
    edge.distance = 0.0;

    for (int i = 0; i < element_num; i++) {
        (*p_matrix_)[i] = edge;
    }

    edges_ = 0;
    create_edge();
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
bool Graph::Adjance(int row, int col)
{
    ST_EDGE* p_edge;
    ST_POINT point;

    point.row = row;
    point.col = col;
    p_edge = get_edge_info(point);

    return p_edge->b_connect;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
int Graph::Neighbors(int vertex_index, int* p_neighbor_list)
{
    ST_EDGE* p_edge = get_row_first_edge_info(vertex_index);
    int node_num = 0;

    for (int i = 0; i < vertices_; i++) {
        if (p_edge->b_connect) {
            *p_neighbor_list = i;
            p_neighbor_list++;
            node_num++;
        }
    }

    return node_num;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void Graph::Add(int vertex_index_x, int vertex_index_y, double distance)
{
    ST_POINT point;
    ST_EDGE  new_edge;

    new_edge.b_connect = true;
    new_edge.distance = distance;

    point.row = vertex_index_x;
    point.col = vertex_index_y;
    set_edge_info(point, new_edge);

    point.row = vertex_index_y;
    point.col = vertex_index_x;
    set_edge_info(point, new_edge);

    edges_++;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
ostream& operator<< (ostream& out, Graph& graph)
{
    ST_EDGE* p_edge;
    ST_POINT point;
    int      disp_width = 5;

    // column number
    //
    cout << "r/c";
    for (int col = 0; col < graph.vertices_; col++) {
        cout << std::setw(disp_width);
        cout << col;
    }
    cout << endl;

    // separator
    //
    cout << "---";
    for ( int i = 0; i < graph.vertices_; i++) {
        cout << "-----";
    }
    cout << endl;

    // matrix
    //
    for (int row = 0; row < graph.vertices_; row++) {
        // row number
        //
        cout << std::setw(2);
        cout << row << "|";

        // connection, distace
        //
        for (int col = 0; col < graph.vertices_; col++) {
            point.row = row;
            point.col = col;
            p_edge = graph.get_edge_info(point);

            cout << std::setw(disp_width);
            if (p_edge->b_connect) {
                cout << std::setprecision(3) << p_edge->distance;
            } else {
                cout << "-";
            }
        }
        cout << endl;
    }
    cout << endl;

    return out;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void TestGraph(void)
{
    srandom((unsigned)time(NULL));

    int vertices = 10;
    double density = 0.1;
    double distance_min = 1.0;
    double distance_max = 10.0;

    double edges = 0.0;
    int try_num = 2;

    for (int i = 0; i < try_num; i++) {
        Graph graph(vertices, density, distance_min, distance_max);
        edges += graph.GetNumberOfEdges();

        cout << graph;
    }

    double edges_average = edges / try_num;
    cout << "edges_average = " << edges_average << endl;
}

// EOF
