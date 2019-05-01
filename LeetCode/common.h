#pragma once

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include<iomanip>
#include <algorithm>
using namespace std;

//打印一维容器
template<typename T>
void printV(const T &t)
{
	for (auto iter = t.cbegin(); iter != t.cend(); ++iter) {
		std::cout << *iter << std::ends;
	}
	std::cout << std::endl;
}

//打印二维容器
template<typename T>
void printV2(const T &t)
{
	for (auto iter1 = t.cbegin(); iter1 != t.cend(); ++iter1) {
		for (auto iter = iter1->cbegin(); iter != iter1->cend(); ++iter) {
			std::cout << setw(4) << setfill(' ') << *iter << std::ends;
		}
		std::cout << std::endl;
	}
}

//链表结点
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};


//打印链表
void printList(ListNode *head) {
	while (head)
	{
		std::cout << head->val << "->";
		head = head->next;
	}
	std::cout << std::endl;
}

template<typename T>
void print(const T &t)
{
	std::cout << t << std::endl;
}

void trimLeftTrailingSpaces(string &input) {
	input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
		return !isspace(ch);
	}));
}

void trimRightTrailingSpaces(string &input) {
	input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
		return !isspace(ch);
	}).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
	vector<int> output;
	trimLeftTrailingSpaces(input);
	trimRightTrailingSpaces(input);
	input = input.substr(1, input.length() - 2);
	stringstream ss;
	ss.str(input);
	string item;
	char delim = ',';
	while (getline(ss, item, delim)) {
		output.push_back(stoi(item));
	}
	return output;
}

ListNode* stringToListNode(string input) {
	// Generate list from the input
	vector<int> list = stringToIntegerVector(input);

	// Now convert that list into linked list
	ListNode* dummyRoot = new ListNode(0);
	ListNode* ptr = dummyRoot;
	for (int item : list) {
		ptr->next = new ListNode(item);
		ptr = ptr->next;
	}
	ptr = dummyRoot->next;
	delete dummyRoot;
	return ptr;
}

string listNodeToString(ListNode* node) {
	if (node == nullptr) {
		return "[]";
	}

	string result;
	while (node) {
		result += to_string(node->val) + ", ";
		node = node->next;
	}
	return "[" + result.substr(0, result.length() - 2) + "]";
}

template<typename T>
bool operator==(const vector<vector<T>> &v1,const  vector<vector<T>> &v2) {
	if (v1.size() != v2.size()) return false;

	for (int i = 0; i < v1.size(); ++i) {
		if (v1[i] != v2[i]) {
			return false;
		}
	}
	return true;
}