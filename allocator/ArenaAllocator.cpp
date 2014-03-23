#include <iostream>
#include <cstring>
#include <cassert>
#include "ArenaAllocator.h"


using std::cout;
using std::endl;


/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
ArenaAllocator::ArenaAllocator()
{
    const unsigned long size_byte = 1024;

    static unsigned long s_a_buff0[size_byte / sizeof(unsigned long)];
    static unsigned long s_a_buff1[size_byte / sizeof(unsigned long)];
    static unsigned long s_a_buff2[size_byte / sizeof(unsigned long)];
    static unsigned long s_a_buff3[size_byte / sizeof(unsigned long)];
    static unsigned long s_a_buff4[size_byte / sizeof(unsigned long)];

    s_p_free_list_[0] = new FreeListAllocator(size_byte, s_a_buff0);
    s_p_free_list_[1] = new FreeListAllocator(size_byte, s_a_buff1);
    s_p_free_list_[2] = new FreeListAllocator(size_byte, s_a_buff2);
    s_p_free_list_[3] = new FreeListAllocator(size_byte, s_a_buff3);
    s_p_free_list_[4] = new FreeListAllocator(size_byte, s_a_buff4);
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void* ArenaAllocator::allocate(size_t size, int location)
{
    FreeListAllocator* p_free_list = getAllocator(location);
    if (NULL == p_free_list) {
        return NULL;
    }

    void* p_ptr;
    p_ptr = p_free_list->allocate(size, alignment_);

    cout << __FUNCTION__ << "():" << location <<
                            "   0x" << std::hex << p_ptr <<
                            " size = " << std::dec << size << endl;
    return p_ptr;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void ArenaAllocator::deallocate(void* p, int location)
{
    FreeListAllocator* p_free_list = getAllocator(location);
    if (NULL == p_free_list) {
        return;
    }

    p_free_list->deallocate(p);

    cout << __FUNCTION__ << "():" << location <<
                            " 0x" << std::hex << p << endl;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void* ArenaAllocatorAllocate(size_t size, int location)
{
    void* p_ptr = ArenaAllocator::GetInstance()->allocate(size, location);
    return p_ptr;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void ArenaAllocatorDeallocate(void* p, int location)
{
    ArenaAllocator::GetInstance()->deallocate(p, location);
}

// EOF
