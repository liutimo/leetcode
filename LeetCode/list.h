#pragma once
#include "common.h"


/***************************************������ص���***************************************/
//
//61. ��ת����
//
//����һ��������ת����������ÿ���ڵ������ƶ� k ��λ�ã����� k �ǷǸ�����
//
//ʾ�� 1:
//
//����: 1->2->3->4->5->NULL, k = 2
//	��� : 4->5->1->2->3->NULL
//	���� :
//	������ת 1 �� : 5->1->2->3->4->NULL
//		������ת 2 �� : 4->5->1->2->3->NULL
//		ʾ�� 2 :
//
//		���� : 0->1->2->NULL, k = 4
//		��� : 2->0->1->NULL
//		���� :
//	������ת 1 �� : 2->0->1->NULL
//		������ת 2 �� : 1->2->0->NULL
//		������ת 3 �� : 0->1->2->NULL
//		������ת 4 �� : 2->0->1->NULL
//
//ִ����ʱ: 16 ms, ��Rotate List��C++�ύ�л�����97.01% ���û�
//�ڴ����� : 8.9 MB, ��Rotate List��C++�ύ�л�����81.06% ���û�
class Solution61 {
public:
	//��ת��Ϊ������Ѱ���и��
	ListNode * rotateRight(ListNode* head, int k) {
		if (k == 0 || !head || !head->next) return head;

		auto len = getListLength(head);
		int actualStepCnt = k % len;
		int headIdx = len - actualStepCnt;


		//��״��������
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
		//head->next = nullptr, ����ָ��head
		ch->next = head;
		return len;
	}
};


//82. ɾ�����������е��ظ�Ԫ�� II
//����һ����������ɾ�����к����ظ����ֵĽڵ㣬ֻ����ԭʼ������ û���ظ����� �����֡�
//
//ʾ�� 1:
//
//����: 1->2->3->3->4->4->5
//	��� : 1->2->5
//	ʾ�� 2 :
//
//	���� : 1->1->1->2->3
//	��� : 2->3

class Solution82 {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		//O(1)�Ŀռ临�Ӷ�

		if (!head) return head;

		ListNode* new_head = nullptr;
		ListNode *new_curr = nullptr;
		auto *curr_node = head;
		while (curr_node) {
			auto *next_node = curr_node->next;
			//1 1 1 3��ɾ��ǰ���1�� curr_node = 3, next_node=nullptr
			if (next_node && next_node->val == curr_node->val) {
				//�ظ�
				while (next_node && curr_node->val == next_node->val) {
					//ɾ�������ظ��Ľڵ�
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
//86. �ָ�����
//
//����һ�������һ���ض�ֵ x����������зָ���ʹ������С�� x �Ľڵ㶼�ڴ��ڻ���� x �Ľڵ�֮ǰ��
//
//��Ӧ����������������ÿ���ڵ�ĳ�ʼ���λ�á�
//
//ʾ�� :
//
//����: head = 1->4->3->2->5->2, x = 3
//	��� : 1->2->2->4->3->5
//ִ����ʱ : 12 ms, ��Partition List��C++�ύ�л�����94.91% ���û�
//�ڴ�����: 8.8 MB, ��Partition List��C++�ύ�л�����5.16% ���û�
//
class Solution86 {
public:
	ListNode* partition(ListNode* head, int x) {
		if (!head) return head;
		

		//��ߵĲ����
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