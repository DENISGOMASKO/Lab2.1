#pragma once
#include <iostream>
#include<fstream>
using namespace std;
#include <stdexcept>
#include <math.h>

#if 0
//количество последовательностей из 0 и 1 длиной N, где нет двух 1 подряд 
void kol(int& count, int last, int N) {

	if (N <= 0) {
		count++;
		return;
	}
	if (last == 1) {
		kol(count, 0, N - 1);
	}
	else {
		kol(count, 0, N - 1);
		kol(count, 1, N - 1);
	}
}

int kol1(int N) {
	if (N <= 0) throw invalid_argument("N cant be 0 and negative");
	if (N == 1) {
		return 2;
	}
	else if (N == 2) {
		return 3;
	}
	return kol1(N - 1) + kol1(N - 2);

}

int kol2(int N) {
	int nums[]{ 1, 2 };
	for (int i{ 0 }; i < N - 1; ++i) {
		nums[i % 2] += nums[1 - i % 2];
	}
	return max(nums[0], nums[1]);
}
#endif

#if 0
bool delimost(int* nums, const int& n, const int& k, int sum = 0, int i = 0) //TODO make the algorithm faster
{
	if(i == 0)
	{
		return delimost(nums, n, k, nums[0], i + 1);
	}
	if(i == n)
	{
		if (sum % k == 0) return true;
		return false;
	}
	return delimost(nums, n, k, sum + nums[i], i + 1) || delimost(nums, n, k, sum - nums[i], i + 1);
}

int main() {
	int n, k;
	cin >> n >> k;
	int* nums = new int[n];
	for (int i{ 0 }; i < n; ++i) {
		cin >> nums[i];
	}
	if (delimost(nums, n, k)) {
		cout << "Divisible" << endl;
	}else
	{
		cout << "Not divisible" << endl;
	}
	return 0;
}
#endif