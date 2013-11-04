#include <vector>
#include <queue>
#include "priority_queue.h"


/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void PriorityQueue::ChangePriority(NODE& node)
{
    NODE_PQUEUE back;
    NODE temp;
    int  size;
    bool b_find = false;

    size = p_queue_->size();

    while (0 < size) {
        temp = p_queue_->top();

        if (temp.index_of_vertics == node.index_of_vertics) {
            b_find = true;
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
 *   @brief
 **************************************************************************************************/
bool PriorityQueue::Contains(NODE& node)
{
    NODE_PQUEUE back;
    NODE temp;
    int  size;
    bool b_find = false;

    back = *p_queue_;

    size = p_queue_->size();

    while (0 < size) {
        temp = p_queue_->top();

        if (temp.index_of_vertics == node.index_of_vertics) {
            b_find = true;
        }

        p_queue_->pop();
        --size;
    }

    *p_queue_ = back;
    return b_find;
}
