#pragma once
/***************************************������ص���***************************************/
#include "common.h"

//
//39. ����ܺ�
//����һ�����ظ�Ԫ�ص����� candidates ��һ��Ŀ���� target ���ҳ� candidates �����п���ʹ���ֺ�Ϊ target ����ϡ�
//
//candidates �е����ֿ����������ظ���ѡȡ��
//
//˵����
//
//�������֣����� target��������������
//�⼯���ܰ����ظ�����ϡ�
//ʾ�� 1:
//
//����: candidates = [2, 3, 6, 7], target = 7,
//	����⼯Ϊ :
//	[
//		[7],
//		[2, 2, 3]
//	]
//	ʾ�� 2 :
//
//		���� : candidates = [2, 3, 5], target = 8,
//		����⼯Ϊ :
//		[
//			[2, 2, 2, 2],
//			[2, 3, 3],
//			[3, 5]
//		]
//
class Solution39 {
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end());
		vector<int> res;
		vector<vector<int>> ret;
		resF(0, 0, res, target, ret, candidates);
		return ret;
	}

	void resF(int j, int currValue, vector<int> res, int target, vector<vector<int>> &ress, vector<int>& candidates)
	{
		if (target == currValue) {
			ress.push_back(res);
			return;
		}
		else if (currValue > target) {
			return;;
		}
		for (int i = j; i < candidates.size(); ++i) {
			if (currValue + candidates[i] > target) {
				return;
			}
			res.push_back(candidates[i]);
			resF(i, currValue + candidates[i], res, target, ress, candidates);
			res.pop_back();
		}
	}
};

//
//40. ����ܺ� II
//����һ������ candidates ��һ��Ŀ���� target ���ҳ� candidates �����п���ʹ���ֺ�Ϊ target ����ϡ�
//
//candidates �е�ÿ��������ÿ�������ֻ��ʹ��һ�Ρ�
//
//˵����
//
//�������֣�����Ŀ������������������
//�⼯���ܰ����ظ�����ϡ�
//ʾ�� 1:
//
//����: candidates = [10, 1, 2, 7, 6, 1, 5], target = 8,
//	����⼯Ϊ :
//	[
//		[1, 7],
//		[1, 2, 5],
//		[2, 6],
//		[1, 1, 6]
//	]
//	ʾ�� 2:
//
//����: candidates = [2, 5, 2, 1, 2], target = 5,
//	����⼯Ϊ :
//	[
//		[1, 2, 2],
//		[5]
//	]

class Solution40 {
public:
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		//ʹ��setȥ�ء��Ż��㣬
		set<vector<int>> ret;
		vector<int> res;
		sort(candidates.begin(), candidates.end());
		resF(0, 0, res, target, ret, candidates);
		return vector<vector<int>>(ret.cbegin(), ret.cend());
	}

	void resF(int j, int currValue, vector<int> res, int target, set<vector<int>> &ress, vector<int>& candidates)
	{
		if (target == currValue) {
			ress.insert(res);
			return;
		}
		else if (currValue > target) {
			return;
		}
		for (int i = j; i < candidates.size(); ++i) {
			if (currValue + candidates[i] > target) {
				return;
			}

			//�Ż��㣬��set��Ϊvector���ɡ�
			//���� 1,1,1,1,1,1,2  target Ϊ2
			//���ڵ�һ��1,�ܹ��ó�2�������1��û����ֱ�ӵ�2
			//if (j < i && candidates[i - 1] == candidates[i]) continue;

			res.push_back(candidates[i]);
			//i + 1�������ظ�ʹ��һ����
			resF(i + 1, currValue + candidates[i], res, target, ress, candidates);
			res.pop_back();
		}
	}
};