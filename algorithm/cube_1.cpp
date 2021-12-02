#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
bool isBreak(string s1, string s2) {
	int rCnt = 0;
	int bCnt = 0;
	int gCnt = 0;
	for (int i = 0; i < 6; i++) {
		if (s1[i] == 'r') {
			rCnt++;
		}
		else if (s1[i] == 'b') {
			bCnt++;
		}
		else if (s1[i] == 'g') {
			gCnt++;
		}

		if (s2[i] == 'r') {
			rCnt++;
		}
		else if (s2[i] == 'b') {
			bCnt++;
		}
		else if (s2[i] == 'g') {
			gCnt++;
		}
	}

	if (rCnt == 12 || bCnt == 12 || gCnt == 12) {
		return true;
	}
	else {
		return false;
	}
}

// 1 6
void r1(string& str) {
	char temp = str[1];
	str[1] = str[2];
	str[2] = str[4];
	str[4] = str[3];
	str[3] = temp;
}

// 2 5
void r2(string& str) {
	char temp = str[0];
	str[0] = str[2];
	str[2] = str[5];
	str[5] = str[3];
	str[3] = temp;
}
//3 4
void r3(string& str) {
	char temp = str[0];
	str[0] = str[1];
	str[1] = str[5];
	str[5] = str[4];
	str[4] = temp;
}
int main() {
	ifstream fin("cube.inp");
	ofstream fout("cube.out");
	string s;
	while (true)
	{
		//cin >> s;
		fin >> s;
		string s1 = s.substr(0, 6);
		string s2 = s.substr(6);
		if (s1 == s2) {
			if (isBreak(s1, s2)) {
				//cout << "true" << endl;
				fout << "TRUE" << '\n';
				break;
			}
		}
		
		int flag = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int m = 0; m < 4; m++) {
					r1(s1);
					if (s1 == s2) {
						flag = 1;
						break;
					}
				}
				r2(s1);
			}
			r3(s1);
		}
		if (flag) {
			fout << "TRUE" << endl;
		}
		else {
			fout << "FALSE" << endl;
		}
	}
	
}