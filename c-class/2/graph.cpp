#include <cassert>
#include <vector>
#include <iostream>
#include <iomanip>


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
    Graph(int vertices, double density, double distance_min, double distance_max)
        : vertices_(vertices),
          density_(density),
          distance_min_(distance_min),
          distance_max_(distance_max)
    {
        assert(0 != vertices_);

        int element_num = vertices_ * vertices_;
        p_matrix_ = new vector<ST_EDGE>(element_num);

        for (int i = 0; i < element_num; i++) {
            (*p_matrix_)[i].b_connect = false;
            (*p_matrix_)[i].distance = 10.3;
        }
    }

    ~Graph()
    {
        delete p_matrix_;
    }

    int get_number_of_vertices(void) { return vertices_; }

    bool adjance(int row, int col)
    {
        ST_EDGE* p_edge;
        ST_POINT point;

        point.row = row;
        point.col = col;
        p_edge = get_edge(point);
    }

    friend ostream& operator<< (ostream& out, Graph& graph);


private:
    int vertices_;
    double density_;
    double distance_min_;
    double distance_max_;

    vector<ST_EDGE>* p_matrix_;

    inline int get_index_of_matrix(const ST_POINT &point)
    {
        return point.row * vertices_ + point.col;
    }

    inline void get_row_col_of_matrix(int index, ST_POINT &point)
    {
        point.row = index / vertices_;
        point.col = index % vertices_;
    }

    inline ST_EDGE* get_edge(const ST_POINT &point)
    {
        int index = get_index_of_matrix(point);
        return &(*p_matrix_)[index];
    }
};

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
    cout << "   ";
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
            p_edge = graph.get_edge(point);

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

void TestGraph(void)
{
    int vertices = 10;
    double density = 0.1;
    double distance_min = 1.0;
    double distance_max = 10.0;

    Graph graph(vertices, density, distance_min, distance_max);
    cout << graph;
}

// EOF
