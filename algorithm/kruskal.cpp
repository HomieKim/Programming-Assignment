#include <iostream>
#include <algorithm>
#include <vector>
#pragma warning(disable:4996)
#define MAX 1000001
using namespace std;
int V, E;
struct Node
{
	int n1, n2, dis, idx, parent;
	Node(int n1, int n2, int dis, int idx) {
		this->n1 = n1;
		this->n2 = n2;
		this->dis = dis;
		this->idx = idx;
	}
	
}typedef node;
vector<node> graph;
bool compare(node &n1, node &n2) {
	if (n1.dis < n2.dis) {
		return true;
	}
	else if (n1.dis == n2.dis) {
		if (n1.idx < n2.idx) {
			return true;
		}
		else {
			return false;
		}
	}	
	else {
		return false;
	}
}
int getParent(int node ) {
	if (graph[node].parent == node) {
		return graph[node].parent;
	}
	else {
		return getParent(graph[node].parent);
	}
}
void merge(int p,int q) {
	int a = getParent(p);
	int b = getParent(q);
	if (a < b) {
		graph[b].parent = a;
	}
	else {
		graph[a].parent = b;
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("kruskal.inp", "r", stdin);
	freopen("kruskal.out", "w", stdout);
	
	cin >> V >> E;
	int u, v, w;
	for (int i = 0; i < E; i++) {
		cin >> u >> v >> w;
		graph.push_back(Node(u, v, w,i));
	}
	sort(graph.begin(), graph.end(), compare);
	for (int i = 0; i < graph.size(); i++) {
		graph[i].parent = i;
	}
	vector<int> rst;
	int sum = 0;
	int i = 0;
	int p, q;
	while (rst.size() < V-1) {
		p = getParent(graph[i].n1);
		q = getParent(graph[i].n2);

		if (p != q) {
			merge(p, q);
			rst.push_back(graph[i].idx);
			sum += graph[i].dis;
		}
		i++;
	}

	cout << sum << '\n';
	for (int ans : rst) {
		cout << ans << '\n';
	}
	
	
}