using std::vector;


class NODE;
typedef vector<NODE> CLOSE_LIST;


class NODE {
public:
	friend bool operator<(const NODE& x, const NODE& y)
	{
		if (x.distance_from_start < y.distance_from_start) {
			return true;
		} else {
			return false;
		}
	}

	typedef typename CLOSE_LIST::iterator iterator;

	int index_of_vertics;
	int vertex_from;
	double distance_from_start;
};

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
class PriorityQueue {

};
