#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
vector<int> heap;
void insertion(int num) {
	heap.push_back(num);
	int now_size = heap.size()-1;
	while (now_size != 1) {
		int p = now_size / 2;
		if (heap[p] < heap[now_size]) {
			int tmp = heap[p];
			heap[p] = heap[now_size];
			heap[now_size] = tmp;
		}
		else {
			break;
		}
		now_size /= 2;
	}

}
void report() {
	int i = 1;
	while (i <= heap.size() - 1) {
		cout << heap[i] << " ";
		i *= 2;
	}
	cout << '\n';
}
void adjust() {
	int end = heap.size() - 1;
	heap[1] = heap[end]; //root�� ������ �ڽ��� ��ȯ
	heap.pop_back(); // ������ ��� ���� �� adjust
	int root = 1;
	while (root * 2 <= heap.size()-1) {
		int target_child = root * 2;
		if ((root * 2) + 1 <= heap.size() - 1) {   // ������ �ڽ��� �ִ� ���
			if (heap[root * 2] < heap[(root * 2) + 1]) {
				target_child = (root * 2) + 1;
			}
		}
		
		// �ڽ��� �θ𺸴� ������ break;
		if (heap[root] > heap[target_child]) {
			break;
		}
		else {
			// �θ��ڽĳ�� �� ��ȯ �� root���� �ڽĳ��� ��ü
			int tmp = heap[root];
			heap[root] = heap[target_child];
			heap[target_child] = tmp;
			root = target_child;
		}
	}

}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("queue.inp", "r", stdin);
	freopen("queue.out", "w", stdout);
	string s;
	heap.push_back(0);
	while (true) {
		cin >> s;
		if (s == "d") {
			adjust();
		}
		else if (s == "r") {
			report();
		}
		else if (s == "q") {
			break;
		}
		else {
			int num = stoi(s);
			heap.size() == 1 ? heap.push_back(num) : insertion(num);
		}
	}

}