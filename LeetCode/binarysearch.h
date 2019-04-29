#pragma once
/***************************************���ֲ�����ص���***************************************/
#include "common.h"
//
//74. ������ά����
//��дһ����Ч���㷨���ж� m x n �����У��Ƿ����һ��Ŀ��ֵ���þ�������������ԣ�
//
//ÿ���е����������Ұ��������С�
//ÿ�еĵ�һ����������ǰһ�е����һ��������
//ʾ�� 1:
//
//����:
//matrix = [
//	[1, 3, 5, 7],
//		[10, 11, 16, 20],
//		[23, 30, 34, 50]
//]
//target = 3
//���: true
//	ʾ�� 2 :
//
//	���� :
//	matrix = [
//		[1, 3, 5, 7],
//			[10, 11, 16, 20],
//			[23, 30, 34, 50]
//	]
//	target = 13
//		���: false
//		ִ����ʱ : 16 ms, ��Search a 2D Matrix��C++�ύ�л�����93.69% ���û�
//		�ڴ����� : 9.8 MB, ��Search a 2D Matrix��C++�ύ�л�����78.19% ���û�
//

//�������⣬��λ����Ϊ������������Ȼ���ö��ֲ��ҿ���
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