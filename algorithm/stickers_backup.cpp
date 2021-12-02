#include <iostream>
#include <queue>
#include <cstring>
#pragma warning(disable:4996)
using namespace std;

int T, N;
int arr[2][100001];
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
priority_queue<pair<int, pair<int, int>>> Q;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	//freopen("stickers.inp", "r", stdin);
	//freopen("stickers.out", "w", stdout);
	cin >> T;
	while (T--) {
		cin >> N;
		int rst = 0;
		int minus_cnt = 0;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < N; j++) {
				cin >> arr[i][j];
				Q.push({ arr[i][j], make_pair(i,j) });
			}
		}
		while (!Q.empty()) {
			if (minus_cnt == 2 * N) break;
			auto cur = Q.top();
			Q.pop();
			int x = cur.second.first;
			int y = cur.second.second;
			if (arr[x][y] == -1) {
				continue;
			}
			else {
				rst += cur.first;
				minus_cnt++;
				for (int i = 0; i < 4; i++) {
					int nx = x + dx[i];
					int ny = y + dy[i];
					if (nx < 0 || nx >= 2 || ny < 0 || ny >= N) continue;
					if (arr[nx][ny] == -1) continue;
					arr[nx][ny] = -1;
					minus_cnt++;
				}
			}
		}

		cout << rst << endl;
		while (!Q.empty()) Q.pop();
		memset(arr, 0, sizeof(arr));
	}
}