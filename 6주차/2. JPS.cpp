#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <chrono>

#define ROWS 8
#define COLS 8

using namespace std;
using namespace chrono;

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// A*와 JPS에서 사용할 노드 구조체
struct Node {
    Point pos;
    int g, h, f;
    Node* parent;

    Node(Point p, int g_cost, int h_cost, Node* par = nullptr) {
        pos = p;
        g = g_cost;
        h = h_cost;
        f = g + h;
        parent = par;
    }
};

// 우선순위 큐를 위한 비교 연산자
struct Compare {
    bool operator()(const Node* a, const Node* b) {
        return a->f > b->f;
    }
};

// 맨해튼 거리 휴리스틱 함수
int heuristic(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}



// JPS에서 점프 포인트 찾기
Point jump(int grid[ROWS][COLS], Point current, int dx, int dy, Point goal) {
    int x = current.x, y = current.y;

    while (true) {
        x += dx;
        y += dy;

        if (x < 0 || x >= ROWS || y < 0 || y >= COLS || grid[x][y] == 1) {
            return {}; // 벽에 막히거나 맵을 벗어나면 종료
        }

        if (Point{x, y} == goal) return {x, y}; // 목표 지점에 도달하면 반환

        // 강제 점프 포인트 탐색 (좌우 또는 상하 이동 중 장애물이 있는 경우)
        if ((dx != 0 && ((y + 1 < COLS && grid[x][y + 1] == 0 && grid[x - dx][y + 1] == 1) ||
            (y - 1 >= 0 && grid[x][y - 1] == 0 && grid[x - dx][y - 1] == 1))) ||
            (dy != 0 && ((x + 1 < ROWS && grid[x + 1][y] == 0 && grid[x + 1][y - dy] == 1) ||
                (x - 1 >= 0 && grid[x - 1][y] == 0 && grid[x - 1][y - dy] == 1)))) {
            return Point{x, y}; // 강제 점프 포인트 발견
        }
    }
}

// JPS 알고리즘
Node* jps(int grid[ROWS][COLS], Point start, Point goal, int& visitedCount) {
    priority_queue<Node*, vector<Node*>, Compare> openList;
    vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));

    Node* startNode = new Node(start, 0, heuristic(start, goal));
    openList.push(startNode);

    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();
        visited[current->pos.x][current->pos.y] = true;
        visitedCount++;

        if (current->pos == goal) return current;

        for (int i = 0; i < 4; i++) {
            Point jumpPoint = jump(grid, current->pos, directions[i][0], directions[i][1], goal);
            if (jumpPoint.x != -1 && !visited[jumpPoint.x][jumpPoint.y]) {
                int g_new = current->g + heuristic(current->pos, jumpPoint);
                int h_new = heuristic(jumpPoint, goal);
                Node* neighbor = new Node(jumpPoint, g_new, h_new, current);

                openList.push(neighbor);
                visited[neighbor->pos.x][neighbor->pos.y] = true;
            }
        }
    }
    return nullptr;
}

// 최단 경로 출력 함수
void printPath(Node* goalNode, const string& algorithm) {
    if (!goalNode) {
        cout << algorithm << " 경로를 찾을 수 없습니다.\n";
        return;
    }

    vector<vector<int>> path(ROWS, vector<int>(COLS, 0));
    Node* temp = goalNode;
    int length = 0;
    while (temp) {
        path[temp->pos.x][temp->pos.y] = 2;
        temp = temp->parent;
        length++;
    }

    cout << algorithm << " 최단 경로 길이: " << length - 1 << endl;
    for (const auto& row : path) {
        for (int cell : row) cout << cell << " ";
        cout << endl;
    }
}

int main() {
    int grid[ROWS][COLS] = {
        {0, 0, 0, 0, 1, 0, 0, 0},
        {1, 1, 1, 0, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 0}
    };

    int visitedA = 0, visitedJPS = 0;
    //Node* goalA = astar(grid, { 0, 0 }, { 7, 7 }, visitedA);
    //printPath(goalA, "A*");

    Node* goalJPS = jps(grid, { 0, 0 }, { 7, 7 }, visitedJPS);
    printPath(goalJPS, "JPS");

    return 0;
}
