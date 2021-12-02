#include <iostream>
#include <vector>
#include <cstring>
#define MOD 100000
#define MAX 202
#pragma warning(disable:4996)
using namespace std;
int T, n,w;
int arr[MAX];
int dp[MAX][80001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("sum.inp", "r", stdin);
	freopen("sum.out", "w", stdout);
	

	cin >> T;
	while (T--) {
		cin >> n >> w;
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}

		for (int i = 0; i <= n; i++) {
			dp[i][0] = 1;
		}
		for (int i = 1; i <= w; i++) {
			dp[0][i] = 0;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= w; j++) {
				if (arr[i - 1] > j) {
					dp[i][j] = (dp[i - 1][j]) % MOD;
				}
				else {
					dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - arr[i - 1]]) % MOD;
				}
			}
		}

		cout << dp[n][w] << '\n';
		memset(dp, 0, sizeof(dp));
		memset(arr, 0, sizeof(arr));
	}
}