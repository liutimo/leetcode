#pragma once
/***************************************λ������ص���***************************************/
#include "common.h"

//137 https://leetcode-cn.com/problems/single-number-ii/
class Solution137 {
public:
	int singleNumber1(vector<int>& nums) {
	
		int res = 0;
		for (int i = 0; i < 32; ++i) {
			int sum = 0;
			for (int num : nums) {
				sum += (num >> i) & 1; //ͳ�Ƶ�iλ��1�ĸ���
			}
			res |= sum % 3 == 0 ? 0 : 1 << i;
		}
		return res;
	}
};