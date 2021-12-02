#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
#pragma warning(disable:4996)
using namespace std;
int dp[1000001][8];
int p, k, s;
int sol(int s, int k, int k_iter ) {
	if (s - k < 0) return -1;
	if (s - k == 0) return 1;
	if ((s - k) % p == 0) return -1;

	for (int i = 1; i <= k_iter; i++) {
		if (i == k) continue;
		if (dp[s - k][i] == 1) return -1;
	}

	return 1;
}
int output() {
	
	for (int i = 1; i <= k; i++) {
		if (dp[s][i] == 1) {
			return s - i;
		}
	}
	return -1;

}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("coinmove.inp", "r", stdin);
	freopen("coinmove.out", "w", stdout);
	int T;
	cin >> T;
	while (T--) {
		
		cin >> p >> k >> s;

		for (int i = 1; i <= s; i++) {
			for (int j = 1; j <= k; j++) {
				dp[i][j] = sol(i, j, k);
			}
		}
		cout << output() << '\n';
	
		memset(dp, 0, sizeof(dp));
	}
}