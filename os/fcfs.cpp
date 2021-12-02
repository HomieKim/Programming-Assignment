
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
	
	ifstream fin("fcfs.inp");
	ofstream fout("fcfs.out");
	
	int n;

	fin >> n;


	vector<int> arTime(n);
	vector<int> useTime(n);
	for (int i = 0; i < n; i++) {
		fin >> arTime[i];
		fin >> useTime[i];
	}

	int useSum = useTime[0]+arTime[0];
	int waitSum = 0;

	for (int i = 1; i < n; i++) {
		if (useSum - arTime[i] <0) {
			useSum = arTime[i] + useTime[i];
		}
		else {

		waitSum += useSum - arTime[i];
		useSum += useTime[i];
		}
	}

	fout << waitSum;


}