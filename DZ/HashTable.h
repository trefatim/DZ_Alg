#pragma once
#include "elements.h"
#include <fstream>

using namespace std;

class HashTable {
	HashTableElement** table;
	HashTableElement* GetListCopy(HashTableElement* pEnd);
	int HashFunction(int key);
public:
	HashTable();
	~HashTable();
	void AddElement(HashTableElement& element);
	int DeleteElement(int key); //0 - элемент не найден, 1 - успешно удален
	HashTableElement* SearchElement(int key);
	HashTableElement* GetMax();
	HashTableElement* GetMin();
	void Show(ofstream& fout);
	HashTable* GetHashTableCopy();
	HashTableElement* operator[](int i);
};