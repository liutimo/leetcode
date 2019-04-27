#pragma once
#include "common.h"

/***************************************������ص���***************************************/
//
//60. ��k������
//��������[1, 2, 3, ��, n]��������Ԫ�ع��� n!�����С�
//
//����С˳���г����������������һһ��ǣ��� n = 3 ʱ, �����������£�
//
//"123"
//"132"
//"213"
//"231"
//"312"
//"321"
//���� n �� k�����ص� k �����С�
//
//˵����
//
//���� n �ķ�Χ��[1, 9]��
//���� k �ķ�Χ��[1, n!]��
//ʾ�� 1:
//
//����: n = 3, k = 3
//	��� : "213"
//	ʾ�� 2 :
//
//	���� : n = 4, k = 9
//	��� : "2314"

class Solution60 {
public:

	//ִ����ʱ : 476 ms, ��Permutation Sequence��C++�ύ�л�����15.84% ���û�
	//�ڴ����� : 8.2 MB, ��Permutation Sequence��C++�ύ�л�����80.60% ���û�
	//̫���˰�
	string getPermutation1(int n, int k) {
		//�Ѿ�����n��k�ķ�Χ
		vector<char> ret(n);
		for (int i = 0; i < n; ++i) {
			ret[i] = '1' + i;
		}

		while (--k) {
			//Ϊ��͵���е�Ͷ��ȡ��
			//��δ�жϺ�������ֵ����Ϊ������֤��n��k����ȷ��
			std::next_permutation(ret.begin(), ret.end());
		}

		return string(ret.begin(), ret.end());
	}

	// ����̫�˰��Լ�
	//�ο����ͣ�https://blog.csdn.net/sinat_35261315/article/details/78412805
	//ִ����ʱ: 8 ms, ��Permutation Sequence��C++�ύ�л�����97.17% ���û�
	//�ڴ����� : 8.3 MB, ��Permutation Sequence��C++�ύ�л�����72.57% ���û�
	//
	string getPermutation(int n, int k) {
		//[1, n]һ����n!����������[1, n]��ÿ����ռ n!/n��
		//��˿��Ը���k��ȷ����k�����е�ÿһλӦ����ʲô��
		
		//1 ����n�Ľ׳�
		vector<char> dict(n + 1, '0');
		vector<int> factorialDict(n + 1, 1);
		for (int i = 1; i <= n; ++i) {
			dict[i] = '0' + i;
			factorialDict[i] = i * factorialDict[i - 1];
		}

		string ret;
		for (int i = 1; i <= n; ++i) {
			int idx = k / factorialDict[n - i];
			if (k % factorialDict[n - i] != 0)
				++idx;
			ret.push_back(dict[idx]);
			//idx �Ѿ������ˣ�����Ҫɾ��
			dict.erase(dict.begin() + idx);
			k -= (idx - 1) * factorialDict[n - i];
		}
		return ret;
	}
};