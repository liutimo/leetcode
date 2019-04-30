#pragma once
/***************************************回溯相关的题***************************************/
#include "common.h"

//
//39. 组合总和
//给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
//
//candidates 中的数字可以无限制重复被选取。
//
//说明：
//
//所有数字（包括 target）都是正整数。
//解集不能包含重复的组合。
//示例 1:
//
//输入: candidates = [2, 3, 6, 7], target = 7,
//	所求解集为 :
//	[
//		[7],
//		[2, 2, 3]
//	]
//	示例 2 :
//
//		输入 : candidates = [2, 3, 5], target = 8,
//		所求解集为 :
//		[
//			[2, 2, 2, 2],
//			[2, 3, 3],
//			[3, 5]
//		]
//
class Solution39 {
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end());
		vector<int> res;
		vector<vector<int>> ret;
		resF(0, 0, res, target, ret, candidates);
		return ret;
	}

	void resF(int j, int currValue, vector<int> res, int target, vector<vector<int>> &ress, vector<int>& candidates)
	{
		if (target == currValue) {
			ress.push_back(res);
			return;
		}
		else if (currValue > target) {
			return;;
		}
		for (int i = j; i < candidates.size(); ++i) {
			if (currValue + candidates[i] > target) {
				return;
			}
			res.push_back(candidates[i]);
			resF(i, currValue + candidates[i], res, target, ress, candidates);
			res.pop_back();
		}
	}
};

//
//40. 组合总和 II
//给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
//
//candidates 中的每个数字在每个组合中只能使用一次。
//
//说明：
//
//所有数字（包括目标数）都是正整数。
//解集不能包含重复的组合。
//示例 1:
//
//输入: candidates = [10, 1, 2, 7, 6, 1, 5], target = 8,
//	所求解集为 :
//	[
//		[1, 7],
//		[1, 2, 5],
//		[2, 6],
//		[1, 1, 6]
//	]
//	示例 2:
//
//输入: candidates = [2, 5, 2, 1, 2], target = 5,
//	所求解集为 :
//	[
//		[1, 2, 2],
//		[5]
//	]

class Solution40 {
public:
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		//使用set去重。优化点，
		set<vector<int>> ret;
		vector<int> res;
		sort(candidates.begin(), candidates.end());
		resF(0, 0, res, target, ret, candidates);
		return vector<vector<int>>(ret.cbegin(), ret.cend());
	}

	void resF(int j, int currValue, vector<int> res, int target, set<vector<int>> &ress, vector<int>& candidates)
	{
		if (target == currValue) {
			ress.insert(res);
			return;
		}
		else if (currValue > target) {
			return;
		}
		for (int i = j; i < candidates.size(); ++i) {
			if (currValue + candidates[i] > target) {
				return;
			}

			//优化点，将set该为vector即可。
			//比如 1,1,1,1,1,1,2  target 为2
			//对于第一个1,能够得出2，后面的1就没有了直接到2
			//if (j < i && candidates[i - 1] == candidates[i]) continue;

			res.push_back(candidates[i]);
			//i + 1来避免重复使用一个数
			resF(i + 1, currValue + candidates[i], res, target, ress, candidates);
			res.pop_back();
		}
	}
};


//89. 格雷编码
//格雷编码是一个二进制数字系统，在该系统中，两个连续的数值仅有一个位数的差异。
//
//给定一个代表编码总位数的非负整数 n，打印其格雷编码序列。格雷编码序列必须以 0 开头。
//
//示例 1:
//
//输入: 2
//	输出 : [0, 1, 3, 2]
//	解释 :
//	00 - 0
//	01 - 1
//	11 - 3
//	10 - 2
//
//	对于给定的 n，其格雷编码序列并不唯一。
//	例如，[0, 2, 3, 1] 也是一个有效的格雷编码序列。
//
//	00 - 0
//	10 - 2
//	11 - 3
//	01 - 1
//	示例 2:
//
//输入: 0
//	输出 : [0]
//	解释 : 我们定义格雷编码序列必须以 0 开头。
//	给定编码总位数为 n 的格雷编码序列，其长度为 2n。当 n = 0 时，长度为 20 = 1。
//	因此，当 n = 0 时，其格雷编码序列为[0]。
//https://blog.csdn.net/w8253497062015/article/details/80896500
class Solution89 {
public:
	//数学公式
	/**
		关键是搞清楚格雷编码的生成过程, G(i) = i ^ (i/2);
		如 n = 3:
		G(0) = 000,
		G(1) = 1 ^ 0 = 001 ^ 000 = 001
		G(2) = 2 ^ 1 = 010 ^ 001 = 011
		G(3) = 3 ^ 1 = 011 ^ 001 = 010
		G(4) = 4 ^ 2 = 100 ^ 010 = 110
		G(5) = 5 ^ 2 = 101 ^ 010 = 111
		G(6) = 6 ^ 3 = 110 ^ 011 = 101
		G(7) = 7 ^ 3 = 111 ^ 011 = 100
	**/
	vector<int> grayCode1(int n) {
		int size = 1 << n;
		vector<int> ret(size);
		for (int i = 0; i < size; ++i) {
			int res = i ^ (i >> 1);
			ret[0] = res;
		}
		return ret;
	}

	//https://blog.csdn.net/w8253497062015/article/details/80896500
	vector<int> grayCode(int n) {
		vector<int> ret(1);
		for (int i = 0; i < n; ++i) {
			for (int j = ret.size() - 1; j >= 0; --j){
				ret.push_back(1 << i + ret[j]);
			}
		}
		return ret;
	}
};