#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;



int main() {
	ifstream fin("srtf.inp");
	ofstream fout("srtf.out");

	int n;
	fin >> n;
	// 작업이 끝난 시간을 구하자 반환 시간은 작업이 끝난시간 - 도착시간
	// 반환 시간 = 대기시간 + 실행시간
	// 작업이 끝난 시간 - 도착시간 - cpu 실행시간  => 대기시간 구해짐

	vector<int> arrive(n);
	vector<int> ps(n);
	vector<int> ready;
	vector<int> endTime(n);
	int arSum = 0;
	int psSum = 0;
	for (int i = 0; i < n; i++) {
		fin >> arrive[i];
		fin >> ps[i];
		arSum += arrive[i];
		psSum += ps[i];
	}

	int runPs = 0;
	int rst = 0;
	int i = arrive[0];
	while (true) {

		int chk = 0;
		if (i > arrive[n - 1]) {
			for (int a = 0; a < n; a++) {
				chk += ps[a];
				if (chk > 0) {
					break;
				}
			}

			if (chk == 0) {
				break;
			}
		}



		for (int j = 1; j < n; j++) {
			if (arrive[j] == i) {
				ready.push_back(j);
			}
		}





		if (!ready.empty()) {
			int minQue = ps[ready[0]];
			int key = ready[0];
			for (int m = 0; m < ready.size(); m++) {
				if (minQue > ps[ready[m]]) {
					minQue = ps[ready[m]];
					key = ready[m];	// 실행시간이 제일 작은 ps번호는 ready에서 몇번째 인덱스니
									// key 값은 ready 중에 젤 실행시간 작은 ps번호
				}
			}
			if (ps[runPs] == 0) {
				runPs = key;
				int chk = 0;
				for (int s = 0; s < ready.size(); s++) {
					if (ready[s] == key) {
						chk = s;
						break;
					}
				}
				ready.erase(ready.begin() + chk);
			}
			else {
				if (minQue < ps[runPs]) {
					ready.push_back(runPs);
					int chk = 0;
					for (int s = 0; s < ready.size(); s++) {
						if (ready[s] == key) {
							chk = s;
							break;
						}
					}
					ready.erase(ready.begin() + chk); // ready에서 key라는 벨류값을 가지는 인덱스 지워야해
					runPs = key;
				}
			}

			ps[runPs] -= 1;

		}
		else {
			if (ps[runPs] == 0) {
				for (int c = 0; c < n; c++) {
					if (i < arrive[c]) {
						i += arrive[c] - i;
						break;
					}
				}
				continue;
			}
			ps[runPs] -= 1;

		}		// 실행시 해야하는 것 ps값 -- 되야함


		for (int k = 0; k < n; k++) {
			if (ps[k] == 0) {
				if (endTime[k] == 0) {
					endTime[k] = i + 1;
					rst += endTime[k];
				}

			}
		}

		i++;
	}



	fout << rst - arSum - psSum;

	fout.close();
	fin.close();

}