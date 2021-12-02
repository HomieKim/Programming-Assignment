#include <iostream>
#include <cstring>
#pragma warning(disable:4996)

#define MAX 302
#define mod 1000000007
using namespace std;
long long dp[MAX][MAX];
int N, K;



int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	//freopen("addingways.inp", "r", stdin);
	//freopen("addingways.out", "w", stdout);
	while (true) {
		cin >> N >> K;
		if (N == 0 && K == 0) break;
		for (int i = 1; i <= N; i++) {
			dp[i][1] = 1;
			dp[i][i] = 1;
		}

		for (int i = 2; i <= N; i++) {
			for (int j = 2; j <= i; j++) {
				dp[i][j] = (dp[i - 1][j - 1] + dp[i - j][j]) % mod;
			}
		}
		cout << dp[N][K] << '\n';
		memset(dp, 0, sizeof(dp));
	}
	

}