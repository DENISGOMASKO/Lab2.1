#include <iostream>

using namespace std;
#include "list.h"

int main() {
	list arr;
	for (int i{0}; i < 10; ++i) arr.push_back(i);


	for (int i{ 0 }; i < arr.len(); ++i) {
		cout << arr.element(i) << " ";
	}

	cout << arr.len();
	return 0;	
}