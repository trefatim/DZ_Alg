#include "stdafx.h"
#include "BinarySearchTree.h"
#include <iostream>
#include <list>

using namespace std;

BinarySearchTree::BinarySearchTree() {
	root = NULL;
}

void BinarySearchTree::AddElement(BinarySearchTreeElement& element) {
	BinarySearchTreeElement* buf = NULL;
	BinarySearchTreeElement* temp = root;
	while (temp) {
		buf = temp;
		if (element.GetKey() < temp->GetKey())
			temp = temp->GetLeft();
		else
			temp = temp->GetRight();
	}
	element.SetParent(buf);
	if (!buf)
		root = &element;
	else if (element.GetKey() < buf->GetKey())
		buf->SetLeft(&element);
	else
		buf->SetRight(&element);
}

BinarySearchTreeElement* BinarySearchTree::SearchElement(int key) {
	BinarySearchTreeElement* temp = root;
	while (temp && key != temp->GetKey()) {
		if (key < temp->GetKey())
			temp = temp->GetLeft();
		else
			temp = temp->GetRight();		
	}
	return temp;
}

BinarySearchTreeElement* BinarySearchTree::GetMax() {
	if (!root)
		return NULL;
	BinarySearchTreeElement* temp = root;
	while (temp->GetRight())
		temp = temp->GetRight();
	return temp;
}

BinarySearchTreeElement* BinarySearchTree::GetMin() {
	if (!root)
		return NULL;
	BinarySearchTreeElement* temp = root;
	while (temp->GetLeft())
		temp = temp->GetLeft();
	return temp;
}

int BinarySearchTree::DeleteElement(int key) {
	BinarySearchTreeElement* element = SearchElement(key);
	BinarySearchTreeElement* buf;
	BinarySearchTreeElement* child;
	if (element) {
		if (!(element->GetLeft()) || !(element->GetRight()))
			buf = element;
		else {
			BinarySearchTreeElement* temp = element->GetRight();
			while (temp->GetLeft())
				temp = temp->GetLeft();
			buf = temp;
		}
		if (buf->GetLeft())
			child = buf->GetLeft();
		else
			child = buf->GetRight();
		if (child)
			(child->GetParent())->SetParent(buf->GetParent());
		if (!(buf->GetParent()))
			root = child;
		else if (buf == (buf->GetParent())->GetLeft())
			(buf->GetParent())->SetLeft(child);
		else
			(buf->GetParent())->SetRight(child);
		if (buf != element) {
			element->SetKey(buf->GetKey());
			element->SetValue(buf->GetValue());
		}
		return 1;
	}
	return 0;
}

/*BinarySearchTreeElement* BinarySearchTree::GetRoot() {
	return root;
}*/

void BinarySearchTree::Show(ofstream& fout) {
	fout << "Binary search tree structure:" << endl;
	list<BinarySearchTreeElement> list;
	if (!root) {
		fout << "there's no elements" << endl;
		return;
	}
	list.push_back(*root);
	int indicator = 10;
	while (!list.empty()) {
		if ((list.front()).GetLeft() && (list.front()).GetRight()) {
			fout << (list.front()).GetKey() << "-" << (list.front()).GetValue() <<
				"(Left:" << ((list.front()).GetLeft())->GetKey() << ", Right:"
				<< ((list.front()).GetRight())->GetKey() << "); ";
		} 
		else if (!(list.front()).GetLeft() && (list.front()).GetRight()) {
			fout << (list.front()).GetKey() << "-" << (list.front()).GetValue()
				<< "(Left:NULL" << ", Right:" << ((list.front()).GetRight())->GetKey() << "); ";
		}
		else if ((list.front()).GetLeft() && !(list.front()).GetRight()) {
			fout << (list.front()).GetKey() << "-" << (list.front()).GetValue()
				<< "(Left:" << ((list.front()).GetLeft())->GetKey()	<< ", Right:NULL); ";
		}
		else if (!(list.front()).GetLeft() && !(list.front()).GetRight()) {
			fout << (list.front()).GetKey() << "-" << (list.front()).GetValue() << "(Left:NULL, Right:NULL); ";
		}
		indicator--;
		if (!indicator) {
			fout << endl;
			indicator = 10;
		}
		if ((list.front()).GetLeft())
			list.push_back(*((list.front()).GetLeft()));
		if ((list.front()).GetRight())
			list.push_back(*((list.front()).GetRight()));
		list.pop_front();
	}
	fout << endl; fout << endl;	
}