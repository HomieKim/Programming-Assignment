#include <stdio.h>
#include<iostream>
#include<vector>
#include<queue>

using namespace std;
#define INF 1e9 // 무한을 의미하는 값으로 10억을 설정


// 노드의 개수는 최대 100,000개라고 가정
int start;
int cnt = 0;

vector<pair<int, int> > graph[100001]; // 각 노드에 연결되어 있는 노드에 대한 정보를 담는 배열
int d[100001]; // 최단 거리 테이블 만들기

void dijkstra(int start)
{
    cout << "--- callFunc ---" << endl;
    priority_queue<pair<int, int>>pq; // 거리, 노드 인덱스

    pq.push({ 0, start }); //시작 노드로 가기위한 최단 경로는 0으로 설정하여, 큐에 삽입.
    d[start] = 0;

    while (!pq.empty())
    {
        cnt++;
        int dist = -pq.top().first; //현재 노드까지의 비용
        int now = pq.top().second; // 현재 노드
        pq.pop();

        if (d[now] < dist) // 이미 최단경로를 체크한 노드인 경우 패스
            continue;

     

        for (int i = 0; i < graph[now].size(); i++)
        {
            int cost = dist + graph[now][i].second; // 거쳐서 가는 노드의 비용을 계산
                                                  // 현재노드까지 비용 + 다음 노드 비용
            if (cost < d[graph[now][i].first]) // 비용이 더 작다면 최단경로 테이블 값을 갱신.
            {
                d[graph[now][i].first] = cost; // 최단거리가 선택됨, 이 값은 위 조건문 d[now] < dist 에서 continue 안되면 갱신 될 수도! 있다.
                pq.push(make_pair(-cost, graph[now][i].first));
            }
        }
       
    }
}

int main(void)
{

    cout << "--- 노드 c 에서 g 가는 비용이 24일 때 ---" << endl;
    char node[] = {' ','a','b','c', 'd', 'e','f','g','h','i','j','k','l','m','n','o','p'};

    start = 1;
    graph[1].push_back({ 2, 4 });
    graph[1].push_back({ 3, 2 });
    graph[1].push_back({ 4, 7 });

    graph[2].push_back({ 3, 6 });
    graph[2].push_back({ 7, 9 });
    graph[2].push_back({ 6, 4 });
    graph[2].push_back({ 5, 6 });

    graph[3].push_back({ 7, 24 });

    graph[4].push_back({ 1, 4 });
    graph[4].push_back({ 8, 3 });

    graph[6].push_back({ 5, 2 });
    graph[6].push_back({ 10, 13 });
    graph[6].push_back({ 9, 8 });

    graph[7].push_back({ 4, 2 });
    graph[7].push_back({ 8, 4 });
    graph[7].push_back({ 11, 4 });
    graph[7].push_back({ 10, 4 });
    graph[7].push_back({ 6, 2 });

    graph[8].push_back({ 13, 3 });
    graph[8].push_back({ 12, 6 });
    graph[8].push_back({ 11, 4 });

    graph[9].push_back({ 14, 3 });

    graph[10].push_back({ 15, 7 });
    graph[10].push_back({ 14, 3 });
    graph[10].push_back({ 9, 8 });

    graph[11].push_back({ 16, 2 });
    graph[11].push_back({ 10, 2 });

    graph[13].push_back({ 16, 15 });
    
    graph[16].push_back({ 14, 2 });

    // 최단 거리 테이블을 모두 무한으로 초기화
    fill(d, d + 100001, INF);

    // 다익스트라 알고리즘을 수행
    dijkstra(start);
    cout << "While문" << cnt << "번 돈다" << endl;
    cout << "--- endFunc ---" << endl;


    // 모든 노드로 가기 위한 최단 거리를 출력
    for (int i = 1; i <= 16; i++)
    {
        // 도달할 수 없는 경우, 무한(INFINITY)이라고 출력
        if (d[i] == INF) {
            cout << "INFINITY" << '\n';
        }
        // 도달할 수 있는 경우 거리를 출력
        else {
            cout << node[i]<<" 노드로 가는 최소비용 : " <<d[i] << '\n';
        }
    }
}