#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;


template<typename T>
void printV(const T &t)
{
	for (auto iter = t.cbegin(); iter != t.cend(); ++iter) {
		std::cout << *iter << std::ends;
	}
	std::cout << std::endl;
}

template<typename T>
void printV2(const T &t)
{
	for (auto iter1 = t.cbegin(); iter1 != t.cend(); ++iter1) {
		for (auto iter = iter1->cbegin(); iter != iter1->cend(); ++iter) {
			std::cout << *iter << std::ends;
		}
		std::cout << std::endl;
	}
}


class Solution54{
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		vector<int> res;

		int left = 0, right = matrix[0].size() - 1;
		int top = 0, bottom = matrix.size() - 1;

		//topLeft -> topRightright
		while (left <= right || top <= bottom) {
			int i = left;
			while (i <= right && top <= bottom) res.push_back(matrix[top][i++]);
			i = ++top;
			while (i <= bottom && left <= right) res.push_back(matrix[i++][right]);
			i = --right;
			// BottomRight -> BottomLeft
			if (left > right) break;
			while (i >= left && top <= bottom) res.push_back(matrix[bottom][i--]);
			i = --bottom;
			while (i >= top && left <= right) res.push_back(matrix[i--][left]);
			++left;
		}
		return res;
	}
};




int main()
{
	vector<vector<int>> in = { {1, 2, 3, 4}, {5,6,7,8},{9,10,11,12} };
	auto ret = Solution54().spiralOrder(in);
	printV<decltype(ret)>(ret);

	system("pause");
	return 0;
}