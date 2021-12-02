#include <iostream>
#include <algorithm>
#include <cstring>
#define INF 500002
using namespace std;
int T;
int dp[5002][5002]; // dp[i][j] lane1 에서 i개 차량 합쳐지고 lane2에서 j개의 차량 합쳐졌을 때 L(c) => 최소로 되게 만들어야함
int num[5002][5002];
int start_[2][26];
int end_[2][26];
void sol(string s1, string s2) {
	int rst= 0;
	
	for (int i = 1; i <= s1.size(); i++) {
		int alpa = s1[i] - 'A';
		start_[0][alpa] = min(i, start_[0][alpa]);
		end_[0][alpa] = i;
	}
	for (int i = 1; i <= s2.size(); i++) {
		int alpa = s2[i] - 'A';
		start_[1][alpa] = min(i, start_[1][alpa]);
		end_[1][alpa] = i;
	}
	num[0][0] = 0;
	for (int i = 0; i <= s1.size(); i++) {
		for (int j = 0; j <= s2.size(); j++) {
			if (i > 0) {
				num[i][j] = num[i - 1][j];
				int alpa = s1[i] - 'A';
				if (start_[0][alpa] == i && start_[1][alpa] > j) ++num[i][j];
				if (end_[0][alpa] == i && end_[1][alpa] <= j) --num[i][j];
			}
			if (j > 0) {
				num[i][j] = num[i][j-1];
				int alpa = s2[i] - 'A';
				if (start_[1][alpa] == j && start_[0][alpa] > i) ++num[i][j];
				if (end_[1][alpa] == j && end_[0][alpa] <= i) --num[i][j];
			}
		}
	}

	for (int i = 0; i <= s1.size(); i++) {
		for (int j = 0; j <= s2.size(); j++) {
			if (i == 0 && j == 0) continue;
			dp[i][j] = INF;
			if (i > 0) {
				dp[i][j] = min(dp[i][j], dp[i - 1][j] + num[i - 1][j]);
			}
			if (j > 0) {
				dp[i][j] = min(dp[i][j], dp[i][j - 1] + num[i][j - 1]);
			}
		}
	}

	cout << dp[s1.size()][s2.size()] << endl;
}

int main() {

	cin >> T;
	string s1;
	string s2;
	while (T--) {
		cin >> s1 >> s2;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 26; j++) {
				start_[i][j] = INF;
			}
		}
		memset(end_, 0, sizeof(end_));
		memset(dp, 0, sizeof(dp));
		memset(num, 0, sizeof(num));
		sol(s1, s2);
		
	}

}