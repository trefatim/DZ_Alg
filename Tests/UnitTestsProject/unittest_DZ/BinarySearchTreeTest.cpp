#include "BinarySearchTreeTest.h"

void BinarySearchTreeTest::SetUp() {
	binary_search_tree = new BinarySearchTree();
	binary_search_tree->AddElement(*(new BinarySearchTreeElement(100, 84)));
	binary_search_tree->AddElement(*(new BinarySearchTreeElement(80, 111)));
	binary_search_tree->AddElement(*(new BinarySearchTreeElement(310, 38)));
	binary_search_tree->AddElement(*(new BinarySearchTreeElement(56, 73)));
	binary_search_tree->AddElement(*(new BinarySearchTreeElement(84, 12)));
	binary_search_tree->AddElement(*(new BinarySearchTreeElement(218, 978)));
	binary_search_tree->AddElement(*(new BinarySearchTreeElement(418, 175)));
	binary_search_tree->AddElement(*(new BinarySearchTreeElement(30, 55)));
	binary_search_tree->AddElement(*(new BinarySearchTreeElement(356, 33)));
}

void BinarySearchTreeTest::TearDown() {
	delete binary_search_tree;
}

TEST_F(BinarySearchTreeTest, AddInEmptyTree) {
	BinarySearchTree* bst = new BinarySearchTree();
	bst->AddElement(*(new BinarySearchTreeElement(33, 11)));
	EXPECT_EQ(11, (bst->GetRoot())->GetValue());
}

TEST_F(BinarySearchTreeTest, AddLeftTest) {
	binary_search_tree->AddElement(*(new BinarySearchTreeElement(23, 1)));
	BinarySearchTreeElement* element = binary_search_tree->GetRoot();
	for (int i = 0; i < 4; ++i)
		element = element->GetLeft();
	EXPECT_EQ(1, element->GetValue());
}

TEST_F(BinarySearchTreeTest, AddRightTest) {
	binary_search_tree->AddElement(*(new BinarySearchTreeElement(500, 136)));
	BinarySearchTreeElement* element = binary_search_tree->GetRoot();
	for (int i = 0; i < 3; ++i)
		element = element->GetRight();
	EXPECT_EQ(136, element->GetValue());
}

TEST_F(BinarySearchTreeTest, AddMidTest) {
	binary_search_tree->AddElement(*(new BinarySearchTreeElement(86, 193)));
	BinarySearchTreeElement* element = binary_search_tree->GetRoot();
	element = element->GetLeft();
	for (int i = 0; i < 2; ++i)
		element = element->GetRight();
	EXPECT_EQ(193, element->GetValue());
}

TEST_F(BinarySearchTreeTest, DeleteFromEmpty) {
	BinarySearchTree* bst = new BinarySearchTree();
	EXPECT_EQ(0, bst->DeleteElement(12111));
}

TEST_F(BinarySearchTreeTest, NotFoundToBeDeleted) {
	EXPECT_EQ(0, binary_search_tree->DeleteElement(12111));
}

TEST_F(BinarySearchTreeTest, DeleteWithNoChildren) {
	binary_search_tree->DeleteElement(30);
	int buf[8] = { 100, 80, 310, 56, 84, 218, 418, 356 };
	int i = 0;
	list<BinarySearchTreeElement> lis;
	lis.push_back(*(binary_search_tree->GetRoot()));
	while (!lis.empty()) {
		EXPECT_EQ(buf[i], lis.front().GetKey());
		i++;
		if ((lis.front()).GetLeft())
			lis.push_back(*((lis.front()).GetLeft()));
		if ((lis.front()).GetRight())
			lis.push_back(*((lis.front()).GetRight()));
		lis.pop_front();
	}
}

TEST_F(BinarySearchTreeTest, DeleteWithOneChildren) {
	binary_search_tree->DeleteElement(56);
	int buf[8] = { 100, 80, 310, 30, 84, 218, 418, 356 };
	int i = 0;
	list<BinarySearchTreeElement> lis;
	lis.push_back(*(binary_search_tree->GetRoot()));
	while (!lis.empty()) {
		EXPECT_EQ(buf[i], lis.front().GetKey());
		i++;
		if ((lis.front()).GetLeft())
			lis.push_back(*((lis.front()).GetLeft()));
		if ((lis.front()).GetRight())
			lis.push_back(*((lis.front()).GetRight()));
		lis.pop_front();
	}
}

TEST_F(BinarySearchTreeTest, DeleteWithTwoChildren) {
	binary_search_tree->DeleteElement(310);
	int buf[8] = { 100, 80, 356, 56, 84, 218, 418, 30 };
	int i = 0;
	list<BinarySearchTreeElement> lis;
	lis.push_back(*(binary_search_tree->GetRoot()));
	while (!lis.empty()) {
		EXPECT_EQ(buf[i], lis.front().GetKey());
		i++;
		if ((lis.front()).GetLeft())
			lis.push_back(*((lis.front()).GetLeft()));
		if ((lis.front()).GetRight())
			lis.push_back(*((lis.front()).GetRight()));
		lis.pop_front();
	}
}

TEST_F(BinarySearchTreeTest, NotFound) {
	EXPECT_EQ(NULL, binary_search_tree->SearchElement(4376));
}

TEST_F(BinarySearchTreeTest, SearchInEmpty) {
	BinarySearchTree* bst = new BinarySearchTree();
	EXPECT_EQ(NULL, bst->SearchElement(4376));
}

TEST_F(BinarySearchTreeTest, SearchLower) {
	EXPECT_EQ(55, (binary_search_tree->SearchElement(30))->GetValue());
}

TEST_F(BinarySearchTreeTest, SearchRoot) {
	EXPECT_EQ(84, (binary_search_tree->SearchElement(100))->GetValue());
}

TEST_F(BinarySearchTreeTest, SearchMid) {
	EXPECT_EQ(111, (binary_search_tree->SearchElement(80))->GetValue());
}

TEST_F(BinarySearchTreeTest, MinInEmpty) {
	BinarySearchTree* bst = new BinarySearchTree();
	EXPECT_EQ(NULL, bst->GetMin());
}

TEST_F(BinarySearchTreeTest, SearchMin) {
	EXPECT_EQ(55, (binary_search_tree->GetMin())->GetValue());
}

TEST_F(BinarySearchTreeTest, MaxInEmpty) {
	BinarySearchTree* bst = new BinarySearchTree();
	EXPECT_EQ(NULL, bst->GetMax());
}

TEST_F(BinarySearchTreeTest, SearchMax) {
	EXPECT_EQ(175, (binary_search_tree->GetMax())->GetValue());
}