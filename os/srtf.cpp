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
	// �۾��� ���� �ð��� ������ ��ȯ �ð��� �۾��� �����ð� - �����ð�
	// ��ȯ �ð� = ���ð� + ����ð�
	// �۾��� ���� �ð� - �����ð� - cpu ����ð�  => ���ð� ������

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
					key = ready[m];	// ����ð��� ���� ���� ps��ȣ�� ready���� ���° �ε�����
									// key ���� ready �߿� �� ����ð� ���� ps��ȣ
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
					ready.erase(ready.begin() + chk); // ready���� key��� �������� ������ �ε��� ��������
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

		}		// ����� �ؾ��ϴ� �� ps�� -- �Ǿ���


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