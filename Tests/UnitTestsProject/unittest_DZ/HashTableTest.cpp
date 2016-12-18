#include "HashTableTest.h"

void HashTableTest::SetUp() {
	hash_table = new HashTable();
	hash_table->AddElement(*(new HashTableElement(33, 43)));
	hash_table->AddElement(*(new HashTableElement(46, 468)));
	hash_table->AddElement(*(new HashTableElement(13, 212)));
	hash_table->AddElement(*(new HashTableElement(26, 144)));
	hash_table->AddElement(*(new HashTableElement(73, 67)));
	hash_table->AddElement(*(new HashTableElement(112, 113)));
	hash_table->AddElement(*(new HashTableElement(20, 113)));
}

void HashTableTest::TearDown() {
	delete hash_table;
}

TEST_F(HashTableTest, AddInEmptyList) {
	HashTable* table = new HashTable();
	table->AddElement(*(new HashTableElement(36, 123)));
	EXPECT_EQ(123, (*table)[10]->GetValue());
}

TEST_F(HashTableTest, AddTest) {
	hash_table->AddElement(*(new HashTableElement(26, 123)));
	EXPECT_EQ(123, (*hash_table)[0]->GetValue());
}

TEST_F(HashTableTest, DeleteFromEmptyList) {
	EXPECT_EQ(0, hash_table->DeleteElement(1000));
}

TEST_F(HashTableTest, NotFoundToBeDeleted) {
	EXPECT_EQ(0, hash_table->DeleteElement(333));
}

TEST_F(HashTableTest, DeleteListHead) {
	hash_table->DeleteElement(20);
	int buf[3] = { 46, 33 };
	int i = 0;
	HashTableElement* element = (*hash_table)[7];
	do {
		EXPECT_EQ(buf[i], element->GetKey());
		i++;
		element = element->GetNext();
	} while (element);
}

TEST_F(HashTableTest, DeleteListEnd) {
	hash_table->DeleteElement(33);
	int buf[3] = { 20, 46 };
	int i = 0;
	HashTableElement* element = (*hash_table)[7];
	do {
		EXPECT_EQ(buf[i], element->GetKey());
		i++;
		element = element->GetNext();
	} while (element);
}

TEST_F(HashTableTest, DeleteListMid) {
	hash_table->DeleteElement(46);
	int buf[3] = { 20, 33 };
	int i = 0;
	HashTableElement* element = (*hash_table)[7];
	do {
		EXPECT_EQ(buf[i], element->GetKey());
		i++;
		element = element->GetNext();
	} while (element);
}

TEST_F(HashTableTest, NotFound) {
	EXPECT_EQ(NULL, hash_table->SearchElement(154444));
}

TEST_F(HashTableTest, SearchInEmptyList) {
	EXPECT_EQ(NULL, hash_table->SearchElement(30));
}

TEST_F(HashTableTest, SearchInBeginList) {
	EXPECT_EQ(113, (hash_table->SearchElement(20))->GetValue());
}

TEST_F(HashTableTest, SearchInEndList) {
	EXPECT_EQ(43, (hash_table->SearchElement(33))->GetValue());
}

TEST_F(HashTableTest, SearchInMidList) {
	EXPECT_EQ(468, (hash_table->SearchElement(46))->GetValue());
}

TEST_F(HashTableTest, SearchMinInEmptyTable) {
	HashTable* ht = new HashTable();
	EXPECT_EQ(NULL, ht->GetMin());
}

TEST_F(HashTableTest, SearchMin) {
	EXPECT_EQ(212, (hash_table->GetMin())->GetValue());
}

TEST_F(HashTableTest, SearchMaxInEmptyTable) {
	HashTable* ht = new HashTable();
	EXPECT_EQ(NULL, ht->GetMax());
}

TEST_F(HashTableTest, SearchMax) {
	EXPECT_EQ(113, (hash_table->GetMax())->GetValue());
}