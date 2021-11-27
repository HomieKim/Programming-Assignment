#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

/* 비복원 나눗셈 구현*/

vector<int> Q;
int divisor_arr[16];
int dividend_arr[16];
int minus_divisor_arr[16];
void output_arr(int* arr, int size) {

	for (int i = 0; i < size; i++) {
		if (i != 0 && i % 4 == 0) cout << " ";
		cout << arr[i];
	}
	cout << endl;

}

void one_complement(int* binary_arr) {

	for (int i = 0; i < 16; i++) {
		if (binary_arr[i] == 0) {
			binary_arr[i] = 1;
		}
		else {
			binary_arr[i] = 0;
		}
	}
	
}
void two_complement(int* binary_arr) {
	int upper = 0;
	for (int i = 16 - 1; i >= 0; i--) {
		if (upper == 0) {
			if (binary_arr[i] == 0) {
				binary_arr[i] = 1;
				break;
			}
			else {
				binary_arr[i] = 0;
				upper = 1;
			}

		}
		else {
			if (binary_arr[i] == 0) {
				binary_arr[i] = 1;
				upper = 0;
				break;
			}
			else {
				binary_arr[i] = 0;
				upper = 1;
			}
		}
	}

}
void to_binary(int number, int* arr) {
	int flag = 0;
	if (number < 0) {
		number *= -1;
		flag = 1;
	}
	for (int i = 0; i < 16; i++) {
		arr[i] = 0;
	}
	int idx = 16;
	int mok, nmg;
	do {
		idx--;
		mok = number / 2;
		nmg = number % 2;
		arr[idx] = nmg;
		number = mok;
	} while (mok != 0);

	if (flag == 1) {
		one_complement(arr);
		two_complement(arr);
	}
}
int b_to_d(string s1) {
	int rst = 0;
	for (int i = 0; i < s1.size(); i++) {
		if (s1[i] == '1') {
			rst += pow(2, (s1.size() - 1) - i);
		}
	}
	return rst;
}



void non_restoring_divide(int divisor, int dividend, int cnt) {
	if (cnt == 9) return;
	cout << endl;
	cout << "### step " << cnt << " ###" << endl;
	printf("%-5s", "<<");
	cout << " Dividend Left Shift" << endl;
	dividend <<= 1;
	to_binary(dividend, dividend_arr);
	if (dividend >= 0) {
		cout << "현재 부분 나머지가 양수 입니다. 제수를 뺍니다." << endl;
		printf("%-13s", "부분 나머지");
		output_arr(dividend_arr, 16);
		printf("%13s", "+");
		output_arr(minus_divisor_arr, 8);
		dividend = dividend - divisor;
	}
	else {
		cout << "현재 부분 나머지가 음수 입니다. 제수를 더합니다." << endl;
		printf("%-13s", "부분 나머지");
		output_arr(dividend_arr, 16);
		printf("%13s", "+");
		output_arr(divisor_arr, 8);
		dividend = dividend + divisor;
	}
	cout << "------------------------" << endl;
	to_binary(dividend, dividend_arr);
	printf("%-13s", "부분 나머지");
	output_arr(dividend_arr, 16);
	if (dividend >= 0) {
		cout << "연산 결과 양수 입니다. 몫에 1을추가 합니다." << endl;
		Q.push_back(1);
	}
	else {
		cout << "연산 결과 음수 입니다. 몫에 0을추가 합니다." << endl;
		Q.push_back(0);
	}
	cout << "현재 몫 : ";
	for (auto a : Q) {
		cout << a;
	}
	cout << endl;
	non_restoring_divide(divisor, dividend, ++cnt);
}
int main() {
	string divisor;	// 제수, 나누는수
	string dividend; // 피제수, 나누어 지는 수
	
	cout << "16bit 피제수 입력 : ";
	cin >> dividend;
	cout << "8bit 제수 입력 : ";
	cin >> divisor;
	int de_divisor = b_to_d(divisor);
	int de_dividend = b_to_d(dividend);
	de_divisor <<= 8;
	to_binary(de_divisor, divisor_arr);
	to_binary(de_divisor * -1, minus_divisor_arr);
	non_restoring_divide(de_divisor, de_dividend,1);
	cout << endl;
	cout << "*** 결과 ***" << endl;
	cout << "몫 : ";
	for (int i = 0; i < Q.size(); i++) {
		if (i != 0 && i % 4 == 0) cout << " ";
		cout << Q[i];
	}
	cout << endl;
	cout << "나머지 : ";
	output_arr(dividend_arr, 8);
	cout << endl;

}