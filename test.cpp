// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
 /*
 TEST_F(CollectionTest, AlwaysFail)
 {
     FAIL();
 }
 */

 // TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, AddingSingleValueMakesCollectionNonEmpty)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, AddingFiveValuesGivesSizeOfFive)
{
    // Verify initial empty state
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    // Add five entries
    add_entries(5);

    // Verify collection now has five elements
    ASSERT_FALSE(collection->empty());
    ASSERT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeIsGreaterThanOrEqualToSize)
{
    // Test with 0 entries
    EXPECT_GE(collection->max_size(), collection->size());

    // Test with 1 entry
    add_entries(1);
    EXPECT_GE(collection->max_size(), collection->size());

    // Test with 5 entries
    add_entries(4);  // Already have 1, so add 4 more to make 5
    EXPECT_GE(collection->max_size(), collection->size());

    // Test with 10 entries
    add_entries(5);  // Already have 5, so add 5 more to make 10
    EXPECT_GE(collection->max_size(), collection->size());
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityIsGreaterThanOrEqualToSize)
{
    // Test with 0 entries
    EXPECT_GE(collection->capacity(), collection->size());

    // Test with 1 entry
    add_entries(1);
    EXPECT_GE(collection->capacity(), collection->size());

    // Test with 5 entries
    add_entries(4);  // Already have 1, so add 4 more
    EXPECT_GE(collection->capacity(), collection->size());

    // Test with 10 entries
    add_entries(5);  // Already have 5, so add 5 more
    EXPECT_GE(collection->capacity(), collection->size());
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizingIncreasesCollection)
{
    size_t originalSize = collection->size();
    size_t newSize = originalSize + 5;

    // Resize collection to be larger
    collection->resize(newSize);

    // Verify size has increased
    ASSERT_GT(collection->size(), originalSize);
    ASSERT_EQ(collection->size(), newSize);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizingDecreasesCollection)
{
    // Add some elements first
    add_entries(10);
    size_t originalSize = collection->size();
    size_t newSize = originalSize - 5;

    // Resize collection to be smaller
    collection->resize(newSize);

    // Verify size has decreased
    ASSERT_LT(collection->size(), originalSize);
    ASSERT_EQ(collection->size(), newSize);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizingDecreasesCollectionToZero)
{
    // Add some elements first
    add_entries(5);

    // Verify collection is not empty
    ASSERT_FALSE(collection->empty());

    // Resize collection to zero
    collection->resize(0);

    // Verify collection is now empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
    // Add some elements
    add_entries(5);

    // Verify collection is not empty
    ASSERT_FALSE(collection->empty());
    ASSERT_EQ(collection->size(), 5);

    // Clear the collection
    collection->clear();

    // Verify collection is now empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseBeginToEndErasesCollection)
{
    // Add some elements
    add_entries(5);

    // Verify collection is not empty
    ASSERT_FALSE(collection->empty());

    // Erase from begin to end
    collection->erase(collection->begin(), collection->end());

    // Verify collection is now empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityButNotSize)
{
    size_t originalSize = collection->size();
    size_t originalCapacity = collection->capacity();
    size_t newCapacity = originalCapacity + 10;

    // Reserve more capacity
    collection->reserve(newCapacity);

    // Verify size remains unchanged
    ASSERT_EQ(collection->size(), originalSize);

    // Verify capacity has increased
    ASSERT_GE(collection->capacity(), newCapacity);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, AtThrowsExceptionWhenIndexOutOfBounds)
{
    // Add some elements
    add_entries(3);

    // Verify accessing valid index doesn't throw
    ASSERT_NO_THROW(collection->at(0));
    ASSERT_NO_THROW(collection->at(2));

    // Verify accessing out of bounds index throws exception
    ASSERT_THROW(collection->at(10), std::out_of_range);
    ASSERT_THROW(collection->at(collection->size()), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative

// Positive test: Verify that front() returns the first element
TEST_F(CollectionTest, FrontReturnsFirstElement)
{
    // Add some elements
    collection->push_back(42);  // Explicitly add 42 as first element
    add_entries(3);  // Add more random elements

    // Verify front returns the first element (42)
    ASSERT_EQ(collection->front(), 42);
}

// Negative test: Verify that pop_back() on empty collection doesn't cause undefined behavior
TEST_F(CollectionTest, PopBackOnEmptyCollectionDoesntCrash)
{
    // Ensure collection is empty
    collection->clear();
    ASSERT_TRUE(collection->empty());

    // Calling pop_back on empty vector is undefined behavior
    // A well-designed test should check if we can detect this situation
    // Rather than calling pop_back directly, we could check if empty before popping
    bool safeToPopBack = !collection->empty();

    // This is a negative test showing we should NOT proceed with pop_back
    ASSERT_FALSE(safeToPopBack);

    // If we wanted to be thorough, we could also add elements and verify pop_back works
    add_entries(1);
    size_t sizeBefore = collection->size();
    collection->pop_back();
    ASSERT_EQ(collection->size(), sizeBefore - 1);
}