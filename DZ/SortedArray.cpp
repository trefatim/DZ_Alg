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

void SortedArray::Insert(int index, Element& element) {
	Element buf1 = sorted_array[index];
	Element buf2;
	sorted_array[index] = element;
	for (int i = index + 1; i < size; ++i) {
		buf2 = sorted_array[i];
		sorted_array[i] = buf1;
		buf1 = buf2;
	}
	sorted_array[size] = buf1;
	size++;
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

	if (!size) {
		sorted_array[size] = element;
		size++;
		return;
	}

	if (element.GetKey() > sorted_array[size - 1].GetKey()) {
		sorted_array[size] = element;
		size++;
		return;
	}

	int down = 0;
	int up = size - 1;
	int mid;
	while (down <= up) {
		mid = (down + up) / 2;
		if (sorted_array[mid].GetKey() < element.GetKey()) {
			if (mid + 1 != size) {
				if (sorted_array[mid + 1].GetKey() > element.GetKey()) {
					Insert(mid + 1, element);
					return;
				}
				down = mid + 1;
			}
			else {
				sorted_array[size] = element;
				size++;
				return;
			}
		}
		else {
			if (mid) {
				if (sorted_array[mid - 1].GetKey() < element.GetKey()) {
					Insert(mid, element);
					return;
				}
				up = mid - 1;
			}
			else {
				Insert(mid, element);
				return;
			}
		}
	}
}

int SortedArray::DeleteElement(int key) {
	if (!size)
		return 0;
	int down = 0;
	int up = size - 1;
	int mid;
	while (down <= up) {
		mid = (down + up) / 2;
		if (sorted_array[mid].GetKey() == key) {
			for (int i = mid; i < size - 1; ++i) {
				sorted_array[i] = sorted_array[i + 1];
			}
			size--;
			return 1;
		}
		if (sorted_array[mid].GetKey() < key)
			down = mid + 1;
		if (sorted_array[mid].GetKey() > key)
			up = mid - 1;
	}
	return 0;
}

Element* SortedArray::SearchElement(int key) {
	if (!size)
		return NULL;
	int down = 0;
	int up = size - 1;
	int mid;
	while (down <= up) {
		mid = (down + up) / 2;
		if (sorted_array[mid].GetKey() == key)
			return &sorted_array[mid];
		if (sorted_array[mid].GetKey() < key)
			down = mid + 1;
		if (sorted_array[mid].GetKey() > key)
			up = mid - 1;
	}
	return NULL;
}

Element* SortedArray::GetMax() {
	if (size)
		return &sorted_array[size - 1];
	return NULL;
}

Element* SortedArray::GetMin() {
	if (size)
		return &sorted_array[0];
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

SortedArray* SortedArray::GetArrayCopy() {
	SortedArray* result = new SortedArray();
	for (int i = 0; i < size; ++i) {
		result->AddElement(sorted_array[i]);
	}
	return result;
}

int SortedArray::GetSize() {
	return size;
}

Element& SortedArray::operator[](int i) {
	return sorted_array[i];
}