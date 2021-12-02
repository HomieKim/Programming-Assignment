#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#define MAX 500002
using namespace std;

int T, N;
int vis[MAX];
int parentCnt[MAX];
int maxDepth = -1;
//vector<vector<int>> graph(MAX);
// 루트 찾고 dfs로 최대 깊이 찾으면 될듯?
vector<vector<int>> graph(MAX);
void dfs(int start, int depth) {

	vis[start] = 1;
	maxDepth = max(maxDepth, depth);
	for (int i = 0; i < graph[start].size(); i++) {
		int next = graph[start][i];
		if (vis[next] == 0) {
			dfs(next, depth+1);
		}
	}

}
int main() {
	ifstream fin("family.inp");
	ofstream fout("family.out");
	//cin >> T;
	fin >> T;
	int parent, child;
	for (int t = 0; t < T; t++) {
		//cin >> N;
		fin >> N;
		
		for (int i = 0; i < N-1; i++) {
			//cin >> parent >> child;
			fin >> parent >> child;
			graph[parent].push_back(child);
			graph[child].push_back(parent);
			parentCnt[child]++;
		}
		// 루트 노드 찾기, 문제에서 부모가 없는 노드는 하나라고 주어짐
		int root=0;
		for (int i = 1; i < N+1; i++) { // 1 부터 N사이의 숫자로 구분됨
			if (parentCnt[i] == 0) {
				root = i;
				break;
			}
		}
		
		dfs(root,0);

		//cout << "MaxDepth : " << maxDepth +1 << endl;
		fout << maxDepth + 1 << '\n';
		maxDepth = -1;
		graph.clear();
		graph.resize(MAX);
		fill_n(vis, N + 1, 0);
		fill_n(parentCnt, N + 1, 0);

	}

	fout.close();
	fin.close();
	return 0;
}