#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<pair<int, int>> zeroIdx;
int T, n;
int board[9][9];
char section[9][9];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
bool rowChk(int x, int num) {
	for (int i = 0; i < 9; i++) {
		if (board[x][i] == num) return false;
	}
	return true;
}
bool colChk(int y, int num) {
	for (int i = 0; i < 9; i++) {
		if (board[i][y] == num) return false;
	}
	return true;
}

bool sectionChk(int x, int y, int num) {
	char tmp = section[x][y];
	queue<pair<int,int>> Q;
	int vis[9][9] = { 0, };
	Q.push({ x,y });
	vis[x][y] = 1;
	while (!Q.empty()) {
		auto cur = Q.front();
		Q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = cur.first + dx[i];
			int ny = cur.second + dy[i];
			if (nx < 0 || ny < 0 || ny > 9 || nx > 9) continue;
			if (vis[nx][ny] == 1) continue;
			if (section[nx][ny] != tmp) continue;
			if (board[nx][ny] == num) {
				return false;
			}
			else {
				Q.push({ nx,ny });
				vis[nx][ny] = 1;
			}
			
		}
	}

	return true;
}
bool chk(int x, int y, int i) {
	if (rowChk(x, i) && colChk(y, i) && sectionChk(x, y, i)) {
		return true;
	}
	else {
		return false;
	}
}

void print_board() {
	cout << "Test Cast No:" << endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
			cout << board[i][j] << ' ';
		cout << '\n';
	}
}
void dfs(int num) {
	if (num == zeroIdx.size()) {
		print_board();
	}

	for (int i = 1; i <= 9; i++) {
		int x = zeroIdx[num].first;
		int y = zeroIdx[num].second;
		if (chk(x, y, i)) {
			board[x][y] = i;
			dfs(num + 1);
			board[x][y] = 0;
		}
	}
}
int main() {

	cin >> T;

	while (T--) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cin >> board[i][j];
				if (board[i][j] == 0) {
					zeroIdx.push_back({ i,j });
				}
			}
		}

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cin >> section[i][j];
			}
		}

		dfs(0);
		memset(board, 0, sizeof(board));
		memset(section, 0, sizeof(section));
	}


}