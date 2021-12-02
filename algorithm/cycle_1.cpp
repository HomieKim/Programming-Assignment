#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define MAX 50001
#pragma warning(disable:4996)
using namespace std;

int T, n;
int rst = -1;
int vis[MAX];
int isCycle = 0;
int vis2[50001];
vector<vector<int>> graph(MAX);

void getCycleSize(int start, int depth) {
	vis[start] = 1;
	for (int i = 0; i < graph[start].size(); i++) {
		int next = graph[start][i];
		if (vis[next] == 0) {
			getCycleSize(next, depth + 1);
		}
		else {
			if (next == isCycle) {
				rst = max(rst, depth + 1);
			}
		}

	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	//freopen("cycle.inp", "r", stdin);
	//freopen("cycle.out", "w", stdout);
	cin >> T;
	int a, b;
	while (T--) {
		cin >> n;
		for (int i = 1; i < n; i++) {
			cin >> a >> b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		for (int i = 1; i <= n; i++) {
			for (int j = i; j <= n; j++) {
				if (j == i) continue;
				auto flag = find(graph[i].begin(), graph[i].end(), j);
				if (flag == graph[i].end()) {
					graph[i].push_back(j);
					graph[j].push_back(i);
					isCycle = i;
					getCycleSize(i, 0);
					graph[i].pop_back();
					graph[j].pop_back();
					fill_n(vis, n + 1, 0);
				}
			}
		}

		cout << "##############" << rst << '\n';
		rst = -1;
		graph.clear();
		graph.resize(MAX);
		//fill_n(vis, n + 1, 0);
	}


}