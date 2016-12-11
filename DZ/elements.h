#pragma once

using namespace std;

class Element {
protected:
	int key, value;

public:
	Element();
	Element(int key, int value);
	int GetKey();
	int GetValue();
};

class HashTableElement : public Element {
	HashTableElement* next;
public:
	HashTableElement(int key, int value);
	HashTableElement();
	void SetNext(HashTableElement& element);
	HashTableElement* GetNext();
};

class BinarySearchTreeElement : public Element {
	BinarySearchTreeElement* left;
	BinarySearchTreeElement* right;
	BinarySearchTreeElement* parent;
public:
	BinarySearchTreeElement(int key, int value);
	BinarySearchTreeElement();
	BinarySearchTreeElement* GetLeft();
	BinarySearchTreeElement* GetRight();
	BinarySearchTreeElement* GetParent();
	void SetLeft(BinarySearchTreeElement* element);
	void SetRight(BinarySearchTreeElement* element);
	void SetParent(BinarySearchTreeElement* element);
	void SetKey(int key);
	void SetValue(int value);
	int GetValue();
	int GetKey();
};