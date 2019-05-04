#pragma once
#include "common.h"

/***************************************树相关的题***************************************/


//106. 从中序与后序遍历序列构造二叉树
//
//根据一棵树的中序遍历与后序遍历构造二叉树。
//
//注意 :
//你可以假设树中没有重复的元素。
//
//例如，给出
//
//中序遍历 inorder = [9, 3, 15, 20, 7]
//后序遍历 postorder = [9, 15, 7, 20, 3]
//返回如下的二叉树：
//
//  		 3
//			/ \
//		   9  20
//			  / \
//			15   7

class Solution106 {
	using Iter = vector<int>::const_iterator;
public:
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		if (inorder.size() != postorder.size()) return nullptr;
		if (inorder.size() == 0 || postorder.size() == 0) return nullptr;

		return buildTree(0, inorder.size() - 1, 0, postorder.size() - 1, inorder, postorder);
	}

	TreeNode* buildTree(int inS, int inE, int pS, int pE,
		const vector<int>& inorder, const vector<int>& postorder) {

		if (inS > inE) return nullptr;
		//根节点
		TreeNode *root = new TreeNode(postorder[pE]);

		//找出中序中根节点的位置，其左边为左子树，右边为右子树
		int inR = find(inorder.cbegin() + inS, inorder.cbegin() + inE + 1, postorder[pE]) - inorder.cbegin();
		//inorder  l:[inS, inR-1]   r: [inR + 1, iE);

		if (inS != inE) {
			root->left = buildTree(inS, inR - 1, pS, pS + inR - inS - 1, inorder, postorder);
		}
		else {
			root->left = nullptr;
		}

		if (pS != pE) {
			root->right = buildTree(inR + 1, inE, pS + inR - inS, pE - 1, inorder, postorder);
		}
		else {
			root->right = nullptr;
		}
		return root;
	}
};



TEST(Tree, Solution106) {
	/*auto inorder = stringToIntegerVector("[9, 3, 15, 20, 7]");
	auto postorder = stringToIntegerVector("[9, 15, 7, 20, 3]");*/
	auto inorder = stringToIntegerVector("[2,1]");
	auto postorder = stringToIntegerVector("[2,1]");
	auto res = TreeNodeCodec::serialize(Solution106().buildTree(inorder, postorder));
	EXPECT_EQ(res, "[1,2]");
}

//109. 有序链表转换二叉搜索树
//给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。
//
//本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。
//
//示例 :
//
//给定的有序链表：[-10, -3, 0, 5, 9],
//
//一个可能的答案是：[0, -3, 9, -10, null, 5], 它可以表示下面这个高度平衡二叉搜索树：
//
//		   0
//		  / \
//		- 3   9
//		/    /
//	 -10    5
//执行用时: 56 ms, 在Convert Sorted List to Binary Search Tree的C++提交中击败了86.46% 的用户
//内存消耗 : 24.4 MB, 在Convert Sorted List to Binary Search Tree的C++提交中击败了76.88% 的用户

class Solution109 {
public:
	TreeNode* sortedListToBST(ListNode* head) {
		if (!head) return nullptr;

		if (!head->next) return  new TreeNode(head->val);;
		//head对应的链表有序，即根据中序遍历构建二叉搜索树

		//中心节点
		auto *slow = head;
		auto *fast = head;
		auto *slow_prev = head;

		while (fast->next && fast->next->next)
		{
			slow_prev = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		//[-10,-3,0,5,9] , 第一次mid为 0，  左子树为 -10  -3
		//第二次， slow_prev = fast = fast = -10
		fast = slow->next; //如果没有这航母， -3就会丢失
		//下次递归时，链表的终点
		slow_prev->next = nullptr;
		TreeNode *root = new TreeNode(slow->val);
		if (head != slow) {
			root->left = sortedListToBST(head);
		}
		root->right = sortedListToBST(fast);

		return root;
	}

};

TEST(Tree, Solution109) {
	
	auto *head = stringToListNode("[-10,-3,0,5,9]");
	auto *root = Solution109().sortedListToBST(head);

	EXPECT_EQ(TreeNodeCodec::serialize(root), "[0,-10,5,null,-3,null,9]");
}



//110. 平衡二叉树
//给定一个二叉树，判断它是否是高度平衡的二叉树。
//
//本题中，一棵高度平衡二叉树定义为：
//
//一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。
//
//示例 1:
//
//给定二叉树[3, 9, 20, null, null, 15, 7]
//
//3
/// \
//9  20
/// \
//15   7
//返回 true 。
//
//示例 2:
//
//给定二叉树[1, 2, 2, 3, 3, null, null, 4, 4]
//
//1
/// \
//2   2
/// \
//3   3
/// \
//4   4
//返回 false 。
//
//执行用时: 28 ms, 在Balanced Binary Tree的C++提交中击败了94.02% 的用户
//内存消耗 : 17.2 MB, 在Balanced Binary Tree的C++提交中击败了55.28% 的用户
class Solution110 {
public:
	bool isBalanced(TreeNode* root) {
		if (!root) return  true;
		int deepth = 0;
		return recursion(root, deepth);
	}

