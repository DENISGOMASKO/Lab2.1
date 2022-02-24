#include <iostream>

using namespace std;
#include <list>
#include <string>
#include <fstream>
#include <iterator>

void print_arr_of_num(const int* arr, const int len, bool ret = true){
	for (int i{ 0 }; i < len; ++i) {
		cout << arr[i] << ' ';
	}

	if (!ret) {
		cout << "len: " << len;
	}
	cout << endl;
}

int cnt_digits(int num) { return (num /= 10) ? 1 + cnt_digits(num) : 1; }

int* read_str_of_num(int &len) {

	string str;
	
	getline(cin, str);

	int str_len{ (int)str.length() };
	int* arr = new int[0];

	len = 0;
	for (int i{ 0 }; i < str_len;) {
		while (str[i] == ' ') {
			i++;
			if (i >= str_len) return arr;
		}
		int last_position = len;
		len++;
		int* tmp = new int[len];

		memcpy(tmp, arr, last_position *sizeof(int));
		tmp[last_position] = stoi(&str[i]);

		i += cnt_digits(tmp[last_position]);
		if (tmp[last_position] < 0) i++;
		delete[] arr;
		arr = tmp;

	}
	return arr;
}

int quantity_of_negative_multiples(const int* arr, const int len, const int num = 1) {

	int qual{ 0 };
	for (int i{ 0 }; i < len; ++i) {
		if (arr[i] < 0 && arr[i] % num == 0) {
			qual++;
		}
	}
	return qual;
}

int sum_of_arr(const int* arr, const int len) {
	int sum{0};
	for (int i{ 0 }; i < len; ++i) sum += arr[i];
	return sum;
}

void remove_element(int* arr, int &len, int num) {
	
	try {
		if (num < 0 || num >= len) {
			throw num;
		}
	}
	catch(int n) {
		cerr << "number " << n << " is invalid!" << endl;
	}
	for (int i{ num }; i < len-1; ++i) { arr[i] = arr[i + 1]; }
	int* tmp = new int[len--];
	
	memcpy(tmp, arr, len * sizeof(int));
	
	//delete[] arr;
	arr = tmp;

}

void remove_all_repetitions(int* arr, int &len) {
	for (int i{ 0 }; i < len; ++i) {
		for (int j{ i + 1 }; j < len; ) {
			if (arr[i] == arr[j]) {
				remove_element(arr, len, j);
			}
			else {
				j++;
			}
		}
	}
}

void remove_consecutive_repetitions(int* arr, int &len) {
	for (int i{ 0 }; i < len-1; ++i) {
		while (i + 1 < len && arr[i + 1] == arr[i]) {
			remove_element(arr, len, i+1);
		}
	}
}

void remove_value(int* arr, int &len, int val, int deviation = 0) {
	int start{0};
	int end{0};
	if (deviation > 0) end = deviation; else start = -deviation;
	for (int i{start}; i < len- end; ++i) {
		if (arr[i] == val) remove_element(arr, len, i+deviation);
	}
}

void swap_values(int &a, int &b) {
	int iTemp{a};
	a = b;
	b = iTemp;
}

void flip_arr(int* arr, const int len) {
	for (int i{ 0 }; i < (len / 2); ++i) {
		swap_values(arr[i], arr[len - 1 - i]);
	}
}

void make_tr(int* arr, const int len, int num) {
	int kos{ num * 2 + 1 };
	if (kos + 1 < len) {
		int kos_true{ arr[kos] > arr[kos + 1] ? kos : kos + 1 };
		if (arr[kos_true] > arr[num]) {

			swap_values(arr[kos_true], arr[num]);
			make_tr(arr, len, kos_true);
		}
	}
	else if (kos < len) {
		if (arr[kos] > arr[num]) {
			swap_values(arr[kos], arr[num]);
		}
	}
}
void sort_pyramide(int* arr, const int len) {
	for (int i{ (len - 1) % 2 == 0 ? int((len - 3) / 2) : int((len - 2) / 2) }; i >= 0; --i) {
		make_tr(arr, len, i);
	}
	swap_values(arr[0], arr[len - 1]);

	if (len > 1) {
		sort_pyramide(arr, len - 1);
	}
}

int Josephs_task(const int N, const int K) {
	int len{ N }, num{0};
	int* group = new int[len];
	
	for (int i{ 0 }; i <= N; ++i) group[i] = i+1;
	while (len > 1) {
		num += K - 1;
		if (num >= len) num -= len;
		remove_element(group, len, num);
		
	}
	//print_arr_of_num(group, len);
	return group[0];
}

void add_arr_to_arr(int* &main_arr, int &main_len, int* added_arr, const int added_len) {
	int* tmp = new int[main_len];
	memcpy(tmp, main_arr, main_len * sizeof(int));


	delete[] main_arr;
	int len = main_len;

	main_len += added_len;

	main_arr = new int[main_len];

	memcpy(main_arr, tmp, len * sizeof(int));

	memcpy(&main_arr[len], added_arr, added_len * sizeof(int));

	/*for (int i{0}; i < added_len; ++i) {
		main_arr[len+i] = added_arr[i];
	}*/
}

int main() {
	




	int len1, len2;
	int* a1 = read_str_of_num(len1);
	int* a2 = read_str_of_num(len2);

	print_arr_of_num(a1, len1);
	print_arr_of_num(a2, len2);

	add_arr_to_arr(a1, len1, a2, len2);

	print_arr_of_num(a1, len1);
	

	delete[] a1;
	delete[] a2;
	return 0;
}