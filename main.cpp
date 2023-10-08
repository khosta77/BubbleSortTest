#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <ctime>
#include <unistd.h>
#include <iomanip>
#include <random>
#include <thread>
#include <cmath>
#include <unistd.h>
#include <stdlib.h> 
#include <fstream>

#include "CPUTime.h"

using namespace std;

void swap(int &A, int &B) {
	int tmp = A;
	A = B;
	B = A;
}

void BubbleSort(int *arr, const size_t &N) {
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			if (arr[i] < arr[j]) {
				swap(arr[i], arr[j]);
			}
		}
	}
}

void BubbleSortJarray(int *arr, const size_t &N) {
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < (N - 1); j++) {
			if (arr[j] < arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void BubbleSortOptimized(int *arr, const size_t &N) {
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < (N - i - 1); j++) {
			if (arr[j] < arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void BubbleSortBool(int *arr, const size_t &N) {
	for (size_t i = 0; i < N; i++) {
		bool swaped = false;
		for (size_t j = 0; j < (N - i - 1); j++) {
			if (arr[j] < arr[j + 1]) {
				swaped = true;
				swap(arr[j], arr[j + 1]);
			}
		}
		if (!swaped)
			i = N;
	}
}

void CocktailSort(int *mas, const size_t &N) {
    size_t control = N - 1;
	size_t left = 0;
    size_t right = N - 1;
    do {
        for (size_t i = left; i < right; i++) {
            if (mas[i] > mas[i + 1]) {
                swap(mas[i], mas[i + 1]);
                control = i;
            }
        }
		right = control;
        for (size_t i = right; i > left; i--) {
            if (mas[i] < mas[i - 1]) {
                swap(mas[i], mas[i - 1]);
                control = i;
            }
        }
        left = control;
	} while (left < right);
}

class BubbleTest {
private:
	size_t TEST_SIZE = 17500;

	std::vector<std::pair<std::function<void(int *arr, const size_t &N)>, std::string>> foo = {
		std::pair<std::function<void(int *arr, const size_t &N)>, std::string>(BubbleSort, std::string("BubbleSort")),
		std::pair<std::function<void(int *arr, const size_t &N)>, std::string>(BubbleSortJarray, std::string("BubbleSortJarray")),
		std::pair<std::function<void(int *arr, const size_t &N)>, std::string>(BubbleSortOptimized, std::string("BubbleSortOptimized")),
		std::pair<std::function<void(int *arr, const size_t &N)>, std::string>(BubbleSortBool, std::string("BubbleSortBool")),
		std::pair<std::function<void(int *arr, const size_t &N)>, std::string>(CocktailSort, std::string("CocktailSort")),
	};

	void generator(int *arr, const size_t &N, const int &complexity) {  // Было бы прикольно сократить эту функцию
		switch (complexity) {
			case 0: {
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dist(0, (int)N);
				for (size_t i = 0; i < N; i++) {
					*(arr + i) = dist(gen);
				}
				break;
			}
			case 1: {
				for (int i = (N - 1); i >= 0; i--) {
					*(arr + i) = i;
				}
				break;
			}
		};
	}

	void saveResult(const string &name, const vector<size_t> &X, const vector<double> &Y) {
		if (X.size() != Y.size())
			throw;
		string nm{name + ".csv"};

		ofstream out(nm, (ios::binary | ios::out));
		out << "x;y" << endl;
		for (size_t i  = 0; i < X.size(); i++) {
			out << X[i] << ";" << Y[i] << endl;
		}
		out.close();
	}

public:
	BubbleTest() {

	}

	int test() {
		string nm;
		double st, en, t;

		for (size_t i = 0; i < foo.size(); i++) {
			auto pr = foo[i];
			nm = pr.second;

			std::vector<size_t> x;
			std::vector<double> y;
			for (size_t n = 100; n <= TEST_SIZE; n += 100) {  // Будем считать, что это нормално (ужасно)
				int *arr = new int[n];
				generator(arr, n, 0);
				x.push_back(n);
				st = getCPUTime();
				pr.first(arr, n);
				en = getCPUTime();
				t = (en - st);
				y.push_back((en - st));
				delete [] arr;
			}
			cout << nm << " SUCCESS!" << endl;
			saveResult(nm, x, y);
			x.clear();
			y.clear();
		}
		return 0;
	}
};


int main() {
	BubbleTest bt;
	return  bt.test();
}


