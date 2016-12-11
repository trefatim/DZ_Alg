#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
//#include <Windows.h>
#include <chrono>
#include "elements.h"
#include "HashTable.h"
#include "SortedArray.h"
#include "BinarySearchTree.h"

using namespace std;

bool IsInt(string str) {
	int temp = 0;
	if (str == "0")
		return true;
	else
		temp = atoi(str.c_str());
	if (!temp)
		return false;
	else
		return true;
}

int StringToInt(string str) {
	if (str == "0") {
		return 0;
	}
	istringstream ss(str);
	int a;
	ss >> a;
	return a;
}

vector<string> CommandInParts(string command) {
	string command_part;
	stringstream ss(command);
	vector <string> command_array;
	while (ss >> command_part)
		command_array.push_back(command_part);
	return command_array;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
		return 0;
	HashTable* hash_table = new HashTable();
	SortedArray* sorted_array = new SortedArray();
	BinarySearchTree* binary_search_tree = new BinarySearchTree();

	HashTableElement* ht_element;
	Element* sa_element;
	BinarySearchTreeElement* bst_element;

	//__int64 start, end, tps;
	int result_time = 0;
	//QueryPerformanceFrequency((LARGE_INTEGER *)&tps);

	int element_key, element_value;
	string command, command_part;
	string* p;
	vector <string> command_array;

	ofstream fout(argv[2], ios::out | ios::trunc);
	if (!fout.is_open()) {
		return 1;
	}

	ifstream fin(argv[1], ios::in);
	if (!fin.is_open()) {
		fout << "error opening file" << endl;;
		return 1;
	}
	fin.seekg(0);

	while (!fin.eof()) {
		getline(fin, command);
		if (!command.empty()) {
			command_array = CommandInParts(command);
			if (command_array.size()) {
				if (command_array.front() == "add") {
					command_array.erase(command_array.begin());
					p = command_array.data();
					if (command_array.size() == 2) {
						if (IsInt(p[0]) && IsInt(p[1])) {
							element_key = StringToInt(p[0]);
							element_value = StringToInt(p[1]);
							ht_element = new HashTableElement(element_key, element_value);
							sa_element = new Element(element_key, element_value);
							bst_element = new BinarySearchTreeElement(element_key, element_value);

							for (int i = 0; i < 100000; ++i) {
								auto start1 = std::chrono::high_resolution_clock::now();
								hash_table->AddElement(*ht_element);
								auto stop1 = std::chrono::high_resolution_clock::now();
								result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
								hash_table->DeleteElement(ht_element->GetKey());
							}
							hash_table->AddElement(*ht_element);
							fout << "element (" << element_key << ", " << element_value << ") was added to hash table over " << (result_time) / 100000 << " ns" << endl;
							result_time = 0;

							//QueryPerformanceCounter((LARGE_INTEGER *)&start);
							for (int i = 0; i < 100000; ++i) {
								auto start1 = std::chrono::high_resolution_clock::now();
								sorted_array->AddElement(*sa_element);
								auto stop1 = std::chrono::high_resolution_clock::now();
								result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
								sorted_array->DeleteElement(sa_element->GetKey());
							}
							sorted_array->AddElement(*sa_element);
							//QueryPerformanceCounter((LARGE_INTEGER *)&end);
							fout << "element (" << element_key << ", " << element_value << ") was added to sorted array over " << (result_time) / 100000 << " ns" << endl;
							result_time = 0;

							//QueryPerformanceCounter((LARGE_INTEGER *)&start);
							for (int i = 0; i < 100000; ++i) {
								auto start1 = std::chrono::high_resolution_clock::now();
								binary_search_tree->AddElement(*bst_element);
								auto stop1 = std::chrono::high_resolution_clock::now();
								result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
								binary_search_tree->DeleteElement(bst_element->GetKey());
							}
							binary_search_tree->AddElement(*bst_element);
							//QueryPerformanceCounter((LARGE_INTEGER *)&end);
							fout << "element (" << element_key << ", " << element_value << ") was added to binary search tree over " << (result_time) / 100000 << " ns" << endl;
							fout << endl;
							result_time = 0;
						}
						else {
							fout << "wrong key/value in command add" << endl;
							fout << endl;
						}
					}
					else {
						fout << "wrong parameters in command add" << endl;
						fout << endl;
					}
				}
				else if (command_array.front() == "delete") {
					command_array.erase(command_array.begin());
					p = command_array.data();
					if (command_array.size() == 1) {
						if (IsInt(p[0])) {
							element_key = StringToInt(p[0]);
							//QueryPerformanceCounter((LARGE_INTEGER *)&start);
							HashTable* ht_copy = hash_table->GetHashTableCopy();
							HashTable* ht_temp;
							if (hash_table->DeleteElement(element_key)) {
								//QueryPerformanceCounter((LARGE_INTEGER *)&end);
								for (int i = 0; i < 100000; ++i) {
									ht_temp = ht_copy->GetHashTableCopy();
									auto start1 = std::chrono::high_resolution_clock::now();
									ht_temp->DeleteElement(element_key);
									auto stop1 = std::chrono::high_resolution_clock::now();
									result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
									delete ht_temp;
								}
								fout << "element with key " << element_key << " was deleted from hash table over " << (result_time) / 100000 << " ns" << endl;
								result_time = 0;
								delete ht_copy;
							}
							else
								fout << "element with key " << element_key << " wasn't found to be deleted from hash table" << endl;

							//QueryPerformanceCounter((LARGE_INTEGER *)&start);
							SortedArray* sa_copy = sorted_array->GetArrayCopy();
							SortedArray* sa_temp;
							if (sorted_array->DeleteElement(element_key)) {
								//QueryPerformanceCounter((LARGE_INTEGER *)&end);
								for (int i = 0; i < 100000; ++i) {
									sa_temp = sa_copy->GetArrayCopy();
									auto start1 = std::chrono::high_resolution_clock::now();
									sa_temp->DeleteElement(element_key);
									auto stop1 = std::chrono::high_resolution_clock::now();
									result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
									delete sa_temp;
								}
								fout << "element with key " << element_key << " was deleted from sorted array over " << (result_time) / 100000 << " ns" << endl;
								result_time = 0;
								delete sa_copy;
							}
							else
								fout << "element with key " << element_key << " wasn't found to be deleted from sorted array" << endl;

							//QueryPerformanceCounter((LARGE_INTEGER *)&start);
							BinarySearchTree* bst_copy = binary_search_tree->GetTreeCopy();
							BinarySearchTree* bst_temp;
							if (binary_search_tree->DeleteElement(element_key)) {
								//QueryPerformanceCounter((LARGE_INTEGER *)&end);
								for (int i = 0; i < 100000; ++i) {
									bst_temp = bst_copy->GetTreeCopy();
									auto start1 = std::chrono::high_resolution_clock::now();
									bst_temp->DeleteElement(element_key);
									auto stop1 = std::chrono::high_resolution_clock::now();
									result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
									delete bst_temp;
								}
								fout << "element with key " << element_key << " was deleted from binary search tree over " << (result_time) / 100000 << " ns" << endl;
								result_time = 0;
								delete bst_copy;
							}
							else
								fout << "element with key " << element_key << " wasn't found to be deleted from binary search tree" << endl;
							fout << endl;
						}
						else {
							fout << "wrong key in command delete" << endl;
							fout << endl;
						}
					}
					else {
						fout << "wrong parameters in command delete" << endl;
						fout << endl;
					}
				}
				else if (command_array.front() == "search") {
					command_array.erase(command_array.begin());
					p = command_array.data();
					if (command_array.size() == 1) {
						if (IsInt(p[0])) {
							element_key = StringToInt(p[0]);
							//QueryPerformanceCounter((LARGE_INTEGER *)&start);
							ht_element = hash_table->SearchElement(element_key);
							//QueryPerformanceCounter((LARGE_INTEGER *)&end);
							if (ht_element) {
								for (int i = 0; i < 100000; ++i) {
									auto start1 = std::chrono::high_resolution_clock::now();
									ht_element = hash_table->SearchElement(element_key);
									auto stop1 = std::chrono::high_resolution_clock::now();
									result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
								}
								fout << "searching element with key " << element_key << ": in hash table " << ht_element->GetKey() << "-" << ht_element->GetValue()
									<< "over " << (result_time) / 100000 << " ns" << endl;
								result_time = 0;
							}
							else {
								fout << "searching element with key " << element_key << ": in hash table not found;";
								fout << endl;
							}

							//QueryPerformanceCounter((LARGE_INTEGER *)&start);
							sa_element = sorted_array->SearchElement(element_key);
							//QueryPerformanceCounter((LARGE_INTEGER *)&end);
							if (sa_element) {
								for (int i = 0; i < 100000; ++i) {
									auto start1 = std::chrono::high_resolution_clock::now();
									sa_element = sorted_array->SearchElement(element_key);
									auto stop1 = std::chrono::high_resolution_clock::now();
									result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
								}
								fout << "searching element with key " << element_key << ": in sorted array " << sa_element->GetKey() << "-" << sa_element->GetValue()
									<< "over " << (result_time) / 100000 << " ns" << endl;
								result_time = 0;
							}
							else {
								fout << "searching element with key " << element_key << ": in sorted array not found;";
								fout << endl;
							}

							//QueryPerformanceCounter((LARGE_INTEGER *)&start);
							bst_element = binary_search_tree->SearchElement(element_key);
							//QueryPerformanceCounter((LARGE_INTEGER *)&end);
							if (bst_element) {
								for (int i = 0; i < 100000; ++i) {
									auto start1 = std::chrono::high_resolution_clock::now();
									bst_element = binary_search_tree->SearchElement(element_key);
									auto stop1 = std::chrono::high_resolution_clock::now();
									result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
								}
								fout << "searching element with key " << element_key << ": in binary search tree " << bst_element->GetKey() << "-" << bst_element->GetValue()
									<< "over " << (result_time) / 100000 << " ns" << endl;
								result_time = 0;
							}
							else {
								fout << "searching element with key " << element_key << ": in binary search tree not found;";
								fout << endl;
							}
							fout << endl;
						}
						else {
							fout << "wrong key in command search" << endl;
							fout << endl;
						}
					}
					else {
						fout << "wrong parameters in command search" << endl;
						fout << endl;
					}
				}
				else if (command_array.front() == "min") {
					if (command_array.size() == 1) {
						//QueryPerformanceCounter((LARGE_INTEGER *)&start);
						ht_element = hash_table->GetMin();
						//QueryPerformanceCounter((LARGE_INTEGER *)&end);
						if (ht_element) {
							for (int i = 0; i < 100000; ++i) {
								auto start1 = std::chrono::high_resolution_clock::now();
								ht_element = hash_table->GetMin();
								auto stop1 = std::chrono::high_resolution_clock::now();
								result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
							}
							fout << "min: in hash table " << ht_element->GetKey() << "-" << ht_element->GetValue() << " over " << (result_time) / 100000 << " ns" << endl;
							result_time = 0;
						}
						else
							fout << "there's no any elements in hash table;" << endl;

						//QueryPerformanceCounter((LARGE_INTEGER *)&start);
						sa_element = sorted_array->GetMin();
						//QueryPerformanceCounter((LARGE_INTEGER *)&end);
						if (sa_element) {
							for (int i = 0; i < 100000; ++i) {
								auto start1 = std::chrono::high_resolution_clock::now();
								sa_element = sorted_array->GetMin();
								auto stop1 = std::chrono::high_resolution_clock::now();
								result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
							}
							fout << "min: in sorted array " << sa_element->GetKey() << "-" << sa_element->GetValue() << " over " << (result_time) / 100000 << " ns" << endl;
							result_time = 0;
						}
						else
							fout << "there's no any elements in sorted array;" << endl;

						//QueryPerformanceCounter((LARGE_INTEGER *)&start);
						bst_element = binary_search_tree->GetMin();
						//QueryPerformanceCounter((LARGE_INTEGER *)&end);
						if (bst_element) {
							for (int i = 0; i < 100000; ++i) {
								auto start1 = std::chrono::high_resolution_clock::now();
								bst_element = binary_search_tree->GetMin();
								auto stop1 = std::chrono::high_resolution_clock::now();
								result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
							}
							fout << "min: in binary search tree " << bst_element->GetKey() << "-" << bst_element->GetValue() << " over " << (result_time) / 100000 << " ns" << endl;
							result_time = 0;
						}
						else
							fout << "there's no any elements in binary search tree;" << endl;
						fout << endl;
					}
					else {
						fout << "wrong parameters in command min" << endl;
						fout << endl;
					}
				}
				else if (command_array.front() == "max") {
					if (command_array.size() == 1) {
						//QueryPerformanceCounter((LARGE_INTEGER *)&start);
						ht_element = hash_table->GetMax();
						//QueryPerformanceCounter((LARGE_INTEGER *)&end);
						if (ht_element) {
							for (int i = 0; i < 100000; ++i) {
								auto start1 = std::chrono::high_resolution_clock::now();
								ht_element = hash_table->GetMax();
								auto stop1 = std::chrono::high_resolution_clock::now();
								result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
							}
							fout << "max: in hash table " << ht_element->GetKey() << "-" << ht_element->GetValue() << " over " << (result_time) / 100000 << " ns" << endl;
							result_time = 0;
						}
						else
							fout << "there's no any elements in hash table;" << endl;

						//QueryPerformanceCounter((LARGE_INTEGER *)&start);
						sa_element = sorted_array->GetMax();
						//QueryPerformanceCounter((LARGE_INTEGER *)&end);
						if (sa_element) {
							for (int i = 0; i < 100000; ++i) {
								auto start1 = std::chrono::high_resolution_clock::now();
								sa_element = sorted_array->GetMax();
								auto stop1 = std::chrono::high_resolution_clock::now();
								result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
							}
							fout << "max: in sorted array " << sa_element->GetKey() << "-" << sa_element->GetValue() << " over " << (result_time) / 100000 << " ns" << endl;
							result_time = 0;
						}
						else
							fout << "there's no any elements in sorted array;" << endl;

						//QueryPerformanceCounter((LARGE_INTEGER *)&start);
						bst_element = binary_search_tree->GetMax();
						//QueryPerformanceCounter((LARGE_INTEGER *)&end);
						if (bst_element) {
							for (int i = 0; i < 100000; ++i) {
								auto start1 = std::chrono::high_resolution_clock::now();
								bst_element = binary_search_tree->GetMax();
								auto stop1 = std::chrono::high_resolution_clock::now();
								result_time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1).count();
							}
							fout << "max: in binary search tree " << bst_element->GetKey() << "-" << bst_element->GetValue() << " over " << (result_time) / 100000 << " ns" << endl;
							result_time = 0;
						}
						else
							fout << "there's no any elements in binary search tree;" << endl;
						fout << endl;
					}
					else {
						fout << "wrong parameters in command max" << endl;
						fout << endl;
					}
				}
				else if (command_array.front() == "print") {
					if (command_array.size() == 1) {
						hash_table->Show(fout);
						sorted_array->Show(fout);
						binary_search_tree->Show(fout);
					}
					else {
						fout << "wrong parameters in command print" << endl;
						fout << endl;
					}
				}
				else {
					fout << "wrong command: " << command_array.front() << endl;
					fout << endl;
				}
			}
			else {
				fout << "line of spaces or tabulations" << endl;
				fout << endl;
			}
		}
		else {
			fout << "empty line" << endl;
			fout << endl;
		}
	}
	fin.close();
	fout.close();
	return 0;
}