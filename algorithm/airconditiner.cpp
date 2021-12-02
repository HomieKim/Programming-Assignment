#include <iostream>
#include <algorithm>
#include <vector>
#pragma warning(disable:4996)

using namespace std;
int T, n, k;
int map[100001];
vector<int> idx;

void L_go(int start) {
	if (start < 0) return;
	if (map[start - 1] == 0) {
		map[start - 1] = map[start] + 1;
		L_go(start - 1);
	}
	else {
		if (map[start - 1] <= map[start]+1) {
			return;
		}
		else {
			map[start - 1] = map[start] + 1;
			L_go(start - 1);
		}
	}
}
void R_go(int start) {
	if (start >= n-1) return;
	if (map[start + 1] == 0) {
		map[start + 1] = map[start] + 1;
		R_go(start + 1);
	}
	else {
		if (map[start + 1] <= map[start] + 1) {
			return;
		}
		else {
			map[start + 1] = map[start] + 1;
			R_go(start + 1);
		}
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("airconditiner.inp", "r", stdin);
	freopen("airconditiner.out", "w", stdout);
	cin >> T;
	while (T--) {
		cin >> n >> k;
		int tmp;
		for (int i = 0; i < k; i++) {
			cin >> tmp;
			idx.push_back(tmp-1);
		
		}
		for (auto i : idx) {
			cin >> tmp;
			map[i] = tmp;
		}
		for (int i : idx) {
			L_go(i);
			R_go(i);
		}
		
		for (int i = 0; i < n; i++) {
			cout << map[i] << " ";
		} 
		cout << '\n';
		idx.clear();
		fill_n(map, n, 0);
	}
}