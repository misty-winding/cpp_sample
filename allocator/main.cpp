#include <iostream>
#include <cstring>
#include <cassert>
#include <vector>
#include <stdio.h>
#include "Poco/SharedPtr.h"
#include "ArenaAllocator.h"
#include "ProxyAllocator.h"
#include "stl_allocator.h"


using Poco::SharedPtr;
using std::cout;
using std::endl;


/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
template <int LOCATION = 0>
class ReferenceCounterLocation : public Poco::ReferenceCounter, public ArenaAllocatorIF<LOCATION>
{
};

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
#define LOCATION_FOR_THIS (1)

struct POD: public ArenaAllocatorIF<LOCATION_FOR_THIS>
{
public:
    int member_0;
    int member_1;
    int member_2;
    int member_3;
};

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/

class TestObject: public ArenaAllocatorIF<LOCATION_FOR_THIS>
{
public:
    TestObject() : p_val_(NULL) {}
    ~TestObject();
    void CreatePOD(void);

private:
    static const int s_location_ = LOCATION_FOR_THIS;
    POD* p_val_;
};

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
TestObject::~TestObject()
{
    if (NULL == p_val_) {
        return;
    }

    delete p_val_;
    p_val_ = NULL;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void TestObject::CreatePOD(void)
{
    size_t size = sizeof(*p_val_);

    p_val_ = new POD;
    memset(p_val_, 0, size);
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
typedef SharedPtr<TestObject, ReferenceCounterLocation<LOCATION_FOR_THIS> > PtrTestOject;

static void test(void)
{
    cout << "**** " << __FUNCTION__ << "() ****" << endl;

    TestObject* p_obj = new TestObject;
    p_obj->CreatePOD();

    PtrTestOject ptr_obj;
    ptr_obj = p_obj;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
using namespace allocator;

static void test2(void)
{
    cout << "**** " << __FUNCTION__ << "() ****" << endl;

    static const int size_byte = 1024;
    static unsigned long s_a_buff[size_byte / sizeof(unsigned long)];

    FreeListAllocator* p_free_list_allocator;
    p_free_list_allocator = new FreeListAllocator(size_byte, s_a_buff);

    ProxyAllocator *p_proxy_allocator = new ProxyAllocator(*p_free_list_allocator);

    delete p_proxy_allocator;
    delete p_free_list_allocator;
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
using namespace MyLib;
using std::vector;

class ClassTest
{
public:
private:
    int member_0;
    int member_1;
    int member_2;
};

static void test3(void)
{
    cout << "**** " << __FUNCTION__ << "() ****" << endl;

    vector<PtrTestOject, StlAllocator<PtrTestOject, 2> > v;

    TestObject* p_obj = new TestObject;
    p_obj->CreatePOD();

    PtrTestOject ptr_obj;
    ptr_obj = p_obj;

    v.push_back(ptr_obj);
    v.pop_back();

    cout << "-- v2 --" << endl;

    TestObject* p_obj2 = new TestObject;
    p_obj2->CreatePOD();

    PtrTestOject ptr_obj2;
    ptr_obj2 = p_obj2;

    vector<PtrTestOject, StlAllocator<PtrTestOject, 3> > v2;
    v2.push_back(ptr_obj2);
    v2.pop_back();

    cout << "-- v3 --" << endl;

    vector<ClassTest, StlAllocator<ClassTest, 4> > v3;
    ClassTest class_test;
    v3.push_back(class_test);
    v3.pop_back();
}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
void test4(void)
{
    char* bigbuf = (char*)malloc(10000);

    // remember our allocs
    std::vector<void*> _allocs;

    FreeListAllocator allocator(10000, bigbuf);

    // lots of iterations
    for(int i = 0; i < 1000; i++)
    {
        // allocate blocks till the allocator is full
        for(;;)
        {
            size_t allocSize = rand()%500+1;
            u8 alignment = rand()%2 == 0 ? 4 : 2;

            //printf("%d %d\n", (int) allocSize, alignment);

            void* alloc = allocator.allocate(allocSize, alignment);

            if (!alloc)
                break;

            _allocs.push_back(alloc);
        }

        if(i%2 == 0)
        {
            // randomly deallocate ~50% of blocks (forward)
            for(size_t j = 0; j < _allocs.size(); j++)
            {
                if ((rand() % 2) == 0 && _allocs[j] != NULL)
                {
                    allocator.deallocate(_allocs[j]);
                    _allocs[j] = NULL;
                }
            }
        } else
        {
            // randomly deallocate ~50% of blocks (backwards)
            for(int j = _allocs.size()-1; j >= 0; j--)
            {
                if ((rand() % 2) == 0 && _allocs[j] != NULL)
                {
                    allocator.deallocate(_allocs[j]);
                    _allocs[j] = NULL;
                }
            }
        }
    }

    for(size_t i = 0; i < _allocs.size(); i++)
    {
        if(_allocs[i] != NULL)
        {
            allocator.deallocate(_allocs[i]);
            _allocs[i] = NULL;
        }
    }

    printf("%d == %d\n", 0, (int) allocator.getUsedMemory());

}

/*
 ***************************************************************************************************
 *   @brief
 **************************************************************************************************/
int main(int argc, char** argv)
{
    if (0 == argc) {}
    if (NULL == argv){}

    test();
    test2();
    test3();
    test4();

    return 0;
}

// EOF
