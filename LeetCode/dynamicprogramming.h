#pragma once

/***************************************��̬�滮��ص���***************************************/
//62. ��ͬ·��
//һ��������λ��һ�� m x n ��������Ͻ� ����ʼ������ͼ�б��Ϊ��Start�� ����
//
//������ÿ��ֻ�����»��������ƶ�һ������������ͼ�ﵽ��������½ǣ�����ͼ�б��Ϊ��Finish������
//
//���ܹ��ж�������ͬ��·����
//˵����m �� n ��ֵ�������� 100��
//
//ʾ�� 1:
//
//����: m = 3, n = 2
//	��� : 3
//	���� :
//	�����Ͻǿ�ʼ���ܹ��� 3 ��·�����Ե������½ǡ�
//	1. ����->����->����
//	2. ����->����->����
//	3. ����->����->����
//	ʾ�� 2 :
//
//	���� : m = 7, n = 3
//	��� : 28
class Solution62 {
public:
	int uniquePaths(int m, int n) {
		//�ݹ�����ֻ�����һ����������ַ�ʽ��
		//return recursion(1, 1, m, n);


		//�ݹ�ĵ���
		vector<vector<int>> vv(m, vector<int>(n, 1)); //����¼

		for (int i = 1; i < m; ++i) {
			for (int j = 1; j < n; ++j) {
				vv[i][j] = vv[i - 1][j] + vv[i][j - 1];
			}
		}
		return vv[m - 1][n - 1];
	}

	int recursion(int x, int y, int m, int n) {
		//�ݹ����
		if (x == m || y == n)
			return 1;
		//�����ظ����㣬����Ż��� 
		//return recursion(x + 1, y, m, n) + recursion(x, y + 1, m, n);
		static vector<vector<int>> vv(m, vector<int>(n, 0)); //����¼

		if (vv[x - 1][y - 1]) {
			return vv[x - 1][y - 1];
		}

		int sum = recursion(x + 1, y, m, n) + recursion(x, y + 1, m, n);
		vv[x - 1][y - 1] = sum;
		return sum;
	}
};
//
//63. ��ͬ·�� II
//һ��������λ��һ�� m x n ��������Ͻ� ����ʼ������ͼ�б��Ϊ��Start�� ����
//
//������ÿ��ֻ�����»��������ƶ�һ������������ͼ�ﵽ��������½ǣ�����ͼ�б��Ϊ��Finish������
//
//���ڿ������������ϰ����ô�����Ͻǵ����½ǽ����ж�������ͬ��·����
//�����е��ϰ���Ϳ�λ�÷ֱ��� 1 �� 0 ����ʾ��
//
//˵����m �� n ��ֵ�������� 100��
//
//ʾ�� 1:
//
//����:
//[
//	[0, 0, 0],
//	[0, 1, 0],
//	[0, 0, 0]
//]
//��� : 2
//	���� :
//	3x3 ��������м���һ���ϰ��
//	�����Ͻǵ����½�һ���� 2 ����ͬ��·����
//	1. ����->����->����->����
//	2. ����->����->����->����
//ִ����ʱ : 16 ms, ��Unique Paths II��C++�ύ�л�����35.88% ���û�
//�ڴ�����: 9.4 MB, ��Unique Paths II��C++�ύ�л�����5.32% ���û�

class Solution63 {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrids) {
		if (obstacleGrids.size() == 0) return 0;
		int m = obstacleGrids.size();
		int n = obstacleGrids[0].size();

		if (m == 1 || n == 1) return 1;

		vector<vector<int>> obstacleGrid(m, vector<int>(n, 0));
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j <n; ++j) {
				if (obstacleGrids[i][j] == 0) {
					if (i >= 1 && j >= 1)
						obstacleGrid[i][j] = obstacleGrid[i - 1][j] + obstacleGrid[i][j - 1];
					else if (i > 0 && j == 0) {
						if (i == 1) {
							obstacleGrid[i][j] = 1;
						}
						else {
							obstacleGrid[i][j] = obstacleGrid[i - 1][j];
						}
					}
					else if (i == 0 && j > 0){
						if (j == 1) {
							obstacleGrid[i][j] = 1;
						}
						else {
							obstacleGrid[i][j] = obstacleGrid[i][j - 1];
						}
					}
				}
				else {
					obstacleGrid[i][j] = 0;
				}
			}
		}

		return obstacleGrid[m - 1][n - 1];
	}
};


//64. ��С·����
//����һ�������Ǹ������� m x n �������ҳ�һ�������Ͻǵ����½ǵ�·����ʹ��·���ϵ������ܺ�Ϊ��С��
//
//˵����ÿ��ֻ�����»��������ƶ�һ����
//
//ʾ�� :
//
//����:
//[
//	[1, 3, 1],
//	[1, 5, 1],
//	[4, 2, 1]
//]
//��� : 7
//���� : ��Ϊ·�� 1��3��1��1��1 ���ܺ���С��
//ִ����ʱ : 16 ms, ��Minimum Path Sum��C++�ύ�л�����96.06% ���û�
//�ڴ�����: 11 MB, ��Minimum Path Sum��C++�ύ�л�����45.31% ���û�

class Solution64 {
public:
	int minPathSum(vector<vector<int>>& grid) {
		if (grid.size() == 0) return 0;
		//recursion(0, 0, 0, grid, min);

		int m = grid.size();
		int n = grid[0].size();
		vector<vector<int>> vv(m, vector<int>(n, 0));
		vv[0][0] = grid[0][0];
		for (int i = 1; i < m; ++i)
			vv[i][0] = grid[i][0] + vv[i - 1][0];

		for (int i = 1; i < n; ++i)
			vv[0][i] = grid[0][i] + vv[0][i - 1];

		for (int i = 1; i < m; ++i) {
			for (int j = 1; j < n; ++j) {
				vv[i][j] = std::min(vv[i - 1][j], vv[i][j - 1]) + grid[i][j];
			}
		}

		return vv[m - 1][n - 1];
	}

	//��ʱ,�ĵ���
	void recursion(int curr, int x, int y, vector<vector<int>>& grid, int &MIN)
	{
		if (x > grid.size() - 1 || y > grid[0].size() - 1) return;
		curr += grid[x][y];
		if (x == grid.size() - 1 && y == grid[0].size() - 1)
		{
			MIN = min(curr, MIN);
		}
		else {
			recursion(curr, x + 1, y, grid, MIN);
			recursion(curr, x, y + 1, grid, MIN);
		}
	}
};;