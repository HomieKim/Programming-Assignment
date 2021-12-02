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
int maxDepth =-1;
int maxDepth_node = 0;
int vis2[50001];
vector<vector<int>> graph(MAX);

void dfs(int start, int depth) {
	vis[start] = 1;
	if (depth > maxDepth) {
		maxDepth = depth;
		maxDepth_node = start;
	}
	for (int i = 0; i < graph[start].size(); i++) {
		int next = graph[start][i];
		if (vis[next] == 0) {
			dfs(next, depth + 1);
		}
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("cycle.inp", "r", stdin);
	freopen("cycle.out", "w", stdout);
	cin >> T;
	int a, b;
	while (T--) {
		cin >> n;
		for (int i = 1; i < n; i++) {
			cin >> a >> b;
			graph[a].push_back(b);
			graph[b].push_back(a);
			
		}
		dfs(1, 0);
		maxDepth = -1;
		fill_n(vis, n + 1, 0);
		dfs(maxDepth_node, 0);
		cout <<maxDepth+1 << '\n';
		maxDepth = -1;
		graph.clear();
		graph.resize(MAX);
		fill_n(vis, n + 1, 0);
	}


}