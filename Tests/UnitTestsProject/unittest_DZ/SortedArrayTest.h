#pragma once
#include "gtest\gtest.h"
#include "elements.h"
#include "SortedArray.h"

class SortedArrayTest : public testing::Test {
protected:
	SortedArray* sorted_array;
	void SetUp();
	void TearDown();
};