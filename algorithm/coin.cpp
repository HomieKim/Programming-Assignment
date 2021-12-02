#include <iostream>
#define MAX 101
#pragma warning(disable:4996)
using namespace std;
int bottle[MAX][MAX][MAX];


int getNum(int a, int b, int c) {
	for (int i = 1; i <= c; i++) {
		if (i > 3) break;
		if (bottle[a][b][c - i] == -1) return 1;
	}

	for (int i = 1; i <= b; i++) {
		if (i > 3) break;
		if (bottle[a][b-i][c] == -1) return 1;
	}

	for (int i = 1; i <= a; i++) {
		if (i > 3) break;
		if (bottle[a-i][b][c] == -1) return 1;
	}

	return -1;
}
void sol() {

	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			for (int m = 0; m < 101; m++) {
				if (i + j + m == 0) continue;
				if (i + j + m == 1) {
					bottle[i][j][m] = -1;
					continue;
				}

				
				if (i <= 3 || j <= 3 || m <= 3) { 
					bottle[i][j][m] = getNum(i, j, m);

					/*if(bottle[i][j][m-1] == -1 || bottle[i][j][m-2] == -1 || bottle[i][j][m-3] == -1){
						bottle[i][j][m] = 1;
					}
					else if (bottle[i][j - 1][m] == -1 || bottle[i][j - 2][m] == -1 || bottle[i][j - 3][m] == -1) {
						bottle[i][j][m] = 1;
					}
					else if (bottle[i - 1][j][m] == 1 || bottle[i - 2][j][m] == -1 || bottle[i - 3][j][m] == -1) {
						bottle[i][j][m] = 1;
					}
					else {
						bottle[i][j][m] = -1;
					}*/
					
				}
				else {
					if (bottle[i][j][m-1] == -1 || bottle[i][j - 1][m] == -1 || bottle[i-1][j][m] == -1) {
						bottle[i][j][m] = 1;
					}
					else if (bottle[i][j][m-2] == -1 || bottle[i][j - 2][m] == -1 || bottle[i-2][j][m] == -1) {
						bottle[i][j][m] = 1;
					}
					else if (bottle[i][j][m-3] == -1 || bottle[i][j - 3][m] == -1 || bottle[i-3][j][m] == -1) {
						bottle[i][j][m] = 1;
					}
					else {
						bottle[i][j][m] = -1;
					}
				}
					


			}
		}
	}	
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("coin.inp", "r", stdin);
	freopen("coin.out", "w", stdout);
	int T;
	cin >> T;
	int a, b, c;
	sol();
	while (T--) {
		cin >> a >> b >> c;
		cout << "(" << a << " " << b << " " << c << ") : " << bottle[a][b][c] << '\n';
	}
}