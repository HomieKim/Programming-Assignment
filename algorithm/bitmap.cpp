#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <string.h>


using namespace std;

ifstream fin("bitmap.inp");
ofstream fout("bitmap.out");

char bitmap[201][201];
int length = 0;
int cnt = 0;

/*
열의 수가 홀수인 경우 왼쪽 쿼터에 열이 하나 더있음
행 수가 홀수인 경우 위쪽 쿼터에 행이 하나 더있음
그냥 /2 해서 몫+1 이랑 몫
*/

bool chk(int a, int b, int c, int d) {
	char tmp = bitmap[a][b];
	int flag = 0;
	for (int i = a; i < c; i++) {
		for (int j = b; j < d; j++) {
			if (bitmap[i][j] != tmp) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) break;
	}

	if (flag == 1) {
		return false;
	}
	else {
		return true;
	}
}

void solveB(int start_y, int start_x, int row, int col ) {
	if (chk(start_y, start_x, row, col)) {
		fout << bitmap[start_y][start_x];
		length++;
		if (length % 50 == 0) fout << '\n';
	}
	else {
		// D인경우 -> 출력 후 4개로 분할
		// 하나의 행이나 하나의 열만 있는 경우 위쪽 먼저, 왼쪽 먼저
		fout << 'D';
		length++;
		if (length % 50 == 0) fout << '\n';

		int divide_row = ((start_y + row) % 2 == 0) ? (start_y + row) / 2 : (start_y + row) / 2 + 1;
		int divide_col = ((start_x + col) % 2 == 0) ? (start_x + col) / 2 : (start_x + col) / 2 + 1;
		// row, col값이 하나 크게 끝나야함
		if (row == start_y+1) { //행이 하나 일때
			// 왼쪽
			solveB(start_y, start_x, row, divide_col);
			// 오른쪽
			solveB(start_y, divide_col, row, col); 
		}
		else if (col == start_x+1) {   //열이 하나 일때
			//위
			solveB(start_y, start_x, divide_row ,col);
			//아래
			solveB(divide_row, start_x, row, col);

		}
		else {
			//왼쪽 위
			solveB(start_y, start_x, divide_row, divide_col);
			//오른쪽 위
			solveB(start_y, divide_col, divide_row, col);
			// 왼쪽 아래
			solveB(divide_row, start_x, row, divide_col);
			// 오른쪽 아래
			solveB(divide_row, divide_col, row, col);
		}
	}
}

void solveD(int start_y, int start_x, int row, int col) {
	// 입력 받고 D면 분할하고 아니면 입력 받은 1 또는 0으로 bitmap배열 채워넣고
	char data;
	fin >> data;
	
	if (data == 'D') {
		int divide_row = ((start_y + row) % 2 == 0) ? (start_y + row) / 2 : (start_y + row) / 2 + 1;
		int divide_col = ((start_x + col) % 2 == 0) ? (start_x + col) / 2 : (start_x + col) / 2 + 1;
		// row, col값이 하나 크게 끝나야함
		if (row == start_y + 1) { //행이 하나 일때
			// 왼쪽
			solveD(start_y, start_x, row, divide_col);
			// 오른쪽
			solveD(start_y, divide_col, row, col); 
		}
		else if (col == start_x + 1) {   //열이 하나 일때
			//위
			solveD(start_y, start_x, divide_row, col);
			//아래
			solveD(divide_row, start_x, row, col);

		}
		else {
			//왼쪽 위
			solveD(start_y, start_x, divide_row, divide_col);
			//오른쪽 위
			solveD(start_y, divide_col, divide_row, col);
			// 왼쪽 아래
			solveD(divide_row, start_x, row, divide_col);
			// 오른쪽 아래
			solveD(divide_row, divide_col, row, col);
		}

	}
	else {
		for (int i = start_y; i < row; i++) {
			for (int j = start_x; j < col; j++) {
				bitmap[i][j] = data;
			}
		}
	}


}

int main() {

	char type, inp_c;
	int row=0, col=0;
	while (true) {
		fin >> type >> row >> col;
		if (type == '#') break;
		if (type == 'B') {
			fout << "D " << row << " " << col << '\n';
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					fin >> inp_c;
					bitmap[i][j] = inp_c;
				}
			}
			solveB(0, 0, row, col);
			fout << '\n';
		}
		else {
			fout << "B " << row << " " << col << '\n';
			solveD(0, 0, row, col);
			for (int i = 0; i < row; i++) {
				for(int j = 0; j < col; j++) {
					fout << bitmap[i][j];
					length++;
					if (length % 50 == 0) {
						fout << '\n';
					}
				}
			}
			if (length % 50 != 0) fout << '\n';
		}
		length = 0;
		memset(bitmap, 0, sizeof(bitmap));
	}
	
	fin.close();
	fout.close();
	return 0;

}