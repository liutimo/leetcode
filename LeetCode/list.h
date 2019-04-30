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


class Solution {
public:
	ListNode * deleteDuplicates(ListNode* head) {
		if (!head) return head;
		
		auto *h = head; 
		auto *start = h;
		auto *end = start;
		auto *tmp = h->next;
		while (tmp) {
			if (start->val == tmp->val) {
				end = tmp;
			}
			else {
				if (start != end) {
					if (h == start) {
						h = tmp;
					}
					while (start != end->next) {
						auto *t = start;
						start = start->next;
						delete t;
					}
				}
				else {
					start = start->next;
				}
			}
			tmp = tmp->next;
		}
		return head;
	}
};