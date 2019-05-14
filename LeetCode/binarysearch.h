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



//33. 搜索旋转排序数组
//假设按照升序排序的数组在预先未知的某个点上进行了旋转。
//
//(例如，数组[0, 1, 2, 4, 5, 6, 7] 可能变为[4, 5, 6, 7, 0, 1, 2])。
//
//搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 - 1 。
//
//你可以假设数组中不存在重复的元素。
//
//你的算法时间复杂度必须是 O(log n) 级别。
//
//示例 1:
//
//输入: nums = [4, 5, 6, 7, 0, 1, 2], target = 0
//	输出 : 4
//	示例 2 :
//
//	输入 : nums = [4, 5, 6, 7, 0, 1, 2], target = 3
//	输出 : -1
class Solution33 {
public:
	int search(vector<int>& nums, int target) {
		int left = 0, right = nums.size() - 1;

		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (nums[mid] == target) {
				return mid;
			}
			else {
				//mid在右侧有序段
				if (nums[mid] < nums[right]) {
					if (nums[mid] < target && target <= nums[right]) { //target 在有序段
						left = mid + 1;
					}
					else {
						right = mid - 1;	//target 在mid右侧
					}
				}
				else { // mid在左侧有序段
					if (nums[mid] > target && target > nums[right]) {
						right = mid - 1;
					}
					else {
						left = mid + 1;
					}
				}
			}
		}
		return -1;
	}
};

TEST(Array, Solution33) {
	vector<int> vec{ 0,1, 2, 3, 4, 5, 6, 7, 8 };
	Solution33  ss;
	EXPECT_EQ(0, ss.search(vec, 0));
	EXPECT_EQ(8, ss.search(vec, 8));
	EXPECT_EQ(2, ss.search(vec, 2));
	EXPECT_EQ(5, ss.search(vec, 5));
}

//81. 搜索旋转排序数组 II
//假设按照升序排序的数组在预先未知的某个点上进行了旋转。
//
//(例如，数组[0, 0, 1, 2, 2, 5, 6] 可能变为[2, 5, 6, 0, 0, 1, 2])。
//
//编写一个函数来判断给定的目标值是否存在于数组中。若存在返回 true，否则返回 false。
//
//示例 1:
//
//输入: nums = [5, 6, 0, 1, 2], target = 0
//	输出 : true
//	示例 2 :
//
//	输入 : nums = [2, 5, 6, 0, 0, 1, 2], target = 3
//	输出 : false
//	进阶 :
//
//	这是 搜索旋转排序数组 的延伸题目，本题中的 nums  可能包含重复元素。
//	这会影响到程序的时间复杂度吗？会有怎样的影响，为什么？


class Solution81 {
public:
	bool search(vector<int>& nums, int target) {
		int left = 0, right = nums.size() - 1;
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (nums[mid] == target)
				return true;
			if (nums[mid] == nums[left] && nums[mid] == nums[right])
				left++, right--;
			else if (nums[mid] <= nums[right]) {
				if (nums[mid] <target && target <= nums[right])
					left = mid + 1;
				else
					right = mid - 1;
			}
			else {
				if (nums[left] <= target && target < nums[mid])
					right = mid - 1;
				else
					left = mid + 1;
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