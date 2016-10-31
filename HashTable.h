#pragma once
#include "stdafx.h"
#include "elements.h"
#include <fstream>

using namespace std;

class HashTable {
	HashTableElement** table;
public:
	HashTable();
	~HashTable();
	int HashFunction(int key);
	void AddElement(HashTableElement& element);
	int DeleteElement(int key); //0 - элемент не найден, 1 - успешно удален
	HashTableElement* SearchElement(int key);
	HashTableElement* GetMax();
	HashTableElement* GetMin();
	void Show(ofstream& fout);
};