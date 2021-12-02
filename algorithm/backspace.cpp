#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;

int T;
string s1, s2;
vector<int> idx;
string sol(string s1, string s2) {
	if (s1 == s2) return "YES";

	if (s1.size() >= s2.size()) {
		int start = s1.size() - 1;
		for (int i = s2.size()-1; i >= 0; i--) {
			int chk = 0;
			for (int j = start; j >= 0; j-=2) {
				if (s2[i] == s1[j]) {
					idx.push_back(j);
					start = j-1;
					chk = 1;
					break;
				}
			}
			if (chk == 0) {
				return "NO";
			}
		}

		
		sort(idx.begin(), idx.end());
		
		for (int i = 0; i < idx.size()-1; i++) {
			if (idx[i + 1] - idx[i] == 2) {
				return "NO";
			}
		}
		return "YES";
	}
	else {
		return "NO";
	}


	
}
int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	freopen("backspace.inp", "r", stdin);
	freopen("backspace.out", "w", stdout);

	cin >> T;
	while (T--) {
		cin >> s1 >> s2;

		cout << sol(s1, s2) << '\n';
		idx.clear();
	}


}