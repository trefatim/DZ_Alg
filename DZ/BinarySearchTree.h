#pragma once
#include "elements.h"
#include <fstream>

using namespace std;

class BinarySearchTree {
	BinarySearchTreeElement* root;
public:
	BinarySearchTree();
	void AddElement(BinarySearchTreeElement& element);
	int DeleteElement(int key); //0 - элемент не найден, 1 - успешно удален
	BinarySearchTreeElement* SearchElement(int key);
	BinarySearchTreeElement* GetMax();
	BinarySearchTreeElement* GetMin();
	BinarySearchTreeElement* GetRoot();
	void Show(ofstream& fout);
	BinarySearchTree* GetTreeCopy();
};