#pragma once
/***************************************二分查找相关的题***************************************/
#include "common.h"
//
//74. 搜索二维矩阵
//编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性：
//
//每行中的整数从左到右按升序排列。
//每行的第一个整数大于前一行的最后一个整数。
//示例 1:
//
//输入:
//matrix = [
//	[1, 3, 5, 7],
//		[10, 11, 16, 20],
//		[23, 30, 34, 50]
//]
//target = 3
//输出: true
//	示例 2 :
//
//	输入 :
//	matrix = [
//		[1, 3, 5, 7],
//			[10, 11, 16, 20],
//			[23, 30, 34, 50]
//	]
//	target = 13
//		输出: false
//		执行用时 : 16 ms, 在Search a 2D Matrix的C++提交中击败了93.69% 的用户
//		内存消耗 : 9.8 MB, 在Search a 2D Matrix的C++提交中击败了78.19% 的用户
//

//根据题意，二位矩阵为单调递增，当然是用二分查找咯。
class Solution74 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0) return false;
        
        int row = matrix.size();
        int col = matrix[0].size();
        
        int left = 0, right = matrix.size() * matrix[0].size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int x = mid / col;
            int y = mid % col;
            if (matrix[x][y] == target) {
                return true;
            } else if (matrix[x][y] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return false;  
    }
};

TEST(testCase, test1)
{
	vector<vector<int>> matrix = {

		{1, 2,  3,  4},
		{5, 6,  7,  8},
		{9, 10, 11, 12}
	};

	EXPECT_EQ(true, Solution74().searchMatrix(matrix, 12));
}