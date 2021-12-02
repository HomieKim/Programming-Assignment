#include <iostream>
#include <algorithm>
#include <cstring>
#pragma warning(disable:4996)

#define MAX 100001
using namespace std;

int arr[MAX];
int dp[MAX];

int T, n;
int sol(int i,int rst) {
	if (i > n-1) {
		return rst;
	}
	if (dp[i] != 0) {
		return dp[i];
	}
	else {
		rst += arr[i];
		return dp[i] = sol(i+arr[i],rst);
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	freopen("jump.inp", "r", stdin);
	freopen("jump.out", "w", stdout);

	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}
		int ans = 0;
		for (int i = 0; i < n; i++) {
			ans = max(ans,sol(i,0));
		}
		cout << ans << '\n';
		memset(arr, 0, sizeof(arr));
		memset(dp, 0, sizeof(dp));
	}

}