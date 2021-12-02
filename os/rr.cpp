#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

int main() {

	ifstream fin("rr.inp");
	ofstream fout("rr.out");

	int n;
	int ts;
	fin >> n;
	fin >> ts;

	vector<vector<int>> burst;
	vector<int> arTime(n);
	int k;
	
	vector<int> tmp;
	int a;
	for (int i = 0; i < n; i++) {
		fin >> arTime[i];
		fin >> k;
		for (int j = 0; j < k; j++) {
			fin >> a;
			tmp.push_back(a);
		}
		burst.push_back(tmp);
		tmp.clear();
		
	}
	vector<vector<int>> cpuburst;
	vector<vector<int>> ioburst;
	vector<int> tmp1;
	vector<int> tmp2;
	
	for (int i = 0; i < n; i++) {
		tmp1.push_back(burst[i][0]);
		for (int j = 1; j < burst[i].size(); j++) {
			if (j % 2 == 0) {
				tmp1.push_back(burst[i][j]);
			}
			else {
				tmp2.push_back(burst[i][j]);
			}
		}
		cpuburst.push_back(tmp1);
		ioburst.push_back(tmp2);
		tmp1.clear();
		tmp2.clear();
	}

	
	queue<int> readyque;
	vector<int> ioque;
	int ps = arTime[0]; 
	vector<int> endTime(n);
	int runPs = 0;
	int chk = 0;
	int sel = 0;

	while (true) {
		
		if (ps > arTime[n - 1]) {
			int chksum1 = 0;
			
			for (int a = 0; a < n; a++) {
				for (int b = 0; cpuburst[a].size(); b++) {
					chksum1 += cpuburst[a][b];
					if (chksum1 > 0) {
						break;
					}
				}
			}
			if (chksum1 == 0) {
				break;
			}
		}

		for (int i = 1; i < n; i++) {
			if (arTime[i] == ps) {
				readyque.push(i);
			}
		}
		
		// 실행 할 프로세스 --로 떨구기 
		for (int i = 0; i < cpuburst[runPs].size(); i++) {
			if (cpuburst[runPs][i] != 0) {
				sel = i;
				break;
			}
		}
		cpuburst[runPs][sel]--;
		chk++;

		
		if (cpuburst[runPs][sel] == 0) {
			if (!readyque.empty()) {
				ioque.push_back(runPs);
				int a = readyque.front();
				runPs = a;
				readyque.pop();
			}
			chk = 0;
		}else if (chk == ts) {
			readyque.push(runPs);
			int a = readyque.front();
			runPs = a;
			readyque.pop();
			chk = 0;
		}

		if (!ioque.empty()) {
			int sel1 = 0;
			for (int a = 0; a < ioque.size(); a++) {
				int b = ioque[a];
				for (int j = 0; j < ioburst[b].size(); j++) {
					if (ioburst[b][j] != 0) {
						sel1 = j;
						break;
					}
				}
				ioburst[b][sel1]--;
				if (ioburst[b][sel1] == 0) {
					readyque.push(b);
				}
			}
			vector<int> tmpvec;
			for (int k = 0; k < ioque.size(); k++) {
				if (ioque[k] == 0) {
					tmpvec.push_back(k);
				}
			}
			for (int k = 0; k < tmpvec.size(); k++) {
				ioque.erase(ioque.begin() + tmpvec[k]);
			}
		}

		for (int k = 0; k < n;k++) {
			int tmp = 0;
			for (int j = 0; j < cpuburst[k].size(); j++) {
				tmp += cpuburst[k][j];
			}
			if (tmp == 0) {
				if (endTime[k] == 0) {
					endTime[k] = ps;
				}
			}
		}
		
		ps++;

	}

	vector<int> wt(n);
	for (int j=0; j < n; j++) {
		int sum1 = 0;
		int sum2 = 0;
		for (int k = 0; k < cpuburst[j].size(); k++) {
			sum1 += cpuburst[j][k];
		}
		for (int k = 0; k < ioburst[j].size(); k++) {
			sum2 += ioburst[j][k];
		}
		wt[j] = endTime[j] - arTime[j] - sum1 - sum2;
	}
	fout << "프로세스 번호 대기 시간" << endl;
	for (int j = 0; j < n; j++) {
		fout << j << " " << wt[j] << endl;
	}
}
