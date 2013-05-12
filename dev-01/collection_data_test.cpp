#include "gmock/gmock.h"


// ###todo use include because I didn't make header file.
#include "collection_data.cpp"


using namespace testing;


TEST(collection_data, initialize)
{
	TopA1Holder top_a1;

	ASSERT_THAT(0, top_a1.GetTopA1Num());
}

TEST(collection_data, add_data)
{
	TopA1Holder top_a1;
	TopA1Holder::PtrTopA1 ptr_top_a1;
	int key;

	key = 0;
	TopA1Holder::PtrTopA1 p_data0(new TopA1(key));
	top_a1.AddTopA1(p_data0);
	ASSERT_THAT(top_a1.GetTopA1Num(), 1);

	// unused key => NULL
	ptr_top_a1 = top_a1.GetTopA1Ptr(key + 1);
	ASSERT_TRUE(ptr_top_a1 == NULL);

	// used key => success
	ptr_top_a1 = top_a1.GetTopA1Ptr(key);
	ASSERT_THAT(ptr_top_a1, NotNull());

	// get key inside data
	ASSERT_THAT(ptr_top_a1->GetKey(), key);


	key = 2;
	TopA1Holder::PtrTopA1 p_data2(new TopA1(key));
	top_a1.AddTopA1(p_data2);
	ASSERT_THAT(top_a1.GetTopA1Num(), 2);

	// unused key => NULL
	ptr_top_a1 = top_a1.GetTopA1Ptr(key + 1);
	ASSERT_TRUE(ptr_top_a1 == NULL);

	// used key => success
	ptr_top_a1 = top_a1.GetTopA1Ptr(key);
	ASSERT_THAT(ptr_top_a1, NotNull());

	// get key inside data
	ASSERT_THAT(ptr_top_a1->GetKey(), key);
}

TEST(collection_data, CollectionPtr)
{
	TopA1Holder top_a1;
	TopA1Holder::CollectionPtr collection_ptr;

	collection_ptr = top_a1.GetCollectionPtr();
	ASSERT_THAT(collection_ptr->GetNum(), 0);
}

// EOF
