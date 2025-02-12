#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <cstring>
#include <numeric>
#include <cmath>
#include <cstdio>
using namespace std;

char map[10][10];   // 'W'는 이동할 수 있는 칸, 'B'는 이동할 수 없는 칸
int cnt = 0;        // 임의의 좌표를 기준으로 이동할 수 있는 칸의 총 개수 -> 최종적으로 출력하기
bool visited[10][10] = {false,};    // 탐색할 때 해당 칸을 이미 방문했는지 판단하는 배열 -> 중복 방지

int x_move[4] = {1, -1, 0, 0};
int y_move[4] = {0, 0, 1, -1};

queue<pair<int, int>> Q;

void init();
void BFS();

int main() {
    init(); // map의 상태를 설정하는 함수
    BFS();  // 너비 우선 탐색을 통해 이동할 수 있는 칸을 찾는 함수
    cout << cnt << endl;
    return 0;
}

void init() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i + j == 3 || i + j == 15) map[i][j] = 'B';
            else map[i][j] = 'W';
        }
    }
}

void BFS() {
    int x, y;
    cin >> x >> y;  // 임의로 좌표값을 입력하기
    if (map[x][y] == 'B') return;  // 입력한 좌표값이 이동할 수 없는 칸이라면..?

    visited[x][y] = true;
    cnt++;
    Q.push({x, y});
    
    while (!Q.empty()) {
        int curr_x = Q.front().first;
        int curr_y = Q.front().second;
        Q.pop();
        
        for (int i = 0; i < 4; i++) {
            int new_x = curr_x + x_move[i];
            int new_y = curr_y + y_move[i];
            
            if (new_x >= 0 && new_x <= 9 &&
                new_y >= 0 && new_y <= 9) {        // 새로운 좌표값이 맵의 크기에 알맞는지 확인
                
                if (!visited[new_x][new_y] && map[new_x][new_y] == 'B') {    // 새로운 좌표값이 처음 방문하는 칸이고, W인지 확인
                    
                    visited[new_x][new_y] = true;
                    cnt++;
                    Q.push({new_x, new_y});
                }
            }
        }
    }
}
