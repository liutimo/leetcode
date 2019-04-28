#pragma once
#include "common.h"
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