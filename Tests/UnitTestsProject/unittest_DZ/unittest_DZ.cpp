#include "gtest\gtest.h"
#include "SortedArrayTest.h"
#include "HashTableTest.h"
#include "BinarySearchTreeTest.h"


int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}