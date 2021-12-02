#include <iostream>
#include <fstream>
#define ll long long


using namespace std;

int T;
ll a, b, c, d, mod;

ll matrix[2][2] = { {1,1}, {1,0} };	// 초기 행렬
ll ans[2][2] = { {1,0}, {0,1} };	// 단위 행렬
void multi(ll mat1[][2], ll mat2[][2]) {
	ll tmp[2][2] = { 0, };

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				tmp[i][j] += mat1[i][k] * mat2[k][j];
			}
			tmp[i][j] %= mod;
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			mat1[i][j] = tmp[i][j];
		}
	}


}

ll solve(ll num) {
	
	while (num > 0) {
		if (num % 2 != 0) {
			multi(ans, matrix);
		}
		multi(matrix, matrix);
		num /= 2;
	}
	
	return ans[0][1];

}
void init() {
	ans[0][0] = 1; ans[0][1] = 0; ans[1][0] = 0; ans[1][1] = 1;
	matrix[0][0] = 1; matrix[0][1] = 1; matrix[1][0] = 1; matrix[1][1] = 0;
}
int main() {
	ifstream fin("fibonacci.inp");
	ofstream fout("fibonacci.out");
	fin >> T;
	ll A, B, C, D;
	for (int t = 0; t < T; t++) {
		fin >> a >> b >> c >> d >> mod;
		A =solve(a);
		init();
		B = solve(b);
		init();
		C = solve(c);
		init();
		D = solve(d);
		init();
		
		fout << ((A * B)%mod + (C * D)%mod)%mod << endl;
	}



 }