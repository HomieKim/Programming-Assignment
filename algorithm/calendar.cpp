#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

/* 윤년 계산 하는 법 : 4로 나누어 떨어지고 100으로 나누어 떨어지 거나 400으로 나누어 떨어지면 윤년
1월 : 31
2월 : 윤년이면 29일 아니면 28일
3월 : 31일
4월 : 30일
5월 : 31일
6월 : 30일
7월 : 31일
8월 : 31일
9월 : 30일
10월 : 31일
11월 : 30일
12월 : 31일
*/


// 윤년 확인 하는 함수 
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

int map[6][7]; //  특정요일이 유효한지 검사하려면 달력만들어서 체크해야함

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
bool isPossible_2(calendar cal) {// cal에 count 번째 dayOfWeek가 존재하면 false 존재하지 않으면 true
	// 몇번째 요일인지 구하는 법??,, 1년 1월 1일이 월요일 이니까 7로 나눈 나머지에 +1 하면 시작요일
	int datyOfMonth[12] = { 31, 28, 31, 30, 31, 30,31, 31,30,31,30,31 };
	int cnt = 0;
	int startDay;
	for (int i = 1; i < cal.year; i++) { // 1년 부터 year - 1년 까지 일 수 더함
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
	// 첫번째 목요일이 첫째주 목요일이 아니네,, count 번째 나오는 요일을 체크
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
	for (int i = 1; i < cal.year; i++) { // 1년 부터 year - 1년 까지 일 수 더함
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
				// isPossible_2가 true == cal2의 count번째 day_w요일이 존재 하지 않는다
				flag = 1;
			}
			else {
				// 존재하면 해당 요일이 며칠인지 알면 calcDay함수 재사용하면 됨
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