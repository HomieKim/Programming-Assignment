#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

struct MyStruct
{
	pair<int, int> lowL;
	pair<int, int> upR;
	// state 1 : 아무도 안덮음, 2: 부분적으로 덮힘, 3: 전체가 덮힘
	int state;

}typedef rec;

rec recArr[2001];

int main() {
	ifstream fin("paper.inp");
	ofstream fout("paper.out");
	int n;
	//cin >> n;
	fin >> n;
	int x, y, w, h;
	int one = 0, two = 0, three = 0;
	for (int i = 0; i < n; i++) {
		//cin >> x >> y >> w >> h;
		fin >> x >> y >> w >> h;
		recArr[i].lowL = make_pair(x, y);
		recArr[i].upR = make_pair(x + w, y + h);

	}
	/*
		겹치지 않는 경우 4가지
		1. A의 왼쪽모서리가 B의 오른쪽 모서리보다 오른쪽에 있을 때
		2. A의 오른쪽 모서리가 B의 왼쪽 모서리보다 왼쪽에 있음
		3. A의 위쪽 모서리가 B의 아래쪽 모서리보다 아래에 있음
		4. A의 아래쪽 모서리가 B의 위쪽 모서리보다 위에 있음
	*/
	for (int i = 0; i < n - 1; i++) {
		/*int wd = recArr[i].upR.first - recArr[i].lowL.first;
		int he = recArr[i].upR.second - recArr[i].lowL.second;
		vector<vector<int>>arr(10, vector<int>(10));*/
		int cnt = 0;
		for (int j = i + 1; j < n; j++) {
		
			//겹치지 않는 경우
			if (recArr[i].lowL.first >= recArr[j].upR.first || recArr[i].upR.first <= recArr[j].lowL.first ||
				recArr[i].upR.second <= recArr[j].lowL.second || recArr[i].lowL.second >= recArr[j].upR.second) {
				if (recArr[i].state != 2) {
					recArr[i].state = 1;
				}
			}
			else {
				// 완전히 덮히는지 부분적으로 덮히는지 체크
				/* 완전히 덮히는 경우
					1. A의 왼쪽 모서리가 B의 왼쪽 모서리와 같거나 더 오른쪽에 있어야함
					2. A의 왼쪽 모서리가 B의 왼쪽 모서리와 같거나 더 위에 있어야함
					3. A의 오른쪽 모서리가 B의 오른쪽 모서리와 같거나 더 왼쪽에 있어야함
					4. A의 오른쪽 모서리가 B의 오른족 모서리와 같거나 더 아래에 있어야함

					-- B를 기준으로 잡고 A모서리가 하나라도 바깥으로 나오면 2
				*/
				// 부분적으로 덮힐 때
				if (recArr[i].lowL.first < recArr[j].lowL.first || recArr[i].lowL.second < recArr[j].lowL.second ||
					recArr[i].upR.first > recArr[j].upR.first || recArr[i].upR.second > recArr[j].upR.second) {
					recArr[i].state = 2;
					/*pair<int, int> left_low;
					pair<int, int> right_upper;
					*/
				}
				else {
					recArr[i].state = 3;
					break;
				}
				
			}

		}
	}

	for (int i = 0; i < n; i++) {
		int tmp = recArr[i].state;
		switch (tmp)
		{
		case 1:
			one++;
			break;
		case 2:
			two++;
			break;
		case 3:
			three++;
			break;
		}
	}

	fout << three << " " << two << " " << one + 1;

}