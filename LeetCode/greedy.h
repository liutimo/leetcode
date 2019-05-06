#pragma once
/***************************************̰���㷨��ص���***************************************/
#include "common.h"

//134 https://leetcode-cn.com/problems/gas-station/
class Solution134 {
public:
	//��ʱ
	int canCompleteCircuit1(vector<int>& gas, vector<int>& cost) {
		//̰���㷨��
		int start = 0;
		while (gas[start] < cost[start]) {
			++start;
		}

		for (int i = start; i < gas.size(); ++i) {
			int s = i;
			int remainder = gas[s] - cost[s];
			if (remainder < 0) {
				continue;
			}
			++s;
			//δ�ص�ԭ��
			while (s != i) {
				if (s == gas.size()) {
					s = 0;
				}
				remainder += gas[s] - cost[s];
				if (remainder < 0) {
					break;
				}
				++s;
			}

			if (remainder >= 0) {
				return i;
			}
		}
		return -1;
	}


	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int total = 0, sum = 0, start = 0;

		for (int i = 0; i < gas.size(); ++i) {
			total += gas[i] - cost[i]; //��¼���ͺĺ��ܼ�����֮��
			sum += gas[i] - cost[i];	//��ǰi������Ϊ���
			if (sum < 0) {
				start = i + 1;
				sum = 0;
			}
		}
		// 2 3 4 5 7
		// 1 2 6 6 6
		// ���0 - 3������һ�β��ܵ�����������0-3���κ�һ����������Ϊ���
		return total < 0 ? -1 : start;
	}
};