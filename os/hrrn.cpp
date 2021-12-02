#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <utility>

using namespace std;

int main() {

	ifstream fin("hrrn.inp");
	ofstream fout("hrrn.out");

	int n;
	fin >> n;
	vector<int> arTime(n);
	vector<int> cpuTime(n);

	vector<int> run(n);
	for (int i = 0; i < n; i++) {
		fin >> arTime[i];
		fin >> cpuTime[i];
	}

	int endTime = arTime[0] + cpuTime[0];
	run[0] = 1;
	int wait = 0;

	for (int i = 1; i < n; i++) {
		// 어떤 ps 선택할지 골라야함
		float pri;
		float maxpri = 0;
		int key;

		if (endTime <= arTime[i]) {
			endTime = arTime[i] + cpuTime[i];
			run[i] = 1;
			continue;
		}

		for (int j = 1; j < n; j++) {
			if (arTime[j] < endTime && run[j] != 1) {
				pri = (float)((endTime - arTime[j]) + cpuTime[j]) / cpuTime[j];
				if (maxpri < pri) {
					maxpri = pri;
					key = j;
				}
			}
		}
		endTime += cpuTime[key];
		wait += endTime - arTime[key] - cpuTime[key];
		run[key] = 1;

	}
	fout << wait;

	fout.close();
	fin.close();
}
