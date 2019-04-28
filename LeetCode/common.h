#pragma once

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
