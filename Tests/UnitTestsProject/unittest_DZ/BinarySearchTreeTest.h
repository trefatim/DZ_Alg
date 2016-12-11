#pragma once
#include "gtest\gtest.h"
#include "elements.h"
#include "BinarySearchTree.h"
#include <list>

class BinarySearchTreeTest : public testing::Test {
protected:
	BinarySearchTree* binary_search_tree;
	void SetUp();
	void TearDown();
};