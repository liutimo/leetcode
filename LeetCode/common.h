#pragma once

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include<iomanip>
#include <algorithm>
#include <queue>
#include <cstdio>
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
	ListNode(int x) : val(x), next(nullptr) {}
};

//树节点
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
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



class TreeNodeCodec {
public:

	// Encodes a tree to a single string. 层次遍历
	static string serialize(TreeNode* root) {
		string ans;
		if (root == NULL)
			return "[]";
		ans = "[";
		queue<TreeNode*> que;
		que.push(root);

		char str[100];

		while (!que.empty())
		{
			TreeNode* top = que.front();
			que.pop();

			if (top != NULL)
			{
				que.push(top->left);
				que.push(top->right);

				sprintf_s(str, "%d", top->val);
				ans += str;
			}
			else {
				ans += "null";
			}

			ans += ",";
		}

		int end = ans.length() - 1;
		while (!(ans[end] >= '0' && ans[end] <= '9'))
			end--;

		string rs = ans.substr(0, end + 1);
		rs += "]";

		return rs;
	}

	// Decodes your encoded data to tree. // 解析一个层次遍历
	static TreeNode* deserialize(string data) {

		int len = data.size();

		if (len <= 2)
			return NULL;

		int numsCount = 0;
		vector<TreeNode*> nums;

		string word = "";
		for (int i = 1; i <= len - 2; i++) {
			if (data[i] == ',')
			{
				TreeNode* tmp = NULL;
				if (word == "null")
				{

				}
				else {
					int num = atoi(word.c_str());
					tmp = new TreeNode(num);
				}
				nums.push_back(tmp);
				word = "";
			}
			else {
				//if (data[i] >= '0' && data[i] <= '9')
				word += data[i];
			}
		}
		if (word != "" && word != "null")
		{
			int num = atoi(word.c_str());
			TreeNode* tmp = new TreeNode(num);
			nums.push_back(tmp);
		}

		int cnt = nums.size();

		int q = 0; // 遍历的节点,每个节点一个一个遍历（包括了NULL 节点）
		int p = 1; // 当前遍历结点 的 左孩子节点， p+1就是右孩子节点
		while (p < cnt)
		{
			if (nums[q] == NULL) {
				q++;
			}
			else {
				if (p < cnt)
					nums[q]->left = nums[p];
				if (p + 1 < cnt)
					nums[q]->right = nums[p + 1];
				p += 2;
				q++;
			}
		}

		return nums[0];
	}
};
