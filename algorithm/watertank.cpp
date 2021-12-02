#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#pragma warning(disable:4996)

using namespace std;

/* 처음 N,M,H */
struct  Node
{
    int hight;
    int x;
    int y;
    int hole[4]; // 상 하 좌 우 순서대로
    /*
    0: 상
    1: 하
    2: 좌
    3: 우
    */
}typedef node;

struct cmp {
    bool operator()(node a,node b) { return a.hight > b.hight; }
};

int horizon[1002][1002];
int vertical[1002][1002];
node tank[1002][1002];

int N, M, H, T;
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
priority_queue<node,vector<node>, cmp> pq;
// 큐에 노드를 push할 때 순서 오류

int bfs() {
    int sum = 0;
    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
       
        for (int i = 0; i < 4; i++) {
            if (cur.hole[i] == -1) continue;
            int new_y = cur.y + dy[i];
            int new_x = cur.x + dx[i];
            if (new_x < 0 || new_y < 0 || new_y > N || new_x > M) continue;
            int tmp_min = min(tank[cur.y][cur.x].hole[i], tank[new_y][new_x].hight);
            int next_h = max(tmp_min, tank[cur.y][cur.x].hight);
            if (tank[new_y][new_x].hight > next_h) {
                tank[new_y][new_x].hight = next_h;
                pq.push(tank[new_y][new_x]);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            sum += tank[i][j].hight;
        }
    }
    return sum;
}

int solve() {
    int ans = 0;
    // 가장자리 노드 큐에 담음
    //상
    for (int i = 0; i < M; i++) {
        if (tank[0][i].hole[0] != -1) {
            if (tank[0][i].hight < tank[0][i].hole[0]) continue;
            tank[0][i].hight = tank[0][i].hole[0];
            pq.push(tank[0][i]);
        }
    }
    //하
    for (int i = 0; i < M; i++) {
        if (tank[N-1][i].hole[1] != -1) {
            if (tank[N-1][i].hight < tank[N-1][i].hole[1]) continue;
            tank[N - 1][i].hight = tank[N - 1][i].hole[1];
            pq.push(tank[N-1][i]);
        }
    }
    //좌
    for (int i = 0; i < N; i++) {
        if (tank[i][0].hole[2] != -1) {
            if (tank[i][0].hight < tank[i][0].hole[2]) continue;
            tank[i][0].hight = tank[i][0].hole[2];
            pq.push(tank[i][0]);
        }
    }
    //우
    for (int i = 0; i < N; i++) {
        if (tank[i][M - 1].hole[3] != -1) {
            if (tank[i][M-1].hight < tank[i][M-1].hole[3]) continue;
            tank[i][M - 1].hight = tank[i][M - 1].hole[3];
            pq.push(tank[i][M-1]);
        }
    }
    ans = bfs();
    return ans;
}

void init() {

    for (int i = 0; i < 1002; i++) {
        for (int j = 0; j < 1002; j++) {
            horizon[i][j] = 0;
            vertical[i][j] = 0;
            tank[i][j].y = 0;
            tank[i][j].x = 0;
            tank[i][j].hight = 0;
            tank[i][j].hole[0] = 0;
            tank[i][j].hole[1] = 0;
            tank[i][j].hole[2] = 0;
            tank[i][j].hole[3] = 0;
        }
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    //freopen("watertank.inp", "r", stdin);
    //freopen("watertank.out", "w", stdout);
       
    cin >> T;
    int ans;
    while (T--) {
        // 2 3 5
        cin >> N >> M >> H;
        int tmp;
        // 가로 구멍 입력
        for (int i = 0; i < N + 1; i++) {
            for (int j = 0; j < M; j++) {
                cin >> tmp;
                horizon[i][j] = tmp;
            }
        }
        // 세로 구멍 입력
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M + 1; j++) {
                cin >> tmp;
                vertical[i][j] = tmp;
            }
        }
        // 초기 세팅
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                tank[i][j].x = j;
                tank[i][j].y = i;
                tank[i][j].hight = H;
            }
        }
        // 가로 구멍 세팅
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // 상
                if (horizon[i][j] == -1) {
                    tank[i][j].hole[0] = -1;
                }
                else {
                    tank[i][j].hole[0] = horizon[i][j];
                }
                //하
                if (horizon[i + 1][j] == -1) {
                    tank[i][j].hole[1] = -1;
                }
                else {
                    tank[i][j].hole[1] = horizon[i + 1][j];
                }
            }
        }
        // 세로 구멍 세팅
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // 좌
                if (vertical[i][j] == -1) {
                    tank[i][j].hole[2] = -1;
                }
                else {
                    tank[i][j].hole[2] = vertical[i][j];
                }
                // 우
                if (vertical[i][j + 1] == -1) {
                    tank[i][j].hole[3] = -1;
                }
                else {
                    tank[i][j].hole[3] = vertical[i][j + 1];
                }
            }
        }

        ans = solve();
        cout << ans << '\n';
        init();

    }
}