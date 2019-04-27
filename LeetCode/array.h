#pragma once
#include "common.h"

/***************************************������ص���***************************************/


//
//54. ��������
//
//����һ������ m x n ��Ԫ�صľ���m ��, n �У����밴��˳ʱ������˳�򣬷��ؾ����е�����Ԫ�ء�
//
//ʾ�� 1:
//
//����:
//[
//	[1, 2, 3],
//	[4, 5, 6],
//	[7, 8, 9]
//]
//��� : [1, 2, 3, 6, 9, 8, 7, 4, 5]
//	ʾ�� 2 :
//
//	���� :
//	[
//		[1, 2, 3, 4],
//		[5, 6, 7, 8],
//		[9, 10, 11, 12]
//	]
//	 ��� : [1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7]
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
// 59. �������� II
//
//����һ�������� n������һ������ 1 �� n2 ����Ԫ�أ���Ԫ�ذ�˳ʱ��˳���������е������ξ���
//
//ʾ�� :
//
//����: 3
//	��� :
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

		//˼·��Solution54���һ�ޣ�ֻ��������ӡ��ɸ�ֵ

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


