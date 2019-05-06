#pragma once
/***************************************贪心算法相关的题***************************************/
#include "common.h"

//134 https://leetcode-cn.com/problems/gas-station/
class Solution134 {
public:
	//超时
	int canCompleteCircuit1(vector<int>& gas, vector<int>& cost) {
		//贪心算法，
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
			//未回到原点
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
			total += gas[i] - cost[i]; //记录总油耗和总加油数之差
			sum += gas[i] - cost[i];	//当前i不能作为起点
			if (sum < 0) {
				start = i + 1;
				sum = 0;
			}
		}
		// 2 3 4 5 7
		// 1 2 6 6 6
		// 如果0 - 3出现了一次不能到达的情况，则0-3的任何一个都不能作为起点
		return total < 0 ? -1 : start;
	}
};