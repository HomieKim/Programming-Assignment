#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> S;
vector<int> C;
vector<int> rst;
int n;



int main() {
	ifstream fin("sequence.inp");
	ofstream fout("sequence.out");
	
	//cin >> n;
	fin >> n;
	int tmp;
	for (int i = 0; i < n; i++) {
		//cin >> tmp;
		fin >> tmp;
		S.push_back(tmp);
	}
	for (int i = 0; i < n; i++) {
		//cin >> tmp;
		fin >> tmp;
		C.push_back(tmp);
	}
	sort(S.begin(), S.end());
	for (int i = n-1; i > 0; i--) {
		
		rst.push_back(S[C[i]]);
		S.erase(S.begin() + C[i]);
	}
	rst.push_back(S[0]);
	
	for (int i = n - 1; i >= 0; i--) {
		//cout << rst[i] << endl;
		fout << rst[i] << '\n';
	}
}