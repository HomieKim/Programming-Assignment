#include <iostream>
#include <string>
#include <cstring>
#include <math.h>


/*
�ΰ��� ���� �ּ�
	- GUI���� �ܼ�ȯ�濡�� �����մϴ�.
	- ��� ���� ��� ó�������մϴ�
	- 0�� ��� ���� ó���մϴ�. (+0, -0, 0 �Է°��� �ϳ� -0�ǰ�� 1�� ���� ��ȣ-ũ�� ����� ���븸 ����մϴ�.)
	- ���α׷� ���� �߿� �Է��� �޾Ƽ� ���α׷�ũ�� (bit ��)�� ���մϴ�. 8, 16, 32, 64 �ܿ��� ����ó�� �մϴ�.
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
		printf("%12s", "��ȣ-ũ�� : "); signed_magnitude();
		printf("%12s", "1�� ���� : "); one_complement();
	}
	else {
		printf("%12s", "��ȣ-ũ�� : "); output_arr(binary_arr);
		printf("%12s", "2�� ���� : "); output_arr(binary_arr);
		printf("%12s", "1�� ���� : "); output_arr(binary_arr);
	}
	for (int i = 0; i < 12 + BIT + (BIT / 4 - 1); i++) {
		cout << "#";
	}
	cout << endl << endl;
}

ll number;


int main() {
	
	string input;
	
	cout << "���α׷� ũ�⸦ �Է��ϼ���(8bit, 16bit, 32bit, 64bit)" << endl;
	
	
	while (true) {
		cout << "bit �� �Է� : ";
		cin >> BIT;
		
		if (BIT == 8 || BIT == 16 || BIT == 32 || BIT == 64) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << endl;
			break;
		}
		else {
			cout << "�߸��� �Է��Դϴ�. 8, 16, 32, 64 bit �Է°��� " << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		cout << endl;
		
	}
	cout << "** "<<BIT << "bit 10���� ��ȯ ���α׷� **" << endl;
	ll range =pow(2,BIT-1);
	ll range_down;
	BIT == 64 ? range_down = range : range_down = range * -1;
	ll range_upper = range - 1;
	cout << "������ �Է� ���� " << range_down << " ~ " << range_upper << endl;
	while (true) {
		int is_minus=0;
		cout << "10���� ���� �Է�(Q : ����) : ";
		cin >> input;
		cout << endl;
		
		if (input == "Q") {
			cout << "���α׷� ����" << endl;
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
				cout << "�Է¹��� �ʰ�" << endl;
				continue;
			}
			if (number < range_down) {
				cout << "�Է¹��� �̸�" << endl;
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
			if (is_minus) { //������ ���
				printf("%12s", "��ȣ-ũ�� : "); signed_magnitude();
				printf("%12s", "1�� ���� : "); one_complement();
				printf("%12s", "2�� ���� : "); two_complement();
			}
			else {	//����� ���
				printf("%12s", "��ȣ-ũ�� : "); output_arr(binary_arr);
				printf("%12s", "2�� ���� : "); output_arr(binary_arr);
				printf("%12s", "1�� ���� : "); output_arr(binary_arr);
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