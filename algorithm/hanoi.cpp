#include <iostream>
#include <vector>
#pragma warning(disable:4996)

/*
빨간색은 순서 반대로 되야함
파란색은 순서 그대로여야 됨
초록색은 순서 상관 없음
한번 이동 하면 순서 반대로 됨
move count가 홀수면 순서 반대인 상태
*/

struct MyStruct
{
	char color;
	int num;
	int move_count;
	int location;
}typedef disk;

using namespace std;
int T;
int rst = 0;

vector<disk> tower(26);
int now;
void hanoi(int n, int start, int dest, int by)
{
	if (n <= 0) return;
	hanoi(n - 1, start, dest, by);
	tower[n].move_count++;
	tower[n].location = dest;
	rst += tower[n].num;
	hanoi(n - 1, by, start, dest);
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("hanoi.inp", "r", stdin);
	freopen("hanoi.out", "w", stdout);
	cin >> T;
	int m;
	char input_color;
	int input_num;
	while (T--)
	{
		cin >> m;
		for (int i = 1; i <= m; i++) {
			cin >> input_color >> input_num;
			tower[i].color = input_color;
			tower[i].num = input_num;
			tower[i].location = 1;
			tower[i].move_count = 0;
		}

		for (int i = m; i >= 1; i--) {
			int now = tower[i].location;
			int by;
			int dest=3;

			(now == 1) ? by = 2 : by = 1;
			//색깔이 초록이거나 빨강인데 이동횟수 짝수, 파랑인데 이동횟수 홀수면 바로 3번으로 가면됨
			if (tower[i].color == 'G' || tower[i].num == 1 ||
				(tower[i].color == 'R' && tower[i].move_count % 2 == 0) ||
				(tower[i].color == 'B' && tower[i].move_count % 2 == 1)) {
				hanoi(i-1, now, dest, by);
				tower[i].move_count++;
				tower[i].location = dest;
				rst += tower[i].num;
			}
			else {
				// 색깔조건을 맞추기 위해 by를 한번 경유하고 3번으로 이동해야함
				hanoi(i-1, now, by, dest );
				tower[i].move_count++;
				tower[i].location = by;
				rst += tower[i].num;

				hanoi(i-1, by, dest, now);
				tower[i].move_count++;
				tower[i].location = dest;
				rst += tower[i].num;

				if (i == 1) rst--;
			} 

		}
		 
		cout << rst << '\n';
		rst = 0;
	}


}
