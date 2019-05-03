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
};



//91. 解码方法
//一条包含字母 A - Z 的消息通过以下方式进行了编码：
//
//'A' -> 1
//'B' -> 2
//...
//'Z' -> 26
//给定一个只包含数字的非空字符串，请计算解码方法的总数。
//
//示例 1:
//
//输入: "12"
//	输出 : 2
//	解释 : 它可以解码为 "AB"（1 2）或者 "L"（12）。
//	示例 2 :
//
//	输入 : "226"
//	输出 : 3
//	解释 : 它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6) 。
//执行用时: 12 ms, 在Decode Ways的C++提交中击败了44.38% 的用户
//内存消耗 : 8.4 MB, 在Decode Ways的C++提交中击败了47.32% 的用户
//	
class Solution91 {
public:
	//1234
	//1=1               1
	//12   (1 2) (12)    2
	//123  (((1 2) (12)) 3)  (1 23)   3
	//1234  (((((1 2) (12)) 3)  (1 23)) 4) 
	//对于长度超过 2的s
	// s[i] = s[i - 1] + s[i - 2];
	int numDecodings(string s) {
		//开头为0， 直接返回0
		if (s.length() == 0 || s[0] == '0') return 0;
		vector<int> dp(s.length(), 0);
		//长度为1，返回1
		if (s.length() == 1) return 1;
		//正确处理好2位数的情况， 比如 22 == 2   10 == 1   27 = 0  30 == 0
		dp[0] = s[0] > '0' && s[1] > '0' ? 1 : 0;
		dp[1] = dp[0] + ((s[0] == '1' || s[0] == '2' &&s[1] <= '6') ? 1 : 0);
		for (int i = 2; i < s.length(); ++i) {
			//当前不为0,则表示当前数字可单独存在，组合数为dp[i - 1]
			if (s[i] != '0') {
				dp[i] == dp[i - 1];
			}
			//如果当前数字和前一位可构成组合，则组合数要加上dp[i - 2]
			if (s[i - 1] == '1' || s[i - 1] == '2' && s[i] <= '6') {
				dp[i] += dp[i - 2];
			}
		}
		return dp.back();
	}
};

TEST(Dynamic, Solution91) {
	EXPECT_EQ(Solution91().numDecodings("0111"), 0);
	EXPECT_EQ(Solution91().numDecodings("26"), 2);
	EXPECT_EQ(Solution91().numDecodings("20"), 1);
}


//96. 不同的二叉搜索树
//给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？
//
//示例 :
//
//输入: 3
//	输出 : 5
//	解释 :
//	给定 n = 3, 一共有 5 种不同结构的二叉搜索树 :
//
//	1         3     3      2      1
//	\       /     /      / \      \
//	3     2     1      1   3      2
//	/     /       \                 \
//	2     1         2                 3
//执行用时: 8 ms, 在Unique Binary Search Trees的C++提交中击败了69.95% 的用户
//内存消耗 : 8.5 MB, 在Unique Binary Search Trees的C++提交中击败了5.17% 的用户
//可喜可贺，第一道完全自己解答的动态规划题
class Solution96 {
public:
	int numTrees(int n) {
		vector<int> dp(n + 1, 0);

		if (n < 3) return n;
		dp[0] = 1;
		dp[1] = 1;
		dp[2] = 2;

		for (int i = 3; i <= n; i++)
		{
			for (int j = 1; j <= i; ++j) {
				//j作为根节点
				//左子树 * 右子树
				dp[i] += dp[j - 1] * dp[i - j];
			}
		}
		return dp.back();
	}
};

TEST(Dynamic, Solution96) {
	EXPECT_EQ(Solution96().numTrees(4), 14);
}


//95. 不同的二叉搜索树 II
//给定一个整数 n，生成所有由 1 ... n 为节点所组成的二叉搜索树。
//
//示例 :
//
//输入: 3
//	输出 :
//	[
//		[1, null, 3, 2],
//		[3, 2, null, 1],
//		[3, 1, null, null, 2],
//		[2, 1, 3],
//		[1, null, 2, null, 3]
//	]
//	解释:
//	  以上的输出对应以下 5 种不同结构的二叉搜索树：
//
//		  1         3     3      2      1
//		  \       /     /      / \      \
//		  3     2     1      1   3      2
//		  /     /       \                 \
//		  2     1         2                 3
//执行用时 : 40 ms, 在Unique Binary Search Trees II的C++提交中击败了78.28% 的用户
//内存消耗: 17.3 MB, 在Unique Binary Search Trees II的C++提交中击败了18.73% 的用户
class Solution95 {
public:
	vector<TreeNode*> generateTrees(int n) {
		vector<TreeNode*> res;
		if (n < 1) {
			return res;
		}
		return recursion(1, n);
	}

	vector<TreeNode*>  recursion(int start, int end) {
		vector<TreeNode*> res;
		if (start > end) {
			res.push_back(nullptr);
		}

		for (int i = start; i <= end; ++i) {
			//以i为根节点的左子树包含的所有可能子树
			auto lefts = recursion(start, i - 1);
			//以i为根节点的右子树包含的所有可能子树
			auto rights = recursion(i + 1, end);
			for (auto left : lefts) {
				for (auto right : rights) {
					TreeNode *root = new TreeNode(i);
					root->left = left;
					root->right = right;
					res.push_back(root);
				}
			}
		}

		return res;
	}
};

TEST(Dynamic, Solution95) {
	
	auto tree = Solution95().generateTrees(3);

	string ret = "[";

	for (auto node : tree) {
		ret += TreeNodeCodec::serialize(node);
		ret += ",";
	}
	ret.back() = ']';

	EXPECT_EQ(ret, "[[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]");
}

// 120. 三角形最小路径和
//给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。
//
//例如，给定三角形：
//
//[
//	[2],
//	[3, 4],
//	[6, 5, 7],
//	[4, 1, 8, 3]
//]
//自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。
//
//说明：
//
//如果你可以只使用 O(n) 的额外空间（n 为三角形的总行数）来解决这个问题，那么你的算法会很加分
//执行用时: 16 ms, 在Triangle的C++提交中击败了51.83 % 的用户
//内存消耗 : 9.7 MB, 在Triangle的C++提交中击败了88.16 % 的用户

class Solution120 {
public:
	int minimumTotal1(vector<vector<int>>& triangle) {
		for (int i = 1; i < triangle.size(); ++i) {
			for (int j = 1; j < i; ++j) {
				triangle[i][j] += min(triangle[i - 1][j - 1], triangle[i - 1][j]);
			}

			triangle[i][0] += triangle[i - 1][0];
			triangle[i].back() += triangle[i - 1].back();
		}

		return *min_element(triangle.back().cbegin(), triangle.back().cend());
	}

	int minimumTotal(vector<vector<int>>& A) {
		int n = A.size();
		vector<int> dp(n + 1, 0);
		for (int i = n - 1; i >= 0; i--) {
			for (int j = 0; j <= i; j++) {
				dp[j] = min(dp[j], dp[j + 1]) + A[i][j];
			}
		}
		return dp[0];
	}
};

TEST(Dynamic, Solution120) {
	vector<vector<int>> in = { {2},{3,4},{6,5,7},{4,1,8,3} };

	EXPECT_EQ(11, Solution120().minimumTotal(in));
}