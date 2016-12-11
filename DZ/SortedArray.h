#pragma once
#include "elements.h"
#include <fstream>

using namespace std;

class SortedArray {
	Element* sorted_array;
	int size, capacity;
	void Insert(int index, Element& element);
public:
	SortedArray();
	~SortedArray();
	void AddElement(Element& element);
	int DeleteElement(int key); //0 - элемент не найден, 1 - успешно удален
	Element* SearchElement(int key);
	Element* GetMax();
	Element* GetMin();
	void Show(ofstream& fout);
	SortedArray* GetArrayCopy();
	int GetSize();
	Element& operator[](int i);
};
