#include <iostream>
#include <string>
#include <cstring>
#include <math.h>


/*
부가점 관련 주석
	- GUI없이 콘솔환경에서 실행합니다.
	- 양수 음수 모두 처리가능합니다
	- 0의 경우 따로 처리합니다. (+0, -0, 0 입력가능 하나 -0의경우 1의 보수 부호-크기 방식의 내용만 출력합니다.)
	- 프로그램 실행 중에 입력을 받아서 프로그램크기 (bit 수)를 정합니다. 8, 16, 32, 64 외에는 예외처리 합니다.
*/


#define ll long long
#define MAX 64

using namespace std;
int binary_arr[MAX];
ll BIT;

void output_arr(int* arr) {

	
	for (int i = 0; i < BIT; i++) {
		if (i != 0 && i % 4 == 0) cout << " ";
		cout << arr[i];
	}
	cout << endl;

}
void signed_magnitude() {
	int arr_[MAX];
	memcpy(arr_, binary_arr, sizeof(binary_arr));
	arr_[0] = 1;
	output_arr(arr_);
}
void one_complement() {
	
	for (int i = 0; i < BIT; i++) {
		if (binary_arr[i] == 0) {
			binary_arr[i] = 1;
		}
		else {
			binary_arr[i] = 0;
		}
	}
	output_arr(binary_arr);
}
void two_complement() {
	int upper = 0;
	for (int i = BIT-1; i >= 0; i--) {
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
	output_arr(binary_arr);
}
void to_binary(ll number) {
	int idx = BIT;
	ll mok, nmg;
	do {
		idx--;
		mok = number / 2;
		nmg = number%2;
		binary_arr[idx] = nmg;
		number = mok;
	} while (mok != 0);
}
void zero_process(string input) {
	for (int i = 0; i < 12 + BIT + (BIT / 4 - 1); i++) {
		cout << "#";
	}
	cout << endl;
	if (input == "-0") {
		printf("%12s", "부호-크기 : "); signed_magnitude();
		printf("%12s", "1의 보수 : "); one_complement();
	}
	else {
		printf("%12s", "부호-크기 : "); output_arr(binary_arr);
		printf("%12s", "2의 보수 : "); output_arr(binary_arr);
		printf("%12s", "1의 보수 : "); output_arr(binary_arr);
	}
	for (int i = 0; i < 12 + BIT + (BIT / 4 - 1); i++) {
		cout << "#";
	}
	cout << endl << endl;
}

ll number;


int main() {
	
	string input;
	
	cout << "프로그램 크기를 입력하세요(8bit, 16bit, 32bit, 64bit)" << endl;
	
	
	while (true) {
		cout << "bit 수 입력 : ";
		cin >> BIT;
		
		if (BIT == 8 || BIT == 16 || BIT == 32 || BIT == 64) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << endl;
			break;
		}
		else {
			cout << "잘못된 입력입니다. 8, 16, 32, 64 bit 입력가능 " << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		cout << endl;
		
	}
	cout << "** "<<BIT << "bit 10진수 변환 프로그램 **" << endl;
	ll range =pow(2,BIT-1);
	ll range_down;
	BIT == 64 ? range_down = range : range_down = range * -1;
	ll range_upper = range - 1;
	cout << "가능한 입력 범위 " << range_down << " ~ " << range_upper << endl;
	while (true) {
		int is_minus=0;
		cout << "10진수 숫자 입력(Q : 종료) : ";
		cin >> input;
		cout << endl;
		
		if (input == "Q") {
			cout << "프로그램 종료" << endl;
			return 0;
		}
		else {
			if (input == "0" || input == "+0" || input == "-0") {
				zero_process(input);
				memset(binary_arr, 0, sizeof(binary_arr));
				continue;
			}
			number = stoll(input);
			if (number > range_upper) {
				cout << "입력범위 초과" << endl;
				continue;
			}
			if (number < range_down) {
				cout << "입력범위 미만" << endl;
				continue;
			}
			if (number < 0) {
				is_minus = 1;
				number *= -1;
			}
			to_binary(number);

			for (int i = 0; i < 12 + BIT + (BIT / 4 - 1); i++) {
				cout << "#";
			}
			cout << endl;
			if (is_minus) { //음수인 경우
				printf("%12s", "부호-크기 : "); signed_magnitude();
				printf("%12s", "1의 보수 : "); one_complement();
				printf("%12s", "2의 보수 : "); two_complement();
			}
			else {	//양수인 경우
				printf("%12s", "부호-크기 : "); output_arr(binary_arr);
				printf("%12s", "2의 보수 : "); output_arr(binary_arr);
				printf("%12s", "1의 보수 : "); output_arr(binary_arr);
			}

			for (int i = 0; i < 12 + BIT + (BIT / 4 - 1); i++) {
				cout << "#";
			}
			cout << endl;
			memset(binary_arr, 0, sizeof(binary_arr));
			cout << endl;

		}
	}
}