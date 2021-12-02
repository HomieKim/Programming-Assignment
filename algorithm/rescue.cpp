#include <iostream>
#include <algorithm>
#include <cstring>
#pragma warning(disable:4996)
#define MAX 10001
using namespace std;

int T,n;
int map[MAX];
int dp[MAX];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("rescue.inp", "r", stdin);
	freopen("rescue.out", "w", stdout);
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> map[i];
		}
		// 초기값 세팅, dp[4]부터는 연속 3개를 못감
		dp[1] = map[1];
		dp[2] = map[1] + map[2];
		int a = map[1] + map[3];
		int b = map[2] + map[3];
		dp[3] = max(a, b);
		
		for (int i = 4; i <= n; i++) {
			int tmp1 = dp[i - 2] + map[i];
			int tmp2 = dp[i - 3] + map[i - 1] + map[i];
			dp[i] = max(tmp1, tmp2);
		}
		cout <<dp[n] << '\n';
		memset(map, 0, sizeof(map));
		memset(dp, 0, sizeof(dp));
	}
}