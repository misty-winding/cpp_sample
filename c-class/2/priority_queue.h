#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H


using std::vector;
using std::priority_queue;
using std::ostream;


class Node {
public:
    Node()
    {

    }

    Node& operator=(const Node& rhs)
    {
        if (this != &rhs) {
            this->index_of_vertices_ = rhs.index_of_vertices_;
            this->vertex_from_ = rhs.vertex_from_;
            this->distance_from_start_ = rhs.distance_from_start_;
        }

        return *this;
    }

    friend bool operator<(const Node& x, const Node& y)
    {
        if (x.distance_from_start_ > y.distance_from_start_) {
            return true;
        } else {
            return false;
        }
    }

    friend ostream& operator<<(ostream& out, Node& node);

    int index_of_vertices_;
    int vertex_from_;
    double distance_from_start_;
};


typedef vector<Node> NodeList;


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


class PriorityQueue {
public:
    PriorityQueue()  { p_queue_ = new NodeQueue; }
    ~PriorityQueue() { delete p_queue_; }

    void ChangePriority(Node& node);
    void MinPriority(void);
    void Insert(Node& node);
    bool Contains(Node& node, Node& contain_node);
    bool Contains(Node& node);
    const Node& Top(void);
    int Size() { return p_queue_->size(); }
    void Dump(void);

private:
    typedef priority_queue<Node> NodeQueue;
    NodeQueue* p_queue_;

};

#endif // #ifndef PRIORITY_QUEUE_H
