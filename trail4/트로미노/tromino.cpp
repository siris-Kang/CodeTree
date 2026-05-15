#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

int N, M;
vector<vector<int>> map;
vector<vector<int>> visited;
int now_num = 0;
int max_num = 0;

bool oob(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M)
        return true;
    return false;
}

void backtrack(int depth, int x, int y) {
    if (depth >= 2) {
        max_num = max(max_num, now_num);
        return;
    }

    for (int dir = 0; dir < 4; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (oob(nx, ny))
            continue;
        if (visited[nx][ny] == 1)
            continue;
        now_num += map[nx][ny];
        visited[nx][ny] = 1;
        backtrack(depth + 1, nx, ny);
        now_num -= map[nx][ny];
        visited[nx][ny] = 0;
    }
}

int main() {
    // Please write your code here.
    cin >> N >> M;
    map.resize(N, vector<int>(M));
    visited.resize(N, vector<int>(M, 0));
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            now_num += map[i][j];
            visited[i][j] = 1;
            backtrack(0, i, j);
            now_num -= map[i][j];
            visited[i][j] = 0;
        }
    }
    cout << max_num << endl;

    return 0;
}