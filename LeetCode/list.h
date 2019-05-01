#pragma once
#include "common.h"

/***************************************链表相关的题***************************************/
//
//61. 旋转链表
//
//给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
//
//示例 1:
//
//输入: 1->2->3->4->5->NULL, k = 2
//	输出 : 4->5->1->2->3->NULL
//	解释 :
//	向右旋转 1 步 : 5->1->2->3->4->NULL
//		向右旋转 2 步 : 4->5->1->2->3->NULL
//		示例 2 :
//
//		输入 : 0->1->2->NULL, k = 4
//		输出 : 2->0->1->NULL
//		解释 :
//	向右旋转 1 步 : 2->0->1->NULL
//		向右旋转 2 步 : 1->2->0->NULL
//		向右旋转 3 步 : 0->1->2->NULL
//		向右旋转 4 步 : 2->0->1->NULL
//
//执行用时: 16 ms, 在Rotate List的C++提交中击败了97.01% 的用户
//内存消耗 : 8.9 MB, 在Rotate List的C++提交中击败了81.06% 的用户
class Solution61 {
public:
	ListNode * rotateRight(ListNode* head, int k) {
		if (k == 0 || !head || !head->next) return head;

		auto len = getListLength(head);
		int actualStepCnt = k % len;
		int headIdx = len - actualStepCnt;


		ListNode *before = nullptr;
		for (int i = 0; i < headIdx; ++i) {
			before = head;
			head = head->next;
		}
		before->next = nullptr;
		return head;
	}


	int getListLength(ListNode *head) {
		if (!head) {
			return 0;
		}
		auto *ch = head;
		int len = 1;
		while (ch->next)
		{
			++len;
			ch = ch->next;
		}
		//head->next = nullptr, 
		ch->next = head;
		return len;
	}
};


//82. 删除排序链表中的重复元素 II
//给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中 没有重复出现 的数字。
//
//示例 1:
//
//输入: 1->2->3->3->4->4->5
//	输出 : 1->2->5
//	示例 2 :
//
//	输入 : 1->1->1->2->3
//	输出 : 2->3

class Solution82 {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		//O(1)的空间复杂度

		if (!head) return head;

		ListNode* new_head = nullptr;
		ListNode *new_curr = nullptr;
		auto *curr_node = head;
		while (curr_node) {
			auto *next_node = curr_node->next;
			//1 1 1 3，删除前面的1后， curr_node = 3, next_node=nullptr
			if (next_node && next_node->val == curr_node->val) {
				//重复
				while (next_node && curr_node->val == next_node->val) {
					//删除连续重复的节点
					delete curr_node;
					curr_node = next_node;
					next_node = next_node->next;
				}
				delete curr_node;
				curr_node = next_node;
				continue;
			}
			else {
				if (!new_head) {
					new_head = curr_node;
					new_curr = new_head;
				}
				else {
					new_curr->next = curr_node;
					new_curr = curr_node;
				}

			}
			curr_node = curr_node->next;
		}
		if (new_curr)
			new_curr->next = nullptr;
		return new_head;
	}
};


