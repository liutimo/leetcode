#pragma once
#include "common.h"

/***************************************����ص���***************************************/


//106. �����������������й��������
//
//����һ��������������������������������
//
//ע�� :
//����Լ�������û���ظ���Ԫ�ء�
//
//���磬����
//
//������� inorder = [9, 3, 15, 20, 7]
//������� postorder = [9, 15, 7, 20, 3]
//�������µĶ�������
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
		//���ڵ�
		TreeNode *root = new TreeNode(postorder[pE]);

		//�ҳ������и��ڵ��λ�ã������Ϊ���������ұ�Ϊ������
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

//109. ��������ת������������
//����һ�����������е�Ԫ�ذ��������򣬽���ת��Ϊ�߶�ƽ��Ķ�����������
//
//�����У�һ���߶�ƽ���������ָһ��������ÿ���ڵ� ���������������ĸ߶Ȳ�ľ���ֵ������ 1��
//
//ʾ�� :
//
//��������������[-10, -3, 0, 5, 9],
//
//һ�����ܵĴ��ǣ�[0, -3, 9, -10, null, 5], �����Ա�ʾ��������߶�ƽ�������������
//
//		   0
//		  / \
//		- 3   9
//		/    /
//	 -10    5
//ִ����ʱ: 56 ms, ��Convert Sorted List to Binary Search Tree��C++�ύ�л�����86.46% ���û�
//�ڴ����� : 24.4 MB, ��Convert Sorted List to Binary Search Tree��C++�ύ�л�����76.88% ���û�

