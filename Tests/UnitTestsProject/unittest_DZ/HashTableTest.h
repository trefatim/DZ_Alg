#pragma once
#include "gtest\gtest.h"
#include "elements.h"
#include "HashTable.h"

class HashTableTest : public testing::Test {
protected:
	HashTable* hash_table;
	void SetUp();
	void TearDown();
};