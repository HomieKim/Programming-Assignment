#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

struct MyStruct
{
	pair<int, int> lowL;
	pair<int, int> upR;
	// state 1 : �ƹ��� �ȵ���, 2: �κ������� ����, 3: ��ü�� ����
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
		��ġ�� �ʴ� ��� 4����
		1. A�� ���ʸ𼭸��� B�� ������ �𼭸����� �����ʿ� ���� ��
		2. A�� ������ �𼭸��� B�� ���� �𼭸����� ���ʿ� ����
		3. A�� ���� �𼭸��� B�� �Ʒ��� �𼭸����� �Ʒ��� ����
		4. A�� �Ʒ��� �𼭸��� B�� ���� �𼭸����� ���� ����
	*/
	for (int i = 0; i < n - 1; i++) {
		/*int wd = recArr[i].upR.first - recArr[i].lowL.first;
		int he = recArr[i].upR.second - recArr[i].lowL.second;
		vector<vector<int>>arr(10, vector<int>(10));*/
		int cnt = 0;
		for (int j = i + 1; j < n; j++) {
		
			//��ġ�� �ʴ� ���
			if (recArr[i].lowL.first >= recArr[j].upR.first || recArr[i].upR.first <= recArr[j].lowL.first ||
				recArr[i].upR.second <= recArr[j].lowL.second || recArr[i].lowL.second >= recArr[j].upR.second) {
				if (recArr[i].state != 2) {
					recArr[i].state = 1;
				}
			}
			else {
				// ������ �������� �κ������� �������� üũ
				/* ������ ������ ���
					1. A�� ���� �𼭸��� B�� ���� �𼭸��� ���ų� �� �����ʿ� �־����
					2. A�� ���� �𼭸��� B�� ���� �𼭸��� ���ų� �� ���� �־����
					3. A�� ������ �𼭸��� B�� ������ �𼭸��� ���ų� �� ���ʿ� �־����
					4. A�� ������ �𼭸��� B�� ������ �𼭸��� ���ų� �� �Ʒ��� �־����

					-- B�� �������� ��� A�𼭸��� �ϳ��� �ٱ����� ������ 2
				*/
				// �κ������� ���� ��
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