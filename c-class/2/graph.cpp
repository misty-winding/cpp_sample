#include <cassert>


class Graph {
public:
	Graph(int vertices, double density, double distance_min, double distance_max)
		: vertices_(vertices),
		  density_(density_),
		  distance_min_(distance_min),
		  distance_max_(distance_max)
	{
		assert(0 != vertices_);
		matrix_ = new ST_EDGE[vertices_ * vertices_];
	}

	~Graph()
	{
		delete [] matrix_;
	}
	
	int get_number_of_vertices(void) { return vertices_; }
	
private:
	typedef struct {
		bool   b_connect;
		double distance;
	} ST_EDGE;

	typedef struct {
		int row;
		int col;
	} ST_POINT;
	
	int vertices_;
	double density_;
	double distance_min_;
	double distance_max_;

	ST_EDGE* matrix_;

	inline int get_index_of_matrix(const ST_POINT &point)
	{
		return point.row * vertices_ + point.col;
	}

	inline void get_row_col_of_matrix(int index, ST_POINT &point)
	{
		point.row = index / vertices_;
		point.col = index % vertices_;
	}
};

void TestGraph(void)
{
	int vertices = 10;
	double density = 0.1;
	double distance_min = 1.0;
	double distance_max = 10.0;
	
	Graph graph(vertices, density, distance_min, distance_max);
}

// EOF
