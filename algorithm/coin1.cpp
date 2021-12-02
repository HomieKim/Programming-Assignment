#include <iostream>
#include <string.h>
#include <algorithm>
#pragma warning(disable:4996)


using namespace std;
int T, m;

// 구간합 알고리즘

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("coin.inp", "r", stdin);
	freopen("coin.out", "w", stdout);
	cin >> T;
	;
	while (T--) {
		cin >> m;
		int** arr = new int* [2];
		int* top = new int[m];
		int* bottom = new int[m];
		top[0] = 0;
		bottom[0] = 0;
		// 누적합을 top, bottom  배열에 담음
		for (int i = 0; i < 2; i++) {
			arr[i] = new int[m];
			for (int j = 0; j < m; j++) {
				cin >> arr[i][j];
				if (i == 0) {
					if (j == 0) {
						top[j] = arr[i][j];
					}
					else {
						top[j] = top[j - 1] + arr[i][j];
					}

				}
				else {
					if (j == 0) {
						bottom[j] = arr[i][j];
					}
					else {
						bottom[j] = bottom[j - 1] + arr[i][j];
					}
				}
			}
		}

		int ans = 10000000000;
		int bottom_value = 0;
		for (int i = 0; i < m; i++) {
			int top_value = top[m - 1] - top[i];
			int max_value = max(top_value, bottom_value); // Alice가 지나가고 남은 동전을 bob이 주울 건데 bob은 가능하면 큰 값을 주우려고함
			if (ans > max_value) ans = max_value; // Alice는 가능하면 bob의 값이 작게 하려 하므로, 최솟값을 구하면 답
			bottom_value = bottom[i];
		}
		cout << ans << '\n';

		delete[] arr[0];
		delete[] arr[1];
		delete[] arr;
		delete[] top;
		delete[] bottom;

	}
	
}