	bool recursion(TreeNode* root, int &deepth) {
		if (!root) {
			deepth = 0;
			return true;
		}

		int lDeepth = 0;
		int rDeepth = 0;
		bool left = recursion(root->left, lDeepth);
		bool right = recursion(root->right, rDeepth);

		deepth = max(lDeepth, rDeepth) + 1;

		if (!left || !right) {
			return false;
		}

		return abs(lDeepth - rDeepth) <= 1;
	}
};

TEST(Tree, Solution110) {

	auto *head = TreeNodeCodec::deserialize("[1,2,2,3,3,null,null,4,4]");

	EXPECT_EQ(Solution110().isBalanced(head), false);

	EXPECT_EQ(Solution110().isBalanced(TreeNodeCodec::deserialize("[3,9,20,null,null,15,7]")), true);
}





//111. 二叉树的最小深度
//给定一个二叉树，找出其最小深度。
//
//最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
//
//说明 : 叶子节点是指没有子节点的节点。
//
//	示例 :
//
//给定二叉树[3, 9, 20, null, null, 15, 7],
//
//3
/// \
//9  20
/// \
//15   7
//返回它的最小深度  2.
//执行用时: 40 ms, 在Minimum Depth of Binary Tree的C++提交中击败了39.05% 的用户
//内存消耗 : 20.4 MB, 在Minimum Depth of Binary Tree的C++提交中击败了5.06% 的用户
class Solution111 {
public:
	int minDepth(TreeNode* root) {
		if (!root) {
			return 0;
		}
		//说明其为叶子节点
		if (!root->left && !root->right) {
			return 1;
		}

		//有一个不为空
		if ((root->left == nullptr) ^ (root->right == nullptr)) {
			return  max(minDepth(root->left), minDepth(root->right)) + 1;
		}
		//都不为空
		return min(minDepth(root->left), minDepth(root->right)) + 1;
	}
};


TEST(Tree, Solution111) {
	//生成树的函数似乎有点问题
	EXPECT_EQ(2, Solution111().minDepth(TreeNodeCodec::deserialize("[1, 9]")));
}
//
//112. 路径总和
//给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。
//
//说明 : 叶子节点是指没有子节点的节点。
//
//	示例 :
//给定如下二叉树，以及目标和 sum = 22，
//
//5
/// \
//4   8
///   / \
//11  13  4
/// \      \
//7    2      1
//返回 true, 因为存在目标和为 22 的根节点到叶子节点的路径 5->4->11->2。

class Solution112 {
public:
	bool hasPathSum(TreeNode* root, int sum) {
		if (!root) return false;

		sum -= root->val;
		if (root->left && root->right)
			return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);

		if (root->right) {
			return hasPathSum(root->right, sum);
		}

		if (root->left) {
			return hasPathSum(root->left, sum);
		}
		return sum == 0;
	}
};

TEST(Tree, Solution112) {
	//生成树的函数似乎有点问题
	EXPECT_EQ(true, Solution112().hasPathSum(TreeNodeCodec::deserialize("[1,2,3,4,5,6,]"), 7));
	EXPECT_EQ(false, Solution112().hasPathSum(TreeNodeCodec::deserialize("[1,2,3,4,5,6]"), 4));
	EXPECT_EQ(false, Solution112().hasPathSum(TreeNodeCodec::deserialize("[1,2,3,4,5,6,7]"), 0));
}

//113. 路径总和 II
//给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。
//
//说明 : 叶子节点是指没有子节点的节点。
//
//	示例 :
//给定如下二叉树，以及目标和 sum = 22，
//
//			  5
//			 / \
//			4   8
//		   /   / \
//		  11  13  4
//		 /  \    / \
//		7    2  5   1


class Solution113 {
public:
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		vector<vector<int>> ret;
		if (!root) return {};

