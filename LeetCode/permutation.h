#pragma once
#include "common.h"

/***************************************排列相关的题***************************************/
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