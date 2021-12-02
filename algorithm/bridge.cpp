#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
//CQDTC4D8S7HTDAH7D2S3D6C6S6D9S4SAD7H2CKH5D3CTS8C9H3C3 26Àå µÎ¹ø ³ª´²¼­ ÀÔ·ÂµÊ
//SQD8C7D6H9DADQH8D2SACADTD4H6C2CKCJS5C8S6DJHQS3H4D3H7

// first : C= 0, D=1, S =2, H=3
// second : 2~9 < T=10, J=11, Q=12, K=13, A=14

ifstream fin("bridge.inp");
ofstream fout("bridge.out");

struct st
{
	char name;
	
	vector<pair<int, int>> card;
}typedef play;

play player[4];

void setCard(char ch1, char ch2, int startNum) {
	int firstNum, secondNum;
	if (ch1 == 'C') {
		firstNum = 0;
	}
	else if (ch1 == 'D') {
		firstNum = 1;
	}
	else if (ch1 == 'S') {
		firstNum = 2;
	}
	else {
		firstNum = 3;
	}

	if (ch2 >= '0' && ch2 <= '9') {
		secondNum = ch2 - '0';
	}
	else {
		if (ch2 == 'T') {
			secondNum = 10;
		}
		else if (ch2 == 'J') {
			secondNum = 11;
		}
		else if (ch2 == 'Q') {
			secondNum = 12;
		}
		else if (ch2 == 'K') {
			secondNum = 13;
		}
		else if (ch2 == 'A') {
			secondNum = 14;
		}
	}
	player[startNum].card.push_back({ firstNum,secondNum });
}
void dealing(char start) {
	int startNum;
	if (start == 'S') {
		startNum = 1;
	}
	else if (start == 'W') {
		startNum = 2;
	}
	else if (start == 'N') {
		startNum = 3;
	}
	else {
		startNum = 0;
	}
	string s;
	string sub;
	for (int i = 0; i < 2; i++) {
		//cin >> s;
		fin >> s;
		for (int j = 0; j < 52; j += 2) {
			sub = s.substr(j, 2);
			setCard(sub[0], sub[1], startNum);
			if (startNum == 3) {
				startNum = 0;
			}
			else {
				startNum++;
			}
		}
	}
}

void printCard(play player) {

	// first : C= 0, D=1, S =2, H=3
	// second : 2~9 < T=10, J=11, Q=12, K=13, A=14
	vector<string> printVec;
	int f, s;
	char secondChar;
	string first;
	for (int i = 0; i < 13; i++) {
		f = player.card[i].first;
		s = player.card[i].second;
		if (f == 0) {
			first = "C";
		}
		else if (f == 1) {
			first = "D";
		}
		else if (f == 2) {
			first = "S";
		}
		else {
			first = "H";
		}

		if (s >= 0 && s <= 9) {
			secondChar = s + '0';
		}
		else {
			if (s == 10) {
				secondChar = 'T';
			}
			else if (s == 11) {
				secondChar = 'J';
			}
			else if (s == 12) {
				secondChar = 'Q';
			}
			else if (s == 13) {
				secondChar = 'K';
			}
			else if (s == 14) {
				secondChar = 'A';
			}
		}
		printVec.push_back(first + secondChar);
	}

	//cout << player.name << ": ";
	fout << player.name << ": ";
	for (string str : printVec) {
		//cout << str << " ";
		fout << str << " ";
	}
	
}
int main() {
	char dealer;
	
	player[0].name = 'S';
	player[1].name = 'W';
	player[2].name = 'N';
	player[3].name = 'E';
	while (true) {
		//cin >> dealer;
		fin >> dealer;
		if (dealer == '#') break;
		dealing(dealer);
		// sorting
		for (int i = 0; i < 4; i++) {
			sort(player[i].card.begin(), player[i].card.end());
		}
		// print
		for (int i = 0; i < 4; i++) {
			printCard(player[i]);
			player[i].card.clear();
			//cout << '\n';
			fout << '\n';
		}

	}
	
}