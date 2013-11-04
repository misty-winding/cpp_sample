#include <iostream>
#include <vector>
#include <queue>
#include "priority_queue.h"


using std::cout;
using std::endl;


/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void PriorityQueue::ChangePriority(Node& node)
{
    NodeQueue back;
    Node temp;
    int  size;

    size = p_queue_->size();

    while (0 < size) {
        temp = p_queue_->top();

        if (temp.index_of_vertices_ == node.index_of_vertices_) {
            temp = node;
        }

        back.push(temp);

        p_queue_->pop();
        --size;
    }

    *p_queue_ = back;
}

/*
 ***************************************************************************************************
 *   @brief  removes the top element of the queue
 **************************************************************************************************/
void PriorityQueue::MinPriority(void)
{
    p_queue_->pop();
}

/*
 ***************************************************************************************************
 *   @brief  insert queue_element into queue
 **************************************************************************************************/
void PriorityQueue::Insert(Node& node)
{
    bool b_exist = this->Contains(node);

    if (!b_exist) {
        p_queue_->push(node);
    }
}

/*
 ***************************************************************************************************
 *   @brief  returns the top element of the queue.
 **************************************************************************************************/
const Node& PriorityQueue::Top(void)
{
    const Node& node = p_queue_->top();

    return node;
}

/*
 ***************************************************************************************************
 *   @brief  does the queue contain queue_element
 **************************************************************************************************/
bool PriorityQueue::Contains(Node& node, Node& contain_node)
{
    NodeQueue back;
    Node temp;
    int  size;
    bool b_find = false;

    back = *p_queue_;

    size = p_queue_->size();

    while (0 < size) {
        temp = p_queue_->top();

        if (temp.index_of_vertices_ == node.index_of_vertices_) {
            b_find = true;
            contain_node = temp;
        }

        p_queue_->pop();
        --size;
    }

    *p_queue_ = back;
    return b_find;
}

/*
 ***************************************************************************************************
 *   @brief  does the queue contain queue_element
 **************************************************************************************************/
bool PriorityQueue::Contains(Node& node)
{
    Node contain_node;
    bool b_find = Contains(node, contain_node);

    return b_find;
}

/*
 ***************************************************************************************************
 *   @brief  does the queue contain queue_element
 **************************************************************************************************/
void PriorityQueue::Dump(void)
{
    NodeQueue back;
    Node temp;
    int  size;

    back = *p_queue_;

    size = p_queue_->size();

    for (int i = 0; i < size; i++) {
        temp = p_queue_->top();

        cout << i
             << ": "
             << temp
             << endl;

        p_queue_->pop();
    }
    cout << endl;

    *p_queue_ = back;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
ostream& operator<< (ostream& out, Node& node)
{
    out << "v_name = "
        << node.index_of_vertices_
        << ", v_from = "
        << node.vertex_from_
        << ", dist = "
        << node.distance_from_start_;

    return out;
}

/*
 ***************************************************************************************************
 *   @brief  test
 **************************************************************************************************/
void PriorityQueueTest(void)
{
    PriorityQueue pqueue;
    Node node;
    Node node_contain;

    node.index_of_vertices_ = 0;
    node.vertex_from_ = 0;
    node.distance_from_start_ = 10.0;
    pqueue.Insert(node);

    node.index_of_vertices_ = 1;
    node.vertex_from_ = 1;
    node.distance_from_start_ = 5.0;
    pqueue.Insert(node);

    node.index_of_vertices_ = 2;
    node.vertex_from_ = 2;
    node.distance_from_start_ = 1.0;
    pqueue.Insert(node);

    pqueue.Dump();

    int size = pqueue.Size();
    cout << "size = " << size << endl;

    bool b_exist = pqueue.Contains(node);
    cout << "b_exist1 = " << b_exist << endl;
    b_exist = pqueue.Contains(node, node_contain);
    cout << node_contain << endl;

    node.index_of_vertices_ = 3;
    cout << "b_exist2 = " << b_exist << endl;

    Node top = pqueue.Top();
    cout << "top: " << top << endl;

    cout << endl;
    cout << "node 2 distance = 20" << endl;
    node.index_of_vertices_ = 2;
    node.vertex_from_ = 2;
    node.distance_from_start_ = 20.0;
    pqueue.ChangePriority(node);

    cout << endl;
    pqueue.Dump();

    cout << endl;
    cout << "get rid of top" << endl;
    pqueue.MinPriority();
    cout << endl;
    pqueue.Dump();
}

// EOF
