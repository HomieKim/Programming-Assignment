#include <iostream>
#include <cstring>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;

int T, N;
int arr[2][100002];
int dp1[100002];
int dp2[100002];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("stickers.inp", "r", stdin);
	freopen("stickers.out", "w", stdout);
	cin >> T;
	while (T--) {
		cin >> N;
		for (int i = 0; i < 2; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> arr[i][j];
			}
		}
		dp1[1] = arr[0][1];
		dp2[1] = arr[1][1];

		for (int i = 2; i <= N; i++) {
			dp1[i] = max(dp2[i - 2], dp2[i - 1]) + arr[0][i];
			dp2[i] = max(dp1[i - 2], dp1[i - 1]) + arr[1][i];
		}

		int rst = max(dp1[N], dp2[N]);
		cout << rst << endl;
		
	}
}