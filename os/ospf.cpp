#include <stdio.h>
#include<iostream>
#include<vector>
#include<queue>

using namespace std;
#define INF 1e9 // ������ �ǹ��ϴ� ������ 10���� ����


// ����� ������ �ִ� 100,000����� ����
int start;
int cnt = 0;

vector<pair<int, int> > graph[100001]; // �� ��忡 ����Ǿ� �ִ� ��忡 ���� ������ ��� �迭
int d[100001]; // �ִ� �Ÿ� ���̺� �����

void dijkstra(int start)
{
    cout << "--- callFunc ---" << endl;
    priority_queue<pair<int, int>>pq; // �Ÿ�, ��� �ε���

    pq.push({ 0, start }); //���� ���� �������� �ִ� ��δ� 0���� �����Ͽ�, ť�� ����.
    d[start] = 0;

    while (!pq.empty())
    {
        cnt++;
        int dist = -pq.top().first; //���� �������� ���
        int now = pq.top().second; // ���� ���
        pq.pop();

        if (d[now] < dist) // �̹� �ִܰ�θ� üũ�� ����� ��� �н�
            continue;

     

        for (int i = 0; i < graph[now].size(); i++)
        {
            int cost = dist + graph[now][i].second; // ���ļ� ���� ����� ����� ���
                                                  // ��������� ��� + ���� ��� ���
            if (cost < d[graph[now][i].first]) // ����� �� �۴ٸ� �ִܰ�� ���̺� ���� ����.
            {
                d[graph[now][i].first] = cost; // �ִܰŸ��� ���õ�, �� ���� �� ���ǹ� d[now] < dist ���� continue �ȵǸ� ���� �� ����! �ִ�.
                pq.push(make_pair(-cost, graph[now][i].first));
            }
        }
       
    }
}

int main(void)
{

    cout << "--- ��� c ���� g ���� ����� 24�� �� ---" << endl;
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

    // �ִ� �Ÿ� ���̺��� ��� �������� �ʱ�ȭ
    fill(d, d + 100001, INF);

    // ���ͽ�Ʈ�� �˰����� ����
    dijkstra(start);
    cout << "While��" << cnt << "�� ����" << endl;
    cout << "--- endFunc ---" << endl;


    // ��� ���� ���� ���� �ִ� �Ÿ��� ���
    for (int i = 1; i <= 16; i++)
    {
        // ������ �� ���� ���, ����(INFINITY)�̶�� ���
        if (d[i] == INF) {
            cout << "INFINITY" << '\n';
        }
        // ������ �� �ִ� ��� �Ÿ��� ���
        else {
            cout << node[i]<<" ���� ���� �ּҺ�� : " <<d[i] << '\n';
        }
    }
}