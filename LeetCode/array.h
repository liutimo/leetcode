#pragma once
#include "common.h"

/***************************************数组相关的题***************************************/


//
//54. 螺旋矩阵
//
//给定一个包含 m x n 个元素的矩阵（m 行, n 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。
//
//示例 1:
//
//输入:
//[
//	[1, 2, 3],
//	[4, 5, 6],
//	[7, 8, 9]
//]
//输出 : [1, 2, 3, 6, 9, 8, 7, 4, 5]
//	示例 2 :
//
//	输入 :
//	[
//		[1, 2, 3, 4],
//		[5, 6, 7, 8],
//		[9, 10, 11, 12]
//	]
//	 输出 : [1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7]
//
class Solution54 {
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		vector<int> res;
		//used matrix[0]. so must check.
		if (matrix.size() == 0) {
			return res;
		}
		int left = 0, right = matrix[0].size() - 1;
		int top = 0, bottom = matrix.size() - 1;

		while (left <= right || top <= bottom) {
			int i = left;
			//TopLeft to TopRight
			while (i <= right && top <= bottom) res.push_back(matrix[top][i++]);
			i = ++top;
			//LeftTop to LeftBottom
			while (i <= bottom && left <= right) res.push_back(matrix[i++][right]);
			i = --right;
			//BottomRight to BottomLeft
			while (i >= left && top <= bottom) res.push_back(matrix[bottom][i--]);
			i = --bottom;
			//LeftBottom to RightBottom
			while (i >= top && left <= right) res.push_back(matrix[i--][left]);
			++left;
		}
		return res;
	}
};
// 59. 螺旋矩阵 II
//
//给定一个正整数 n，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。
//
//示例 :
//
//输入: 3
//	输出 :
//	[
//		[1, 2, 3],
//		[8, 9, 4],
//		[7, 6, 5]
//	]
//
class Solution59 {
public:
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> res(n, vector<int>(n));
		if (n == 0) return res;

		//思路和Solution54如出一辙，只不过将打印变成赋值

		int left = 0, right = res[0].size() - 1;
		int top = 0, bottom = res.size() - 1;

		int num = 1;
		while (left <= right || top <= bottom) {
			int i = left;
			//TopLeft to TopRight
			while (i <= right && top <= bottom) res[top][i++] = num++;
			i = ++top;
			//LeftTop to LeftBottom
			while (i <= bottom && left <= right) res[i++][right] = num++;
			i = --right;
			//BottomRight to BottomLeft
			while (i >= left && top <= bottom)  res[bottom][i--] = num++;
			i = --bottom;
			//LeftBottom to RightBottom
			while (i >= top && left <= right) res[i--][left] = num++;
			++left;
		}
		return res;
	}
};



TEST(testadd, test1)
{
	vector<vector<int>> res = { {1, 2, 3}, {8, 9, 4 } , {7, 6, 5} };
	EXPECT_EQ(res, Solution59().generateMatrix(3));
}

//119. 杨辉三角 II
//给定一个非负索引 k，其中 k ≤ 33，返回杨辉三角的第 k 行。
//
//
//
//在杨辉三角中，每个数是它左上方和右上方的数的和。
//
//示例 :
//
//输入: 3
//	输出 : [1, 3, 3, 1]
//	进阶：
//
//	你可以优化你的算法到 O(k) 空间复杂度吗？
class Solution119 {
public:
	vector<int> getRow(int rowIndex) {
		vector<int> ret;
		if (rowIndex < 0) return ret;
		ret.resize(rowIndex + 1);
		ret[0] = 1;
		for (int i = 1; i <= rowIndex; ++i) {
			for (int j = rowIndex; j >= 1; --j) {
				ret[j] = ret[j] + ret[j - 1];
			}
		}
		return ret;
	}
};



TEST(Array, Solution119)
{
	vector<int> res = { 1,4,6,4,1 };

	EXPECT_EQ(Solution119().getRow(4), res);
}
