#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

/* ���� ��� �ϴ� �� : 4�� ������ �������� 100���� ������ ������ �ų� 400���� ������ �������� ����
1�� : 31
2�� : �����̸� 29�� �ƴϸ� 28��
3�� : 31��
4�� : 30��
5�� : 31��
6�� : 30��
7�� : 31��
8�� : 31��
9�� : 30��
10�� : 31��
11�� : 30��
12�� : 31��
*/


// ���� Ȯ�� �ϴ� �Լ� 
//bool isLeapYear() {
//	return null;
//}
struct Cal {
	int year;
	int month;
	int day;
	int count;
	string dayOfWeek;
}typedef calendar;

int map[6][7]; //  Ư�������� ��ȿ���� �˻��Ϸ��� �޷¸��� üũ�ؾ���

bool isPossible(calendar cal) {
	int datyOfMonth[12] = { 31, 28, 31, 30, 31, 30,31, 31,30,31,30,31 };
	int year = cal.year;
	int month = cal.month;
	int day = cal.day;
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
		datyOfMonth[1]++;
	}
	if (day > datyOfMonth[month-1]) return true;
	else return false;
}
int getDay(string str) {
	//0 : Sun, 1 :  Mon, 2 : Tue, 3 :  Wed, 4 : Thu, 5 :  Fri, 6 : Sat
	int num;
	if (str == "Sun") {
		num = 0;
	}
	else if (str == "Mon") {
		num = 1;
	}
	else if (str == "Tue") {
		num = 2;
	}
	else if (str == "Wed") {
		num = 3;
	}
	else if (str == "Thu") {
		num = 4;
	}
	else if (str == "Fri") {
		num = 5; 
	}
	else if (str == "Sat") {
		num = 6;
	}

	return num;
}
bool isPossible_2(calendar cal) {// cal�� count ��° dayOfWeek�� �����ϸ� false �������� ������ true
	// ���° �������� ���ϴ� ��??,, 1�� 1�� 1���� ������ �̴ϱ� 7�� ���� �������� +1 �ϸ� ���ۿ���
	int datyOfMonth[12] = { 31, 28, 31, 30, 31, 30,31, 31,30,31,30,31 };
	int cnt = 0;
	int startDay;
	for (int i = 1; i < cal.year; i++) { // 1�� ���� year - 1�� ���� �� �� ����
		if (((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0)) {
			cnt += 366;
		}
		else {
			cnt += 365;
		}
	}

	for (int i = 1; i < cal.month; i++) {
		if (i == 2) {
			if (((cal.year % 4 == 0) && (cal.year % 100 != 0)) || (cal.year % 400 == 0)) {
				cnt += 29;
			}
			else {
				cnt += 28;
			}
		}
		else if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
			cnt += 31;
		}
		else {
			cnt += 30;
		}
	}
	//0 : Sun, 1 :  Mon, 2 : Tue, 3 :  Wed, 4 : Thu, 5 :  Fri, 6 : Sat

	startDay = (cnt % 7) + 1;
	if (startDay == 7) startDay = 0;
	
	if (((cal.year % 4 == 0) && (cal.year % 100 != 0)) || (cal.year % 400 == 0)) {
		datyOfMonth[1]++;
	}
	int d_cnt = 1;
	for (int i = startDay; i < 7; i++) {
		map[0][i] = d_cnt;
		d_cnt++;
	}

	for (int i = 1; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			map[i][j] = d_cnt;
			d_cnt++;
			if (d_cnt > datyOfMonth[cal.month - 1]) break;
		}
		if (d_cnt > datyOfMonth[cal.month - 1]) break;
	}

	int day_idx = getDay(cal.dayOfWeek);
	// ù��° ������� ù°�� ������� �ƴϳ�,, count ��° ������ ������ üũ
	int chk = 0;
	int tmpCnt = 0;
	for (int i = 0; i < 6; i++) {

		if (map[i][day_idx] == 0) {
			continue;
		}
		else {
			tmpCnt++;
		}
		
		if (cal.count == tmpCnt) {
			chk = 1; break;
		}
	}

	if (chk) {
		return false;
	}
	else {
		return true;
	}
	
}
int calcDayOfWeek(calendar cal) {
	int num;
	int day_idx = getDay(cal.dayOfWeek);
	int tmpCnt = 0;
	for (int i = 0; i < 6; i++) {
		if (map[i][day_idx] == 0) continue;
		else {
			tmpCnt++;
		}

		if (cal.count == tmpCnt) {
			num = map[i][day_idx]; 
			break;
		}
	}


	return num;

}
int calcDay(calendar cal) {
	int cnt = 0;
	for (int i = 1; i < cal.year; i++) { // 1�� ���� year - 1�� ���� �� �� ����
		if (((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0)) {
			cnt += 366;
		}
		else {
			cnt += 365;
		}
	}

	for (int i = 1; i < cal.month; i++) {
		if (i == 2) {
			if (((cal.year % 4 == 0) && (cal.year % 100 != 0)) || (cal.year % 400 == 0)) {
				cnt += 29;
			}
			else {
				cnt += 28;
			}
		}
		else if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
			cnt += 31;
		}
		else {
			cnt += 30;
		}
	}

	cnt += cal.day;

	return cnt;
}

