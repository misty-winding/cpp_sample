using std::vector;
using std::priority_queue;


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

        NODE& operator=(const NODE& rhs)
        {
            if (this != &rhs) {
                    this->index_of_vertics = rhs.index_of_vertics;
                    this->vertex_from = rhs.vertex_from;
                    this->distance_from_start = rhs.distance_from_start;
            }

            return *this;
        }

        typedef CLOSE_LIST::iterator iterator;

        int index_of_vertics;
        int vertex_from;
        double distance_from_start;
};

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
/*
  chgPrioirity(PQ, priority): changes the priority (node value) of queue element.
  minPrioirty(PQ): removes the top element of the queue.
  contains(PQ, queue_element): does the queue contain queue_element.
  Insert(PQ, queue_element): insert queue_element into queue
  top(PQ):returns the top element of the queue.
  size(PQ): return the number of queue_elements.
 */


typedef priority_queue<NODE> NODE_PQUEUE;


class PriorityQueue {
public:
    PriorityQueue()  { p_queue_ = new NODE_PQUEUE; }
    ~PriorityQueue() { delete p_queue_; }

    void ChangePriority(NODE& node);
    bool Contains(NODE& node);
    int size() { return p_queue_->size(); }

private:
    NODE_PQUEUE* p_queue_;

};
