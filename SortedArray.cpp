#include "stdafx.h"
#include "SortedArray.h"
#include <iostream>

#define StartCapacity 10
#define K 2

using namespace std;

SortedArray::SortedArray() {
	sorted_array = new Element[StartCapacity];
	capacity = StartCapacity;
	size = 0;
}

SortedArray::~SortedArray() {
	delete sorted_array;
}

void SortedArray::AddElement(Element& element) {
	if (capacity == size) {
		Element* buf = new Element[K*capacity];
		for (int i = 0; i < size; ++i) {
			buf[i] = sorted_array[i];
		}
		capacity *= K;
		delete sorted_array;
		sorted_array = buf;
	}
	for (int i = 0; i < size - 1; ++i) {
		if (sorted_array[i].GetKey() < element.GetKey()) {
			if (sorted_array[i + 1].GetKey() > element.GetKey()) {
				Element buf1 = sorted_array[i + 1];
				Element buf2;
				sorted_array[i + 1] = element;
				for (int j = i + 2; j < size; ++j) {
					buf2 = sorted_array[j];
					sorted_array[j] = buf1;
					buf1 = buf2;
				}
				sorted_array[size] = buf1;
				size++;
				return;
			}
		}
		else {
			Element buf1 = sorted_array[i];
			Element buf2;
			sorted_array[i] = element;
			for (int j = i + 1; j < size; ++j) {
				buf2 = sorted_array[j];
				sorted_array[j] = buf1;
				buf1 = buf2;
			}
			sorted_array[size] = buf1;
			size++;
			return;
		}
	}
	sorted_array[size] = element;
	size++;
}

int SortedArray::DeleteElement(int key) {
	if (!size)
		return 0;
	if (size == 1) {
		size--;
		return 1;
	}
	int low = 0;
	int high = size - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (sorted_array[mid].GetKey() == key) {
			for (int i = mid; i < size - 1; ++i)
				sorted_array[i] = sorted_array[i + 1];
			size--;
			return 1;
		}
		if (sorted_array[mid].GetKey() < key)
			low = mid + 1;
		if (sorted_array[mid].GetKey() > key)
			high = mid - 1;
	}
	if (sorted_array[high].GetKey() == key) {
		for (int i = high; i < size - 1; ++i)
			sorted_array[i] = sorted_array[i + 1];
		size--;
		return 1;
	}
	else
		return 0;
}

Element* SortedArray::SearchElement(int key) {
	if (!size)
		return NULL;
	if (size == 1)
		return &sorted_array[0];
	int low = 0;
	int high = size - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (sorted_array[mid].GetKey() == key)
			return &sorted_array[mid];
		if (sorted_array[mid].GetKey() < key)
			low = mid + 1;
		if (sorted_array[mid].GetKey() > key)
			high = mid - 1;
	}
	if (sorted_array[high].GetKey() == key)
		return &sorted_array[high];
	else
		return NULL;
}

Element* SortedArray::GetMax() {
	if (size)
		return &sorted_array[size - 1];
	//cout << "there's no any elements" << endl;
	return NULL;
}

Element* SortedArray::GetMin() {
	if (size)
		return &sorted_array[0];
	//cout << "there's no any elements" << endl;
	return NULL;
}

void SortedArray::Show(ofstream& fout) {
	fout << "Sorted array structure:" << endl;
	if (!size) {
		fout << "there's no any elements" << endl;
		return;
	}
	for (int i = 0; i < size; ++i)
		fout << "(" << sorted_array[i].GetKey() << "," << sorted_array[i].GetValue() << ") ";
	fout << endl; fout << endl;	
}