TEST(List, Solution82) {
	std::string line = "[1, 1, 1, 1, 1, 1]";
	auto *head = Solution82().deleteDuplicates(stringToListNode(line));
	EXPECT_EQ(listNodeToString(head), "[]");

	line = "[1,1,1,1,2,2,2,2,3,3,3,4,5]";
	head = Solution82().deleteDuplicates(stringToListNode(line));
	EXPECT_EQ(listNodeToString(head), "[4, 5]");

	line = "[1,2,3,4,5,6,6,6,6,6,6,6,7]";
	head = Solution82().deleteDuplicates(stringToListNode(line));
	EXPECT_EQ(listNodeToString(head), "[1, 2, 3, 4, 5, 7]");

}
//86. 分隔链表
//
//给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于 x 的节点都在大于或等于 x 的节点之前。
//
//你应当保留两个分区中每个节点的初始相对位置。
//
//示例 :
//
//输入: head = 1->4->3->2->5->2, x = 3
//	输出 : 1->2->2->4->3->5
//执行用时 : 12 ms, 在Partition List的C++提交中击败了94.91% 的用户
//内存消耗: 8.8 MB, 在Partition List的C++提交中击败了5.16% 的用户
//
class Solution86 {
public:
	ListNode* partition(ListNode* head, int x) {
		if (!head) return head;
		

		//左边的插入点
		ListNode *left_insert_point = nullptr;
		ListNode *right_insert_point = nullptr;
		ListNode *curr = head;
		ListNode *right_head = nullptr;
		ListNode *left_head = nullptr;

		//1 4 3 2 5 2 
		while (curr) {
			if (curr->val < x) {
				auto *c = curr;
				curr = curr->next;
				if (!left_head) {
					left_head = c;
					left_insert_point = c;
					left_insert_point->next = right_head;
				}
				else {
					left_insert_point->next = c;
					c->next = right_head;
					left_insert_point = c;
				}
			}
			else {
				auto *c = curr;
				curr = curr->next;
				if (!right_head) {
					right_head = c;
					right_insert_point = c;
					if (left_insert_point)
						left_insert_point->next = c;
				}
				else {
					right_insert_point->next = c;
					right_insert_point = c;
				}
			}
		}
		if (right_insert_point)
			right_insert_point->next = nullptr;
		return left_head ? left_head : right_head;
	}
};

TEST(List, Soultion86) {
	string line = "[1,4,3,2,5,2]";
	
	EXPECT_EQ(listNodeToString(Solution86().partition(stringToListNode(line), 3)), "[1, 2, 2, 4, 3, 5]");

	line = "[2, 1]";
	EXPECT_EQ(listNodeToString(Solution86().partition(stringToListNode(line), 2)), "[1, 2]");


	line = "[1, 2]";
	EXPECT_EQ(listNodeToString(Solution86().partition(stringToListNode(line), 2)), "[1, 2]");
}
//
//92. 反转链表 II
//反转从位置 m 到 n 的链表。请使用一趟扫描完成反转。
//
//说明 :
//1 ≤ m ≤ n ≤ 链表长度。
//
//示例 :
//
//输入: 1->2->3->4->5->NULL, m = 2, n = 4
//	输出 : 1->4->3->2->5->NULL
//执行用时 : 8 ms, 在Reverse Linked List II的C++提交中击败了96.41% 的用户
//内存消耗: 8.7 MB, 在Reverse Linked List II的C++提交中击败了64.82% 的用户
//
class Solution92 {
public:
	ListNode * reverseBetween(ListNode* head, int m, int n) {
		if (m == n) return head;
		if (m <= 0)  m = 1;
		ListNode *new_head = (m == 1 ? nullptr : head);

		ListNode *prev = nullptr;
		ListNode *next = head->next;
		ListNode *start_node = nullptr;
		ListNode *before_start_node = nullptr;
		ListNode *next_node = head->next;
		int count = 0;
		while (head) {
			++count;
			if (count >= m && count <= n) {
				if (!before_start_node) {
					before_start_node = prev;
				}
				if (!start_node) start_node = head;
				head->next = prev;
			}
			else if (count > n) {
				break;
			}
			prev = head;
			head = next_node;
			if (head)
			next_node = head->next;
		}
		start_node->next = head;
		if (m != 1)
			before_start_node->next = prev;
		if (new_head == nullptr) new_head = prev;
		return new_head;
	}
};
TEST(list, Solution92) {
	Solution92 s;
	string str = "[1,2,3]";
	auto *head = stringToListNode(str);
	auto res = listNodeToString(s.reverseBetween(head, 1, 3));
	string res2 = "[3, 2, 1]";
	EXPECT_EQ(res, res2);
}