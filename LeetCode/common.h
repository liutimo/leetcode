#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include<iomanip>
#include <algorithm>
using namespace std;

//´òÓ¡Ò»Î¬ÈÝÆ÷
template<typename T>
void printV(const T &t)
{
	for (auto iter = t.cbegin(); iter != t.cend(); ++iter) {
		std::cout << *iter << std::ends;
	}
	std::cout << std::endl;
}

//´òÓ¡¶þÎ¬ÈÝÆ÷
template<typename T>
void printV2(const T &t)
{
	for (auto iter1 = t.cbegin(); iter1 != t.cend(); ++iter1) {
		for (auto iter = iter1->cbegin(); iter != iter1->cend(); ++iter) {
			std::cout << setw(4) << setfill(' ') << *iter << std::ends;
		}
		std::cout << std::endl;
	}
}