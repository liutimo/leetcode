#include "array.h"
#include "permutation.h"
#include "list.h"
#include "dynamicprogramming.h"
int main()
{
	//
	//vector<vector<int>> in = { {1, 2, 3, 4}, {5,6,7,8},{9,10,11,12} };
	//auto ret = Solution54().spiralOrder(in);
	//printV<decltype(ret)>(ret);

	//auto ret = Solution59().generateMatrix(9);
	//printV2<decltype(ret) > (ret);


	//auto ret = Solution60().getPermutation(6, 6);
	//printV<decltype(ret)>(ret);

	//ListNode *head = new ListNode(0);
	//head->next = new ListNode(1);
	//head->next->next = new ListNode(2);
	//printList(Solution61().rotateRight(head, 0));

	/*print<int>(Solution62().uniquePaths(70, 30));*/

	//vector<vector<int>> vec = { { 0,0,0, 0,1,0 },{ 0,1,0,0,0, 0 },{ 0,0,0,0,0, 0 } };
	//print<int>(Solution63().uniquePathsWithObstacles(vec));

	vector<vector<int>> vec = { { 1,3,1 },{ 1,5,1 },{ 4,2,1 } };
	print<int>(Solution64().minPathSum(vec));

	system("pause");
	return 0;
}