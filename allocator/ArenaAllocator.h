#ifndef ARENA_ALLOCATOR_H
#define ARENA_ALLOCATOR_H


#include <cassert>
#include "FreeListAllocator.h"


/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
class ArenaAllocator
{
public:
    ArenaAllocator();
    static ArenaAllocator* GetInstance(void)
    {
        static ArenaAllocator s_arena_allocator;
    return &s_arena_allocator;
    }
    void* allocate(size_t size, int location);
    void deallocate(void* p, int location);

private:
    FreeListAllocator* getAllocator(int location)
    {
        if (!(location < free_list_num_)) {
            assert(false);
        return NULL;
    }

    return s_p_free_list_[location];
    }

    static const int free_list_num_ = 5;
    static const int alignment_ = sizeof(unsigned long);
    FreeListAllocator*  s_p_free_list_[free_list_num_];
};


extern void* ArenaAllocatorAllocate(size_t size, int location);
extern void ArenaAllocatorDeallocate(void* p, int location);


/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
template<int LOCATION = 0>
class ArenaAllocatorIF
{
public:
    static void* operator new(size_t size);
    static void* operator new(size_t size, void* p_ptr);
    static void operator delete(void* p);
};

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
template<int LOCATION>
void* ArenaAllocatorIF<LOCATION>::operator new(size_t size)
{
    void* p_ptr = ArenaAllocatorAllocate(size, LOCATION);
    return p_ptr;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
template<int LOCATION>
void* ArenaAllocatorIF<LOCATION>::operator new(size_t size, void* p_ptr)
{
    if (0 == size) {
    }
    return p_ptr;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
template<int LOCATION>
void ArenaAllocatorIF<LOCATION>::operator delete(void* p)
{
    ArenaAllocatorDeallocate(p, LOCATION);
}


#endif // #ifndef ARENA_ALLOCATOR_H

// EOF
