#pragma once
#include "common.h"

/***************************************排列组合相关的题***************************************/
//
//60. 第k个排列
//给出集合[1, 2, 3, …, n]，其所有元素共有 n!种排列。
//
//按大小顺序列出所有排列情况，并一一标记，当 n = 3 时, 所有排列如下：
//
//"123"
//"132"
//"213"
//"231"
//"312"
//"321"
//给定 n 和 k，返回第 k 个排列。
//
//说明：
//
//给定 n 的范围是[1, 9]。
//给定 k 的范围是[1, n!]。
//示例 1:
//
//输入: n = 3, k = 3
//	输出 : "213"
//	示例 2 :
//
//	输入 : n = 4, k = 9
//	输出 : "2314"

class Solution60 {
public:

	//执行用时 : 476 ms, 在Permutation Sequence的C++提交中击败了15.84% 的用户
	//内存消耗 : 8.2 MB, 在Permutation Sequence的C++提交中击败了80.60% 的用户
	//太慢了吧
	string getPermutation1(int n, int k) {
		//已经给定n和k的范围
		vector<char> ret(n);
		for (int i = 0; i < n; ++i) {
			ret[i] = '1' + i;
		}

		while (--k) {
			//为了偷懒有点投机取巧
			//并未判断函数返回值，因为用例保证了n和k的正确性
			std::next_permutation(ret.begin(), ret.end());
		}

		return string(ret.begin(), ret.end());
	}

	// 还是太菜啊自己
	//参考博客：https://blog.csdn.net/sinat_35261315/article/details/78412805
	//执行用时: 8 ms, 在Permutation Sequence的C++提交中击败了97.17% 的用户
	//内存消耗 : 8.3 MB, 在Permutation Sequence的C++提交中击败了72.57% 的用户
	//
	string getPermutation(int n, int k) {
		//[1, n]一共有n!个排列数，[1, n]中每个数占 n!/n个
		//因此可以根据k来确定第k个排列的每一位应该是什么数
		
		//1 计算n的阶乘
		vector<char> dict(n + 1, '0');
		vector<int> factorialDict(n + 1, 1);
		for (int i = 1; i <= n; ++i) {
			dict[i] = '0' + i;
			factorialDict[i] = i * factorialDict[i - 1];
		}

		string ret;
		for (int i = 1; i <= n; ++i) {
			int idx = k / factorialDict[n - i];
			if (k % factorialDict[n - i] != 0)
				++idx;
			ret.push_back(dict[idx]);
			//idx 已经被用了，所以要删除
			dict.erase(dict.begin() + idx);
			k -= (idx - 1) * factorialDict[n - i];
		}
		return ret;
	}
};
//
//77. 组合
//
//给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
//
//示例 :
//
//输入: n = 4, k = 2
//	输出 :
//	[
//		[2, 4],
//		[3, 4],
//		[2, 3],
//		[1, 2],
//		[1, 3],
//		[1, 4],
//	]
// 性能堪忧哈哈
//执行用时: 112 ms, 在Combinations的C++提交中击败了85.06% 的用户
//内存消耗 : 12 MB, 在Combinations的C++提交中击败了64.31% 的用户
class Solution77 {
public:
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> ress;
		vector<int> res;
		recursion(ress, res, n, k, 1);
		return ress;
	}
	//res必须为引用，提高性能
	void recursion(vector<vector<int>> &ress, vector<int> &res, int n, int k, int cur) {
		if (res.size() == k) {
			ress.emplace_back(res);
			return;
		} 
		if (cur > n) {
			return;
		}

		for (int i = cur; i <= n; ++i) {
			res.push_back(i);
			recursion(ress, res, n, k, i + 1);
			res.pop_back();
		}
	}
};

TEST(combine, Solution77) {
	auto ret = Solution77().combine(4, 2);
	decltype(ret) val = {
							{ 1, 2 },
							{ 1, 3 },
							{ 1, 4 },
							{ 2, 3 },
							{ 2, 4 },
							{ 3, 4 },
						};

	EXPECT_EQ(val, ret);
}