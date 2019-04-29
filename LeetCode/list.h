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
	//先转换为环，再寻找切割点
	ListNode * rotateRight(ListNode* head, int k) {
		if (k == 0 || !head || !head->next) return head;

		auto len = getListLength(head);
		int actualStepCnt = k % len;
		int headIdx = len - actualStepCnt;


		//环状单项链表
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
		//head->next = nullptr, 将其指向head
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