#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

string good, P, Q;
// 문자 패턴에 관한 정보

/*
	? : 하나의 좋은 문자로 바꿈
	* : 빈 문자열 도는 '나쁜문자'를 하나 이상포함하는 임의의 길이의 문자열로 대치

	문제 : Q가 주어지면 P에 주어진 패턴에 따라 Q를 만들수 있는가 묻는 문제
	
*/
vector<string> vecP;
vector<string> vecQ;

bool QuestionChk(string str) {

	char tmp_c = str[0];
	for (int i = 0; i < good.size(); i++) {
		if (good[i] == tmp_c) {
			return true;
		}
	}

	return false;
}



bool StarChk(string str) {	// 나쁜문자를 하나이상 포함하고 있는지 여부
	int cnt = 0;
	for (int i = 0; i < good.size(); i++) {
		for (int j = 0; j < str.size(); j++) {
			if (good[i] == str[j]) cnt++;
		}
	}

	if (cnt == str.size()) {
		return false;
	}
	else {
		return true;
	}
}

bool StringChk(string str1, string str2) {
	if (str1 == str2) {
		return true;
	}
	else {
		return false;
	}
}


string solve() {
	vector<string> tmp;
	string ans, tmp_s;
	int starSzie = Q.size() - P.size() +1;
	if (starSzie < 0) {
		return "No";
	}
	for (int i = 0; i < P.size(); i++) {
		
		if (P[i] == '?' || P[i] == '*') {
			if (!tmp_s.empty()) {
				vecP.push_back(tmp_s);
			}

			if (P[i] == '?') {
				vecP.push_back("?");
			}
			else if (P[i] == '*') {
				vecP.push_back("*");
			}
		
			tmp_s.clear();
			continue;
		}
		tmp_s.push_back(P[i]);
	}
	if (!tmp_s.empty()) {
		vecP.push_back(tmp_s);
	}


	int now_idx = 0;
	for (int i = 0; i < vecP.size(); i++) {
		string tmp_2;
		if (vecP[i] == "?") {
			tmp_2 = Q.substr(now_idx, 1);
			now_idx += 1;
			vecQ.push_back(tmp_2);
		}
		else if (vecP[i] == "*") {
			if (starSzie != 0) {
				tmp_2 = Q.substr(now_idx, starSzie);
				now_idx += starSzie;
				vecQ.push_back(tmp_2);
			}
			else {
				vecQ.push_back("");
			}
		}
		else {
			int stringSize = vecP[i].size();
			tmp_2 = Q.substr(now_idx, stringSize);
			now_idx += stringSize;
			vecQ.push_back(tmp_2);
		}

	}


	bool chk1 = false;
	bool chk2 = false;
	bool chk3 = false;
	int flag = 1;
	for (int i = 0; i < vecP.size(); i++) {
		if (vecP[i] == "?") {
			chk1 = QuestionChk(vecQ[i]);
			if (chk1 == false) flag = 0;
		}
		else if (vecP[i] == "*") {
			if (starSzie == 0) continue;
			chk2 = StarChk(vecQ[i]);
			if (chk2 == false) flag = 0;
		}
		else {
			chk3 = StringChk(vecP[i], vecQ[i]);
			if (chk3 == false) flag = 0;
		}
	}

	if (flag) {
		return "Yes";
	}
	else {
		return "No";
	}
	
}
int main() {

	ifstream fin("exam.inp");
	ofstream fout("exam.out");

	int T;
	//cin >> T;
	fin >> T;
	int case_Cnt = 1;
	string ans;
	for (int t = 0; t < T; t++) {
		//cout << "Test Case: #" << case_Cnt << '\n';
		fout << "Test Case: #" << case_Cnt << '\n';
		int iter = 0;
		//cin >> good;
		fin >> good;
		
		//cin >> P;
		fin >> P;
		
		//cin >> iter;
		fin >> iter;
		for (int i = 0; i < iter; i++) {
			//cin >> Q;
			fin >> Q;
			
			//cout << solve() << '\n';
			fout << solve() << '\n';
			vecP.clear();
			vecQ.clear();

		}
		case_Cnt++;
	}

	fout.close();
	fin.close();

	return 0;
}
