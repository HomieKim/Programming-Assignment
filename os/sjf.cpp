
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


using namespace std;

int main() {

	ifstream fin("sjf.inp");
	ofstream fout("sjf.out");

	int n;

	fin >> n;

	vector<int> arTime(n);
	vector<int> useTime(n);

	for (int i = 0; i < n; i++) {
		fin >> arTime[i];
		fin >> useTime[i];
	}

	int useSum = useTime[0] + arTime[0];
	int waitSum = 0;

	for (int i = 1; i < n; i++) {
		int min = useTime[i];
		int key = i;
		for (int j = i+1; j < n; j++) {
			if (useSum  < arTime[j]) {
				continue;
			}
			else {

				if (min > useTime[j]) {
					min = useTime[j];
					key = j;
				}
			}

		}

		if (key != i) {
			if (useSum < arTime[i]) {
				useSum = arTime[i] + useTime[i];
			}
			else {
				waitSum += useSum - arTime[i];
				useSum += useTime[i];
			}
		}
		else {
			if (useSum < arTime[key]) {
				useSum = arTime[key] + useTime[key];
			}
			else {
				waitSum += useSum - arTime[key];
				useSum += useTime[key];
			}
		}



		
	}

	fout << waitSum;

	fout.close();
	fin.close();

}