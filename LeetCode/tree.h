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
