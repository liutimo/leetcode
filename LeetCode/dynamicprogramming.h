#pragma once

/***************************************动态规划相关的题***************************************/
//62. 不同路径
//一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
//
//机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
//
//问总共有多少条不同的路径？
//说明：m 和 n 的值均不超过 100。
//
//示例 1:
//
//输入: m = 3, n = 2
//	输出 : 3
//	解释 :
//	从左上角开始，总共有 3 条路径可以到达右下角。
//	1. 向右->向右->向下
//	2. 向右->向下->向右
//	3. 向下->向右->向右
//	示例 2 :
//
//	输入 : m = 7, n = 3
//	输出 : 28
class Solution62 {
public:
	int uniquePaths(int m, int n) {
		//递归解决，只有向右或者向下两种方式。
		//return recursion(1, 1, m, n);


		//递归改迭代
		vector<vector<int>> vv(m, vector<int>(n, 1)); //备忘录

		for (int i = 1; i < m; ++i) {
			for (int j = 1; j < n; ++j) {
				vv[i][j] = vv[i - 1][j] + vv[i][j - 1];
			}
		}
		return vv[m - 1][n - 1];
	}

	int recursion(int x, int y, int m, int n) {
		//递归出口
		if (x == m || y == n)
			return 1;
		//大量重复计算，如何优化？ 
		//return recursion(x + 1, y, m, n) + recursion(x, y + 1, m, n);
		static vector<vector<int>> vv(m, vector<int>(n, 0)); //备忘录

		if (vv[x - 1][y - 1]) {
			return vv[x - 1][y - 1];
		}

		int sum = recursion(x + 1, y, m, n) + recursion(x, y + 1, m, n);
		vv[x - 1][y - 1] = sum;
		return sum;
	}
};
//
//63. 不同路径 II
//一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
//
//机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
//
//现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
//网格中的障碍物和空位置分别用 1 和 0 来表示。
//
//说明：m 和 n 的值均不超过 100。
//
//示例 1:
//
//输入:
//[
//	[0, 0, 0],
//	[0, 1, 0],
//	[0, 0, 0]
//]
//输出 : 2
//	解释 :
//	3x3 网格的正中间有一个障碍物。
//	从左上角到右下角一共有 2 条不同的路径：
//	1. 向右->向右->向下->向下
//	2. 向下->向下->向右->向右
//执行用时 : 16 ms, 在Unique Paths II的C++提交中击败了35.88% 的用户
//内存消耗: 9.4 MB, 在Unique Paths II的C++提交中击败了5.32% 的用户

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


//64. 最小路径和
//给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
//
//说明：每次只能向下或者向右移动一步。
//
//示例 :
//
//输入:
//[
//	[1, 3, 1],
//	[1, 5, 1],
//	[4, 2, 1]
//]
//输出 : 7
//解释 : 因为路径 1→3→1→1→1 的总和最小。
//执行用时 : 16 ms, 在Minimum Path Sum的C++提交中击败了96.06% 的用户
//内存消耗: 11 MB, 在Minimum Path Sum的C++提交中击败了45.31% 的用户

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

	//超时,改迭代
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