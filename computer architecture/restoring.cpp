#include <iostream>
#include <vector>
#include <math.h>
#include <cstring>
using namespace std;
/*���� ������ ����*/
vector<int> Q;
int divisor_arr[16];
int dividend_arr[16];

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
void restoring_divide(int divisor, int dividend, int cnt) {
	if (cnt == 9) return;
	cout << endl;
	cout << "### step " << cnt << " ###" << endl;
	cout << "Dividend Left Shift" << endl;
	dividend <<= 1;
	to_binary(dividend, dividend_arr);
	printf("%-13s", "�κ� ������");
	output_arr(dividend_arr, 16);
	printf("%13s", "-");
	output_arr(divisor_arr, 8);
	cout << "------------------------" << endl;
	if (dividend - divisor < 0) {
		cout << "���� ����� �����Դϴ�. �ٽ� �����մϴ�. �� 0�� �߰� �մϴ�." << endl;
		printf("%13s", "+");
		output_arr(divisor_arr, 8);
		cout << "------------------------" << endl;
		printf("%-13s", "�κ� ������");
		output_arr(dividend_arr, 16);
		Q.push_back(0);
	}
	else {
		dividend = dividend - divisor; 
		to_binary(dividend, dividend_arr);
		printf("%-13s", "�κ� ������");
		output_arr(dividend_arr, 16);
		cout << "�������� ��� �Դϴ�. �� 1�� �߰��մϴ�." << endl;
		Q.push_back(1);
	}

	cout << "���� �� : ";
	for (auto a : Q) {
		cout << a;
	}
	cout << endl;
	restoring_divide(divisor, dividend, ++cnt);
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

int main() {
	string divisor;	// ����, �����¼�
	string dividend; // ������, ������ ���� ��

	cout << "16bit ������ �Է� : ";
	cin >> dividend;
	cout << "8bit ���� �Է� : ";
	cin >> divisor;
	int de_divisor = b_to_d(divisor);
	int de_dividend = b_to_d(dividend);
	de_divisor <<= 8;
	to_binary(de_divisor, divisor_arr);

	restoring_divide(de_divisor, de_dividend, 1);
	cout << endl;
	cout << "*** ��� ***" << endl;
	cout << "�� : ";
	for (int i = 0; i < Q.size(); i++) {
		if (i != 0 && i % 4 == 0) cout << " ";
		cout << Q[i];
	}
	cout << endl;
	cout << "������ : ";
	output_arr(dividend_arr, 8);
	cout << endl;
}