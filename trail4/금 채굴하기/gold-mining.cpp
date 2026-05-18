#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct Coor {
    int x, y;
};

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

int N, M;
vector<vector<int>> map;

bool oob(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= N)
        return true;
    return false;
}

int bfs(Coor start, int K) {
    int cnt = 0;
    queue<Coor> que;
    vector<vector<int>> visited(N, vector<int>(N, 0));

    que.push({start.x, start.y});
    visited[start.x][start.y] = 1;
    if (map[start.x][start.y] == 1)
        cnt++;

    while (!que.empty()) {
        Coor now = que.front();
        que.pop();

        if (visited[now.x][now.y] > K)
            continue;

        for (int dir = 0; dir < 4; dir++) {
            int nx = now.x + dx[dir];
            int ny = now.y + dy[dir];
            if (oob(nx, ny))
                continue;
            if (visited[nx][ny] != 0)
                continue;
            que.push({nx, ny});
            visited[nx][ny] = visited[now.x][now.y] + 1;
            if (map[nx][ny] == 1)
                cnt++;
        }
    }
    return cnt;
}

int main() {
    // Please write your code here.
    cin >> N >> M;
    map.resize(N, vector<int>(N));
    
    int golds = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1)
                golds++;
        }
    }

    int max_cnt = 0;

    for (int k = 0; k < 2 * N; k++) {
        int cost = k * k + (k + 1) * (k + 1);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int cnt = bfs({i, j}, k);
                if (cnt * M >= cost) {
                    max_cnt = max(max_cnt, cnt);
                }
            }
        }
    }
    cout << max_cnt;

    return 0;
}