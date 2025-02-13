#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

#define ROWS 8
#define COLS 8
#define INF 99999

using namespace std;

// 좌표 구조체
struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    } // 연산자 오버로딩 -> 중요한 개념!
};

// 노드 구조체 (A*에서 사용)
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
        return a->f > b->f; // f 값이 작은 노드가 우선 탐색됨
    }
};

// 맨해튼 거리 휴리스틱 함수
int heuristic(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// A* 알고리즘
Node* astar(int grid[ROWS][COLS], Point start, Point goal) {
    priority_queue<Node*, vector<Node*>, Compare> openList;
    vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));
    //초기화
    Node* startNode = new Node(start, 0, heuristic(start, goal));
    openList.push(startNode);

    // 이동 가능한 방향 (상, 하, 좌, 우)
    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (current->pos == goal) { // current->pos.operator==(goal) 로도 쓸 수 있음
                                    // by 연산자 오버로딩
            return current; // 목표 지점 도달 시 최단 경로 반환
        }

        visited[current->pos.x][current->pos.y] = true;

        // 상, 하, 좌, 우 탐색
        for (int i = 0; i < 4; i++) {
            int newX = current->pos.x + directions[i][0];
            int newY = current->pos.y + directions[i][1];

            if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS &&
                grid[newX][newY] == 0 && !visited[newX][newY]) {

                int g_new = current->g + 1; // g 값 갱신
                int h_new = heuristic({newX, newY}, goal);
                Node* neighbor = new Node({newX, newY}, g_new, h_new, current);

                openList.push(neighbor);
                visited[newX][newY] = true;
            }
        }
    }
    return nullptr; // 경로 없음
}

// 경로 출력 함수
void printPath(Node* goalNode) {
    if (!goalNode) {
        cout << "경로를 찾을 수 없습니다.\n";
        return;
    }

    int path[ROWS][COLS] = { 0 };
    Node* temp = goalNode;
    while (temp) {
        path[temp->pos.x][temp->pos.y] = 2; // 경로 표시
        temp = temp->parent;
    }

    cout << "최단 경로 (2로 표시됨):\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << path[i][j] << " ";
        }
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

    Point start = { 0, 0 };  // 시작점
    Point goal = { 7, 7 };   // 목표점

    Node* goalNode = astar(grid, start, goal);
    printPath(goalNode);

    return 0;
}
