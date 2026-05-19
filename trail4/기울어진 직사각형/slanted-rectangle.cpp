#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Coor {
    int x, y;
};

int dx[4] = {-1, -1, 1, 1};
int dy[4] = {1, -1, -1, 1};

int N;
vector<vector<int>> map;

int now_num = 0;
int max_num = 0;

bool oob(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= N)
        return true;
    return false;
}

void backtrack(Coor start, int dir, Coor begin) {
    if (dir >= 4) {
        if (start.x != begin.x || start.y != begin.y)
            return;
        max_num = max(max_num, now_num);
        return;
    }

    int accum = 0;
    for (int k = 1; k < N; k++) { // N번 나가면 어차피 out
        int nx = start.x + dx[dir] * k;
        int ny = start.y + dy[dir] * k;
        if (oob(nx, ny))
            continue;
        accum += map[nx][ny];
        now_num += map[nx][ny];
        backtrack({nx, ny}, dir + 1, begin);
    }
    now_num -= accum;
}

int main() {
    // Please write your code here.
    cin >> N;
    map.resize(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            backtrack({i, j}, 0, {i, j});
        }
    }
    cout << max_num;

    return 0;
}