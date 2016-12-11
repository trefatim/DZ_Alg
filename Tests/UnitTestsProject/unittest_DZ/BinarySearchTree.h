#pragma once
#include "elements.h"
#include <fstream>

using namespace std;

class BinarySearchTree {
	BinarySearchTreeElement* root;
public:
	BinarySearchTree();
	void AddElement(BinarySearchTreeElement& element);
	int DeleteElement(int key); //0 - ������� �� ������, 1 - ������� ������
	BinarySearchTreeElement* SearchElement(int key);
	BinarySearchTreeElement* GetMax();
	BinarySearchTreeElement* GetMin();
	BinarySearchTreeElement* GetRoot();
	void Show(ofstream& fout);
	BinarySearchTree* GetTreeCopy();
};