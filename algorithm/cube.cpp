#include <iostream>
#include <fstream>
#include <algorithm>
#pragma warning(disable:4996)

using namespace std;
int w, l, h;
int dp[202][202][202];

void sol() {

	for (int i = 1; i < 202; i++) {
		for (int j = 1; j < 202; j++) {
			for (int m = 1; m < 202; m++) {
				if (i == j && j == m) {
					dp[i][j][m] = 1;
				}
				else if(i == 1 || j == 1 || m == 1) {
					dp[i][j][m] = i * j * m;
				}
				else if(dp[i][j][m] == 0){
					dp[i][j][m] = 8000002;
					for (int k = 1; k <= i / 2; k++) {
						dp[i][j][m] = min(dp[i][j][m], dp[k][j][m] + dp[i - k][j][m]);
					}
					for (int k = 1; k <= j / 2; k++) {
						dp[i][j][m] = min(dp[i][j][m], dp[i][k][m] + dp[i][j-k][m]);
					}
					for (int k = 1; k <= m / 2; k++) {
						dp[i][j][m] = min(dp[i][j][m], dp[i][j][k] + dp[i][j][m-k]);
					}
					dp[i][m][j] = dp[j][i][m] = dp[m][i][j] = dp[j][m][i] = dp[m][j][i] = dp[i][j][m];
				}
			}
		}
	}
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("cube.inp", "r", stdin);
	freopen("cube.out", "w", stdout);

	int T;
	sol();

	cin >> T;
	while (T--) {
		cin >> w >> l >> h;
		cout << dp[w][l][h] << '\n';
	}
}
