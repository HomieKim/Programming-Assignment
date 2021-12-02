#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Process {
	vector<int> Max;
	vector<int> Alloc;
	vector<int> Need;
}typedef ps;

int n, m;
int quesel;
ps** list;
vector<int> Aval;
vector<vector<int>> readyque;
vector<int> readyidx;

bool needchk(int sel, vector<int> request) {
	bool chk = false;
	for (int i = 0; i < m; i++) {
		if (list[sel]->Need[i] < request[i]) { // 여기서 마지막 에러 list[3]->Need[3] = 0 < 2
			chk = true;
			break;
		}
	}
	return chk;
}
bool avalchk(vector<int> request) {
	bool chk = false;
	for (int i = 0; i < m; i++) {
		if (Aval[i] < request[i]) {
			chk = true;
			break;
		}
	}
	return chk;
}


bool isSafe(int sel, vector<int> request) { // unsafe 경우 true 반환, true 반환 시 readyque에 들어감

	ps** list2;
	// Aval 복사
	vector<int> Aval2(m);
	for (int i = 0; i < m; i++) {
		Aval2[i] = Aval[i];
	}
	// list 복사
	list2 = (ps**)malloc(sizeof(ps*) * (n + 1));

	for (int i = 0; i < n; i++) {
		list2[i] = new ps();
		for (int j = 0; j < m; j++) {
			list2[i]->Alloc.push_back(list[i]->Alloc[j]);
			list2[i]->Need.push_back(list[i]->Need[j]);
		}
	}

	int com[51] = { 0, };

	// 먼저 요청 들어줬다고 가정, aval체크는 앞에서 했음
	for (int i = 0; i < m; i++) {
		Aval2[i] -= request[i];
		list2[sel]->Need[i] -= request[i];
		list2[sel]->Alloc[i] += request[i];
	}



	for (int i = 0; i < n; i++) { // ps가 n개 니까 n번 반복, 반복중 unsafe발견되면 true반환하고 종료하면 될듯?
		for (int j = 0; j < n; j++) {	// 여기 체크
			if (com[j] == 0) {
				int flag = 0;
				for (int k = 0; k < m; k++) {
					if (Aval2[k] < list2[j]->Need[k]) {
						flag = 1;
						break;
					}
				}

				if (flag == 0) {
					for (int y = 0; y < m; y++) {
						Aval2[y] += list2[j]->Alloc[y];
					}
					com[j] = 1;
				}

			}
		}
	}

	free(list2);
	for (int i = 0; i < n; i++) {
		if (com[i] == 0) {
			return true;
		}
	}
	return false;

}
bool quechk(vector<int> idx, vector<vector<int>> ready) {	//true리턴되면 요청수락된거, aval값 감소
	bool chk;
	for (int i = 0; i < ready.size(); i++) {
		if (!needchk(readyidx[i], readyque[i])) {
			if (avalchk(readyque[i])) {
				chk = true;
			}
			else if (isSafe(readyidx[i], readyque[i])) {
				chk = true;
			}
			else {
				chk = false;
			}

			if (chk == false) {
				quesel = i;
				return true;
			}
		}

	}
	return false;
}

bool maxchk(int sel, vector<int> release) {
	vector<int> temp(m);
	for (int i = 0; i < m; i++) {
		temp[i] = list[sel]->Alloc[i];
		temp[i] -= release[i];
	}

	for (int j = 0; j < m; j++) {
		if (temp[j] < 0) {
			return true;
		}
	}
	return false;
}

int main() {

	ifstream fin("banker.inp");
	ofstream fout("banker.out");


	fin >> n >> m;

	list = (ps**)malloc(sizeof(ps*) * (n + 1));
	for (int j = 0; j < n; j++) {
		list[j] = new ps();
	}
	for (int i = 0; i < m; i++) {
		int a;
		fin >> a;
		Aval.push_back(a);
	}
	int max, allc;
	// max할당
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fin >> max;
			list[i]->Max.push_back(max);
		}

	}
	// alloc 할당
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fin >> allc;
			list[i]->Alloc.push_back(allc);
		}

	}
	// need 구하기
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int maxidx = list[i]->Max[j] - list[i]->Alloc[j];
			list[i]->Need.push_back(maxidx);
		}

	}
	// 할당된 alloc을 시스템 aval을에서 빼기
	for (int i = 0; i < m; i++) {
		int k = 0;
		for (int j = 0; j < n; j++) {
			k += list[j]->Alloc[i];
		}
		Aval[i] -= k;
	}


	string chk = "";
	int sel = 0;

	vector<int> request;
	vector<int> release;
	while (true) {
		fin >> chk;
		if (chk == "quit") {
			break;
		}
		else if (chk == "request") {
			fin >> sel;
			int a;
			for (int i = 0; i < m; i++) {
				fin >> a;
				request.push_back(a);
			}

			if (!needchk(sel, request)) {

				if (avalchk(request)) {  // true일때 que에 들어감
					readyque.push_back(request);
					readyidx.push_back(sel);
				}
				else if (isSafe(sel, request)) {  // true일때 que에 들어감
					readyque.push_back(request);
					readyidx.push_back(sel);
				}
				else {
					for (int i = 0; i < m; i++) {
						Aval[i] -= request[i];
						list[sel]->Alloc[i] += request[i];
						list[sel]->Need[i] -= request[i];


					}
				}
			}
			request.clear();
			for (int i = 0; i < m; i++) {
				fout << Aval[i] << " ";
			}


		}
		else if (chk == "release") {
			fin >> sel;
			int a;
			for (int i = 0; i < m; i++) {
				fin >> a;
				release.push_back(a);
			}

			for (int j = 0; j < m; j++) {
				Aval[j] += release[j];
				list[sel]->Alloc[j] -= release[j];
				list[sel]->Need[j] += release[j];

			}

			if (!readyque.empty()) {
				if (quechk(readyidx, readyque)) {

					for (int i = 0; i < m; i++) {
						int j = readyidx[quesel];
						Aval[i] -= readyque[quesel][i];
						list[j]->Alloc[i] += readyque[quesel][i];
						list[j]->Need[i] -= readyque[quesel][i];
					}
					readyque.erase(readyque.begin());
					readyidx.erase(readyidx.begin());

				}
			}

		
			release.clear();
			for (int i = 0; i < m; i++) {
				fout << Aval[i] << " ";
			}

		}
		fout << endl;
	}


}