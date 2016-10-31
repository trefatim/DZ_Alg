#include "stdafx.h"
#include "elements.h"
#include <iostream>

using namespace std;

// Методы элементов массива
Element::Element(int key, int value) {
	this->key = key;
	this->value = value;
}

Element::Element() {}

int Element::GetKey() {
	return key;
}

int Element::GetValue() {
	return value;
}

// Методы элементов хэш-таблицы
HashTableElement::HashTableElement(int key, int value) : Element(key, value) {
	next = NULL;
}

HashTableElement::HashTableElement() {
	next = NULL;
}

void HashTableElement::SetNext(HashTableElement& element) {
	next = &element;
}

HashTableElement* HashTableElement::GetNext() {
	return next;
}

// Методы двоичного дерева поиска
BinarySearchTreeElement::BinarySearchTreeElement(int key, int value) : Element(key, value) {
	left = NULL;
	right = NULL;
	parent = NULL;
}

BinarySearchTreeElement::BinarySearchTreeElement() {
	left = NULL;
	right = NULL;
	parent = NULL;
}

BinarySearchTreeElement* BinarySearchTreeElement::GetLeft() {
	return left;
}

BinarySearchTreeElement* BinarySearchTreeElement::GetRight() {
	return right;
}

BinarySearchTreeElement* BinarySearchTreeElement::GetParent() {
	return parent;
}

void BinarySearchTreeElement::SetLeft(BinarySearchTreeElement* element) {
	left = element;
}

void BinarySearchTreeElement::SetRight(BinarySearchTreeElement* element) {
	right = element;
}

void BinarySearchTreeElement::SetParent(BinarySearchTreeElement* element) {
	parent = element;
}

void BinarySearchTreeElement::SetKey(int key) {
	this->key = key;
}

void BinarySearchTreeElement::SetValue(int value) {
	this->value = value;
}

int BinarySearchTreeElement::GetKey() {
	return key;
}

int BinarySearchTreeElement::GetValue() {
	return value;
}