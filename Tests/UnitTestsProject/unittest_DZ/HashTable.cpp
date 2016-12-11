#include "HashTable.h"
#include <iostream>

#define HashTableSize 10

using namespace std;

HashTable::HashTable() {
	table = new HashTableElement*[HashTableSize];
	for (int i = 0; i < HashTableSize; ++i)
		table[i] = NULL;
}

HashTable::~HashTable() {
	delete[] table;
}

int HashTable::HashFunction(int key) {
	return key % HashTableSize;
}

void HashTable::AddElement(HashTableElement& element) {
	int index = HashFunction(element.GetKey());
	if (!table[index])
		table[index] = &element;
	else {
		element.SetNext(*table[index]);
		table[index] = &element;
	}
}

int HashTable::DeleteElement(int key) {
	int index = HashFunction(key);
	HashTableElement* temp = table[index];
	if (!temp) {
		//cout << "element not found" << endl;
		return 0;
	}
	HashTableElement* prev = NULL;
	while (temp) {
		if (temp->GetKey() == key) {
			if (!prev)
				table[index] = temp->GetNext();
			else
				prev->SetNext(*(temp->GetNext()));
			return 1;
		}
		prev = temp;
		temp = temp->GetNext();
	}
	return 0;
}

HashTableElement* HashTable::SearchElement(int key) {
	int index = HashFunction(key);
	HashTableElement* temp = table[index];
	if (!temp) {
		cout << "element not found" << endl;
		return NULL;
	}
	HashTableElement* prev = NULL;
	while (temp) {
		if (temp->GetKey() == key) {
			return temp;
		}
		prev = temp;
		temp = temp->GetNext();
	}
	return NULL;
}

HashTableElement* HashTable::GetMax() {
	int max;
	HashTableElement* temp;
	HashTableElement* buf = NULL;
	for (int i = 0; i < HashTableSize; ++i) {
		if (table[i]) {
			max = table[i]->GetKey();
			buf = table[i];
			break;
		}
	}
	if (!buf) {
		//cout << "there's no any elements" << endl;
		return NULL;
	}

	for (int i = 0; i < HashTableSize; ++i) {
		if (table[i]) {
			temp = table[i];
			while (temp) {
				if (temp->GetKey() > max) {
					max = temp->GetKey();
					buf = temp;
				}
				temp = temp->GetNext();
			}
		}
	}
	return buf;
}

HashTableElement* HashTable::GetMin() {
	int min;
	HashTableElement* temp;
	HashTableElement* buf = NULL;
	for (int i = 0; i < HashTableSize; ++i) {
		if (table[i]) {
			min = table[i]->GetKey();
			buf = table[i];
			break;
		}
	}
	if (!buf) {
		//cout << "there's no any elements" << endl;
		return NULL;
	}

	for (int i = 0; i < HashTableSize; ++i) {
		if (table[i]) {
			temp = table[i];
			while (temp) {
				if (temp->GetKey() < min) {
					min = temp->GetKey();
					buf = temp;
				}
				temp = temp->GetNext();
			}
		}
	}
	return buf;
}

void HashTable::Show(ofstream& fout) {
	fout << "Hash table structure:" << endl;
	HashTableElement* temp;
	for (int i = 0; i < HashTableSize; ++i) {
		if (table[i]) {
			temp = table[i];
			while (temp) {
				fout << "(" << temp->GetKey() << "," << temp->GetValue() << ")" << "->";
				temp = temp->GetNext();
			}
			fout << "NULL" << endl;
		}
		else
			fout << "NULL" << endl;
	}
	fout << endl;
}

HashTableElement* HashTable::GetListCopy(HashTableElement* pEnd) {
	if (!pEnd)
		return NULL;

	HashTableElement* resultEnd = new HashTableElement(pEnd->GetKey(), pEnd->GetValue());
	pEnd = pEnd->GetNext();
	HashTableElement* temp = resultEnd;
	HashTableElement* buf;
	while (pEnd) {
		buf = new HashTableElement(pEnd->GetKey(), pEnd->GetValue());
		temp->SetNext(*buf);
		temp = temp->GetNext();
		pEnd = pEnd->GetNext();
	}
	return resultEnd;
}

HashTable* HashTable::GetHashTableCopy() {
	HashTable* result = new HashTable();
	for (int i = 0; i < HashTableSize; ++i) {
		result->table[i] = GetListCopy(table[i]);
	}
	return result;
}

HashTableElement* HashTable::operator[](int i) {
	return table[i];
}