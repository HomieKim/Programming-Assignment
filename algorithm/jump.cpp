#include <iostream>
#include <vector>
#include <algorithm>
#pragma warning(disable:4996)

using namespace std;
vector<int> vec;
vector<int> new_vec;
int T, N;
int getAbs(int a, int b) {
	int rst;
	rst = a - b;
	if (rst < 0) rst *= -1;
	return rst;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("jump.inp", "r", stdin);
	freopen("jump.out", "w", stdout);
	cin >> T;
	while (T--) {
		cin >> N;
		int tmp;
		for (int i = 0; i < N; i++) {
			cin >> tmp;
			vec.push_back(tmp);
		}
		sort(vec.begin(), vec.end());
		for (int i = 0; i < vec.size(); i++) {
			if (i % 2 == 0) {
				new_vec.push_back(vec[i]);
			}
		}
		for (int i = N - 1; i > 0; i--) {
			if (i % 2 == 1) {
				new_vec.push_back(vec[i]);
			}
		}
		int rst = -1;
		for (int i = 0; i < N; i++) {
			if (i == 0) {
				int diff_L = getAbs(new_vec[i],new_vec[N-1]);
				int diff_R = getAbs(new_vec[i], new_vec[i+1]);
				int max_value = max(diff_L, diff_R);
				rst = max(rst, max_value);
			}
			else if(i==N-1){
				int diff_L = getAbs(new_vec[i], new_vec[i-1]);
				int diff_R = getAbs(new_vec[i], new_vec[0]);
				int max_value = max(diff_L, diff_R);
				rst = max(rst, max_value);
			}
			else {
				int diff_L = getAbs(new_vec[i], new_vec[i - 1]);
				int diff_R = getAbs(new_vec[i], new_vec[i + 1]);
				int max_value = max(diff_L, diff_R);
				rst = max(rst, max_value);
			}
		}
		cout << rst << '\n';
		vec.clear();
		new_vec.clear();
	}
}