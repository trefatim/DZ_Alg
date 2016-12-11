#include "SortedArrayTest.h"

void SortedArrayTest::SetUp() {
	sorted_array = new SortedArray();
	sorted_array->AddElement(*(new Element(6, 22)));
	sorted_array->AddElement(*(new Element(14, 431)));
	sorted_array->AddElement(*(new Element(24, 98)));
	sorted_array->AddElement(*(new Element(49, 58)));
	sorted_array->AddElement(*(new Element(78, 72)));
	sorted_array->AddElement(*(new Element(94, 44)));
}

void SortedArrayTest::TearDown() {
	delete sorted_array;
}

TEST_F(SortedArrayTest, AddInEmtyArray) {
	SortedArray* arr = new SortedArray();
	Element* element = new Element(1, 2);
	arr->AddElement(*element);
	EXPECT_EQ(element->GetKey(), (*arr)[0].GetKey());
}

TEST_F(SortedArrayTest, AddInBegin) {
	Element* element = new Element(1, 2);
	sorted_array->AddElement(*element);
	EXPECT_EQ(element->GetKey(), (*sorted_array)[0].GetKey());
}

TEST_F(SortedArrayTest, AddInEnd) {
	Element* element = new Element(1000, 2);
	sorted_array->AddElement(*element);
	EXPECT_EQ(element->GetKey(), (*sorted_array)[sorted_array->GetSize() - 1].GetKey());
}

TEST_F(SortedArrayTest, AddInMid) {
	Element* element = new Element(36, 2);
	sorted_array->AddElement(*element);
	EXPECT_EQ(element->GetKey(), (*sorted_array)[3].GetKey());
}

TEST_F(SortedArrayTest, NotFoundToBeDeleted) {
	EXPECT_EQ(0, sorted_array->DeleteElement(12333));
}

TEST_F(SortedArrayTest, DeleteFromEmpty) {
	SortedArray* arr = new SortedArray();
	EXPECT_EQ(0, arr->DeleteElement(12333));
}

TEST_F(SortedArrayTest, DeleteFromBegin) {
	sorted_array->DeleteElement(6);
	int buf[5] = { 14, 24, 49, 78, 94 };
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(buf[i], (*sorted_array)[i].GetKey());
	}
}

TEST_F(SortedArrayTest, DeleteFromEnd) {
	sorted_array->DeleteElement(94);
	int buf[5] = { 6, 14, 24, 49, 78 };
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(buf[i], (*sorted_array)[i].GetKey());
	}
}

TEST_F(SortedArrayTest, DeleteFromMid) {
	sorted_array->DeleteElement(14);
	int buf[5] = { 6, 24, 49, 78, 94 };
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(buf[i], (*sorted_array)[i].GetKey());
	}
}

TEST_F(SortedArrayTest, NotFound) {
	EXPECT_EQ(NULL, sorted_array->SearchElement(12333));
}

TEST_F(SortedArrayTest, SearchInEmpty) {
	SortedArray* sorted = new SortedArray();
	EXPECT_EQ(NULL, sorted->SearchElement(12333));
}

TEST_F(SortedArrayTest, SearchBegin) {
	EXPECT_EQ(22, (sorted_array->SearchElement(6))->GetValue());
}

TEST_F(SortedArrayTest, SearchEnd) {
	EXPECT_EQ(44, (sorted_array->SearchElement(94))->GetValue());
}

TEST_F(SortedArrayTest, SearchMid) {
	EXPECT_EQ(98, (sorted_array->SearchElement(24))->GetValue());
}

TEST_F(SortedArrayTest, SearchMinInEmpty) {
	SortedArray* arr = new SortedArray();
	EXPECT_EQ(NULL, arr->GetMin());
}

TEST_F(SortedArrayTest, SearchMaxInEmpty) {
	SortedArray* arr = new SortedArray();
	EXPECT_EQ(NULL, arr->GetMax());
}

TEST_F(SortedArrayTest, SearchMin) {
	EXPECT_EQ(22, (sorted_array->GetMin())->GetValue());
}

TEST_F(SortedArrayTest, SearchMax) {
	EXPECT_EQ(44, (sorted_array->GetMax())->GetValue());
}