int main() {
	
	ifstream fin("calendar.inp");
	ofstream fout("calendar.out");
	int type;
	int y, y2;
	int m, m2;
	int d, d2;
	char bar;

	int count1, count2;
	string day_w, day_w2;

	int flag;
	int tmp;
	calendar cal1;
	calendar cal2;

	while (true) {
		fin >> type;
		if (type == -1) break;
		cal1.count = 0; cal1.day = 0; cal1.month = 0; cal1.year = 0; cal1.dayOfWeek = "";
		cal2.count = 0; cal2.day = 0; cal2.month = 0; cal2.year = 0; cal2.dayOfWeek = "";
		switch (type)
		{
		case 0: //0 2016-2-28 2017-2-28
			fin >> y >> bar >> m >> bar >> d >> y2 >> bar >> m2 >> bar >> d2;
			cal1.year = y; cal1.month = m; cal1.day = d;
			cal2.year = y2; cal2.month = m2; cal2.day = d2;
			flag = 0;

			if (isPossible(cal1)) flag = 1;
			if (isPossible(cal2)) flag = 1;

			if (flag) {
				fout << -1 << '\n';
			}
			else {
				int dayCnt1 = calcDay(cal1);
				int dayCnt2 = calcDay(cal2);

				fout << abs(dayCnt2 - dayCnt1) << '\n';
			}
			memset(map, 0, sizeof(map));
			break;
		case 1:  // 1 2017-5-13 2017-5-2-Sat  --> 
			fin >> y >> bar >> m >> bar >> d >> y2 >> bar >> m2 >> bar >> count2 >> bar >> day_w2;
			cal1.year = y; cal1.month = m; cal1.day = d;
			cal2.year = y2; cal2.month = m2; cal2.count = count2; cal2.dayOfWeek = day_w2;
			flag = 0; tmp = 0;
			if (isPossible(cal1)) flag = 1;
			if (isPossible_2(cal2)) {
				// isPossible_2�� true == cal2�� count��° day_w������ ���� ���� �ʴ´�
				flag = 1;
			}
			else {
				// �����ϸ� �ش� ������ ��ĥ���� �˸� calcDay�Լ� �����ϸ� ��
				tmp = calcDayOfWeek(cal2);
				cal2.day = tmp;
			}

			if (flag) {
				fout << -1 << '\n';
			}
			else {
				int dayCnt1 = calcDay(cal1);
				int dayCnt2 = calcDay(cal2);

				fout << abs(dayCnt2 - dayCnt1) << '\n';
			}
			memset(map, 0, sizeof(map));
			break;
		case 2:  // 2 2017-1-3-Sat 2017-1-16
			fin >> y >> bar >> m >> bar >> count1 >> bar >> day_w >> y2 >> bar >> m2 >> bar >> d2;
			cal1.year = y; cal1.month = m; cal1.count = count1; cal1.dayOfWeek = day_w;
			cal2.year = y2; cal2.month = m2; cal2.day = d2;

			flag = 0; tmp = 0;
			if (isPossible_2(cal1)) {
				flag = 1;
			}
			else {
				tmp = calcDayOfWeek(cal1);
				cal1.day = tmp;
			}
			if (isPossible(cal2)) flag = 1;


			if (flag) {
				fout << -1 << '\n';
			}
			else {
				int dayCnt1 = calcDay(cal1);
				int dayCnt2 = calcDay(cal2);

				fout << abs(dayCnt2 - dayCnt1) << '\n';
			}

			memset(map, 0, sizeof(map));
			break;
		case 3:  // 3 2017-12-1-Fri 2017-2-3-Mon
			fin >> y >> bar >> m >> bar >> count1 >> bar >> day_w >> y2 >> bar >> m2 >> bar >> count2 >> bar >> day_w2;
			cal1.year = y; cal1.month = m; cal1.count = count1; cal1.dayOfWeek = day_w;
			cal2.year = y2; cal2.month = m2; cal2.count = count2; cal2.dayOfWeek = day_w2;

			flag = 0; tmp = 0;
			if (isPossible_2(cal1)) {
				flag = 1;
			}
			else {
				tmp = calcDayOfWeek(cal1);
				cal1.day = tmp;
			}
			memset(map, 0, sizeof(map));
			if (isPossible_2(cal2)) {
				flag = 1;
			}
			else {
				tmp = calcDayOfWeek(cal2);
				cal2.day = tmp;
			}

			if (flag) {
				fout << -1 << '\n';
			}
			else {
				int dayCnt1 = calcDay(cal1);
				int dayCnt2 = calcDay(cal2);

				fout << abs(dayCnt2 - dayCnt1) << '\n';
			}

			memset(map, 0, sizeof(map));
			break;
		}
	}


	fout.close();
	fin.close();
	return 0;
}