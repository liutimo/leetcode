#pragma once
/***************************************位运算相关的题***************************************/
#include "common.h"

//137 https://leetcode-cn.com/problems/single-number-ii/
class Solution137 {
public:
	int singleNumber1(vector<int>& nums) {
	
		int res = 0;
		for (int i = 0; i < 32; ++i) {
			int sum = 0;
			for (int num : nums) {
				sum += (num >> i) & 1; //统计第i位的1的个数
			}
			res |= sum % 3 == 0 ? 0 : 1 << i;
		}
		return res;
	}
};