class Solution109 {
public:
	TreeNode* sortedListToBST(ListNode* head) {
		if (!head) return nullptr;

		if (!head->next) return  new TreeNode(head->val);;
		//head��Ӧ���������򣬼��������������������������

		//���Ľڵ�
		auto *slow = head;
		auto *fast = head;
		auto *slow_prev = head;

		while (fast->next && fast->next->next)
		{
			slow_prev = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		//[-10,-3,0,5,9] , ��һ��midΪ 0��  ������Ϊ -10  -3
		//�ڶ��Σ� slow_prev = fast = fast = -10
		fast = slow->next; //���û���⺽ĸ�� -3�ͻᶪʧ
		//�´εݹ�ʱ��������յ�
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



//110. ƽ�������
//����һ�����������ж����Ƿ��Ǹ߶�ƽ��Ķ�������
//
//�����У�һ�ø߶�ƽ�����������Ϊ��
//
//һ��������ÿ���ڵ� ���������������ĸ߶Ȳ�ľ���ֵ������1��
//
//ʾ�� 1:
//
//����������[3, 9, 20, null, null, 15, 7]
//
//3
/// \
//9  20
/// \
//15   7
//���� true ��
//
//ʾ�� 2:
//
//����������[1, 2, 2, 3, 3, null, null, 4, 4]
//
//1
/// \
//2   2
/// \
//3   3
/// \
//4   4
//���� false ��
//
//ִ����ʱ: 28 ms, ��Balanced Binary Tree��C++�ύ�л�����94.02% ���û�
//�ڴ����� : 17.2 MB, ��Balanced Binary Tree��C++�ύ�л�����55.28% ���û�
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





//111. ����������С���
//����һ�����������ҳ�����С��ȡ�
//
//��С����ǴӸ��ڵ㵽���Ҷ�ӽڵ�����·���ϵĽڵ�������
//
//˵�� : Ҷ�ӽڵ���ָû���ӽڵ�Ľڵ㡣
//
//	ʾ�� :
//
//����������[3, 9, 20, null, null, 15, 7],
//
//3
/// \
//9  20
/// \
//15   7
//����������С���  2.
//ִ����ʱ: 40 ms, ��Minimum Depth of Binary Tree��C++�ύ�л�����39.05% ���û�
//�ڴ����� : 20.4 MB, ��Minimum Depth of Binary Tree��C++�ύ�л�����5.06% ���û�
class Solution111 {
public:
	int minDepth(TreeNode* root) {
		if (!root) {
			return 0;
		}
		//˵����ΪҶ�ӽڵ�
		if (!root->left && !root->right) {
			return 1;
		}

		//��һ����Ϊ��
		if ((root->left == nullptr) ^ (root->right == nullptr)) {
			return  max(minDepth(root->left), minDepth(root->right)) + 1;
		}
		//����Ϊ��
		return min(minDepth(root->left), minDepth(root->right)) + 1;
	}
};


TEST(Tree, Solution111) {
	//�������ĺ����ƺ��е�����
	EXPECT_EQ(2, Solution111().minDepth(TreeNodeCodec::deserialize("[1, 9]")));
}
//
//112. ·���ܺ�
//����һ����������һ��Ŀ��ͣ��жϸ������Ƿ���ڸ��ڵ㵽Ҷ�ӽڵ��·��������·�������нڵ�ֵ��ӵ���Ŀ��͡�
//
//˵�� : Ҷ�ӽڵ���ָû���ӽڵ�Ľڵ㡣
//
//	ʾ�� :
//�������¶��������Լ�Ŀ��� sum = 22��
//
//5
/// \
//4   8
///   / \
//11  13  4
/// \      \
//7    2      1
//���� true, ��Ϊ����Ŀ���Ϊ 22 �ĸ��ڵ㵽Ҷ�ӽڵ��·�� 5->4->11->2��

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
	//�������ĺ����ƺ��е�����
	EXPECT_EQ(true, Solution112().hasPathSum(TreeNodeCodec::deserialize("[1,2,3,4,5,6,]"), 7));
	EXPECT_EQ(false, Solution112().hasPathSum(TreeNodeCodec::deserialize("[1,2,3,4,5,6]"), 4));
	EXPECT_EQ(false, Solution112().hasPathSum(TreeNodeCodec::deserialize("[1,2,3,4,5,6,7]"), 0));
}

//113. ·���ܺ� II
//����һ����������һ��Ŀ��ͣ��ҵ����дӸ��ڵ㵽Ҷ�ӽڵ�·���ܺ͵��ڸ���Ŀ��͵�·����
//
//˵�� : Ҷ�ӽڵ���ָû���ӽڵ�Ľڵ㡣
//
//	ʾ�� :
//�������¶��������Լ�Ŀ��� sum = 22��
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
	//�������ĺ����ƺ��е�����
	auto ret = Solution113().pathSum(TreeNodeCodec::deserialize("[1,2,3,4,5,6,7]"), 7);
	decltype(ret) ret1;
	vector<int> one = { 1, 2, 4 };
	ret1.emplace_back(one);
	EXPECT_EQ(ret1, ret);
}


//114. ������չ��Ϊ����
//����һ����������ԭ�ؽ���չ��Ϊ����
//
//���磬����������
//
//    1
//   / \
//  2   5
// / \   \
//3   4   6
//����չ��Ϊ��
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
//ִ����ʱ : 12 ms, ��Flatten Binary Tree to Linked List��C++�ύ�л�����97.09% ���û�
//�ڴ�����: 9.8 MB, ��Flatten Binary Tree to Linked List��C++�ύ�л�����76.11 % ���û�
//

class Solution114 {
public:
	void flatten(TreeNode* root) {
		TreeNode* tail = nullptr;
		buildChildTree(root, tail);
	}


	void buildChildTree(TreeNode* root, TreeNode*& tail) {
		if (root->right && !root->left) { //��������Ϊ��
			buildChildTree(root->right, tail);
		}
		else if (root->left && !root->right){  //������Ϊ��
			root->right = root->left;
			buildChildTree(root->left, tail);
			root->left = nullptr;
		}
		else if (!root->left && !root->right){
			//����������Ϊ��
			tail = root;
		}
		else {
			//������������Ϊ��
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
//116. ���ÿ���ڵ����һ���Ҳ�ڵ�ָ��
//����һ��������������������Ҷ�ӽڵ㶼��ͬһ�㣬ÿ�����ڵ㶼�������ӽڵ㡣�������������£�
//
//struct Node {
//	int val;
//	Node* left;
//	Node* right;
//	Node* next;
//}
//�������ÿ�� next ָ�룬�����ָ��ָ������һ���Ҳ�ڵ㡣����Ҳ�����һ���Ҳ�ڵ㣬�� next ָ������Ϊ NULL��
//
//��ʼ״̬�£����� next ָ�붼������Ϊ NULL��
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

//117. ���ÿ���ڵ����һ���Ҳ�ڵ�ָ�� II
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

		//����������������
		connect(root->right);
		connect(root->left);
		return root;
	}

	void recursion(Node* root) {

	}
};