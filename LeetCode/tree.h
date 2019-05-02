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