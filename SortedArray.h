#pragma once
#include "stdafx.h"
#include "elements.h"
#include <fstream>

using namespace std;

class SortedArray {
	Element* sorted_array;
	int size, capacity;
public:
	SortedArray();
	~SortedArray();
	void AddElement(Element& element);
	int DeleteElement(int key); //0 - ������� �� ������, 1 - ������� ������
	Element* SearchElement(int key);
	Element* GetMax();
	Element* GetMin();
	void Show(ofstream& fout);
};