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