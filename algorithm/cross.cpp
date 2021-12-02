#include <iostream>
#include <fstream>
#include <vector>
#define MAX 10002

using namespace std;

int S1[MAX];
int S2[MAX];
int t, n;
int main() {
	ifstream fin("cross.inp");
	ofstream fout("cross.out");
	//cin >> t;
	fin >> t;
	int tmp;
	int cnt = 1;
	for (int T = 0; T < t; T++) {
		//cin >> n;
		fin >> n;
		for (int i = 1; i <= n; i++) {
			//cin >> tmp;
			fin >> tmp;
			S1[tmp] = i;
		}
		for (int i = 1; i <= n; i++) {
			//cin >> tmp;
			fin >> tmp;
			S2[i] = S1[tmp];
		}
		int ans = 0;
		for (int i = n; i > 1; i--) {
			for (int j = i - 1; j >= 1; j--) {
				if (S2[i] < S2[j]) ans++;
			}
		}

		//cout << "Case " << cnt << ": " << ans << '\n';
		fout << "Case " << cnt << ": " << ans << '\n';
		cnt++;
	}

}