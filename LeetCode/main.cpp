#include "array.h"
#include "permutation.h"

int main()
{
	//
	//vector<vector<int>> in = { {1, 2, 3, 4}, {5,6,7,8},{9,10,11,12} };
	//auto ret = Solution54().spiralOrder(in);
	//printV<decltype(ret)>(ret);

	//auto ret = Solution59().generateMatrix(9);
	//printV2<decltype(ret) > (ret);


	auto ret = Solution60().getPermutation(6, 6);
	printV<decltype(ret)>(ret);
	system("pause");
	return 0;
}