		vector<int> path;
		dfs(ret, path, root, sum);
		return ret;
	}

	void dfs(vector<vector<int>>& res, vector<int> path, TreeNode* root, int sum) {
		path.push_back(root->val);
		sum -= root->val;
		if (root->right) {
			dfs(res, path, root->right, sum);
		}

		if (root->left) {
			dfs(res, path, root->left, sum);
		}

		if (sum == 0 && !root->left && !root->right) {
			res.emplace_back(path);
		}
	}
};

TEST(Tree, Solution113) {
	//生成树的函数似乎有点问题
	auto ret = Solution113().pathSum(TreeNodeCodec::deserialize("[1,2,3,4,5,6,7]"), 7);
	decltype(ret) ret1;
	vector<int> one = { 1, 2, 4 };
	ret1.emplace_back(one);
	EXPECT_EQ(ret1, ret);
}


//114. 二叉树展开为链表
//给定一个二叉树，原地将它展开为链表。
//
//例如，给定二叉树
//
//    1
//   / \
//  2   5
// / \   \
//3   4   6
//将其展开为：
//
//1
// \
//  2
//   \
//    3
//     \
//      4
//       \
//        5
//         \
//          6
//执行用时 : 12 ms, 在Flatten Binary Tree to Linked List的C++提交中击败了97.09% 的用户
//内存消耗: 9.8 MB, 在Flatten Binary Tree to Linked List的C++提交中击败了76.11 % 的用户
//

class Solution114 {
public:
	void flatten(TreeNode* root) {
		TreeNode* tail = nullptr;
		buildChildTree(root, tail);
	}


	void buildChildTree(TreeNode* root, TreeNode*& tail) {
		if (root->right && !root->left) { //右子树不为空
			buildChildTree(root->right, tail);
		}
		else if (root->left && !root->right){  //右子树为空
			root->right = root->left;
			buildChildTree(root->left, tail);
			root->left = nullptr;
		}
		else if (!root->left && !root->right){
			//左右子树都为空
			tail = root;
		}
		else {
			//左右子树都不为空
			TreeNode* left_tail = nullptr;
			buildChildTree(root->left, left_tail);
			buildChildTree(root->right, tail);
			left_tail->right = root->right;
			root->right = root->left;
			root->left = nullptr;
		}
	}
};

TEST(Tree, Solution114) {
	auto* root = TreeNodeCodec::deserialize("[1,2,5,3,4,null,6]");

	Solution114().flatten(root);

	vector<int> ret;
	while (root) {
		ret.push_back(root->val);
		root = root->right;
	}
	vector<int> res = {1,2,3,4,5,6};

	EXPECT_EQ(ret, res);
}
//
//116. 填充每个节点的下一个右侧节点指针
//给定一个完美二叉树，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：
//
//struct Node {
//	int val;
//	Node* left;
//	Node* right;
//	Node* next;
//}
//填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。
//
//初始状态下，所有 next 指针都被设置为 NULL。
class Solution116 {
public:
	Node* connect1(Node* root) {
		if (!root) return root;

		auto* nr = root;

		while (root->left) {
			auto* curr = root;
			while (curr) {
				curr->left->next = curr->right;
				if (curr->next) {
					curr->right->next = curr->next->left;
				}
				curr = curr->next;
			}
			root = root->left;
		}
		return nr;
	}


	void recursion(Node* root) {
		if (root == nullptr) return;

		if (root->right == nullptr && root->left == nullptr) return;

		root->left->next = root->right;
		if (root->next) {
			root->right->next = root->next->left;
		}
		else {
			root->right->next = nullptr;
		}

		recursion(root->left);
		recursion(root->right);
	}
};

//117. 填充每个节点的下一个右侧节点指针 II
//https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node-ii/
/*
// Definition for a Node.
class Node {
public:
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node() {}

	Node(int _val, Node* _left, Node* _right, Node* _next) {
		val = _val;
		left = _left;
		right = _right;
		next = _next;
	}
};
*/
class Solution117 {
public:
	Node* connect(Node* root) {
		if (!root) return root;

		auto* next = root->next;
		while (next) {
			//    if (next->right || next->left) {
			//        break;
			//    }

			if (next->left) {
				next = next->left;
				break;
			}
			if (next->right) {
				next = next->right;
				break;
			}
			next = next->next;
		}
		if (root->right) root->right->next = next;
		if (root->left) root->left->next = root->right ? root->right : next;

		//必须先连接右子树
		connect(root->right);
		connect(root->left);
		return root;
	}

	void recursion(Node* root) {

	}
};