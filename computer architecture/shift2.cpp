#include <iostream>
#define MAX 64
#define ll long long
using namespace std;
ll acc, rst;
int BIT;
int binary_arr[MAX];
int zero_arr[MAX];
ll b_to_d(string s1) {
	ll rst = 0;
	for (int i = 0; i < s1.size(); i++) {
		if (s1[i] == '1') {
			rst += pow(2, (s1.size() - 1) - i);
		}
	}
	return rst;
}
void to_binary(ll num) {

	int idx = BIT;
	ll mok, nmg;
	do {
		idx--;
		mok = num / 2;
		nmg = num % 2;
		binary_arr[idx] = nmg;
		num = mok;
	} while (mok != 0);

}
void output_arr(int* arr) {
	for (int i = 0; i < BIT; i++) {
		if ((BIT - i) % 4 == 0) cout << " ";
		cout << arr[i];
	}
	cout << endl;

}
void d_to_b(int num) {
	if (num == 0) {
		output_arr(zero_arr);
	}
	else {
		memset(binary_arr, 0, sizeof(binary_arr));
		if (num > 0) {
			to_binary(num);
			output_arr(binary_arr);
		}
		else {
			num *= -1;
			to_binary(num);
			output_arr(binary_arr);
		}
	}
	
}

void shift_add(char n1) {
	if (n1 == '1') {
		printf("%5c", ' ');
		d_to_b(rst);
		ll tmp = acc << 4;
		printf("%-5c", '+');
		d_to_b(tmp);
		rst += tmp;
		cout << "      ";
		for (int i = 0; i <  BIT + (BIT / 4 - 1); i++) {
			cout << "-";
		}
		cout << endl;
		printf("%5c", ' ');
		d_to_b(rst);
		rst = rst >> 1;
		printf("%-5s", ">>");
		d_to_b(rst);
	}
	else {
		printf("%5c", ' ');
		d_to_b(rst);
		printf("%-5c", '+');
		output_arr(zero_arr);
		cout << "      ";
		for (int i = 0; i < BIT + (BIT / 4 - 1); i++) {
			cout << "-";
		}
		cout << endl;
		printf("%5c", ' ');
		d_to_b(rst);
		rst = rst >>=1;
		printf("%-5s", ">>");
		d_to_b(rst);
	}
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

}
void two_complement() {
	int upper = 0;
	for (int i = BIT - 1; i >= 0; i--) {
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
void output_result(int num) {
	if (num == 0) {
		output_arr(zero_arr);
	}
	else if (num > 0) {
		to_binary(num);
		output_arr(binary_arr);
	}
	else {
		num *= -1;
		to_binary(num);
		one_complement();
		two_complement();
	}
}
int main() {

	string multiplicand; //피승수
	string multiplier; // 승수
	cout << "** 이진수 입력해 주세요 **" << endl;
	cout << "피승수 입력 : ";
	cin >> multiplicand;
	cout << "승수 입력   : ";
	cin >> multiplier;
	BIT = 2 * multiplicand.size();
	acc = b_to_d(multiplicand);
	cout << "## shift-add 알고리즘 ##" << endl;
	for (int i = multiplier.size() - 1; i >= 0; i--) {
		shift_add(multiplier[i]);
		for (int i = 0; i < 5 + BIT + (BIT / 4 - 1); i++) {
			cout << "=";
		}
		cout << endl;
	}
	cout << "결과 : ";
	output_result(rst);
	cout << endl;
}