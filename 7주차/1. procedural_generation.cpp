#include <iostream>
#include <vector>
#include <random>
using namespace std;

struct Node {
    int parent;
    int level;
};

int Find(vector<Node>& node, int x) {
    if (node[x].parent == x) return x;
    return node[x].parent = Find(node, node[x].parent);
}

void Union(vector<Node>& node, int a, int b) {
    int rootA = Find(node, a);
    int rootB = Find(node, b);

    if (rootA != rootB) {
        node[rootB].parent = rootA;
    }
}

int main() {
    int n, m;
    cout << "Height & Width: ";
    cin >> n >> m;

    vector<vector<char>> height_wall(n, vector<char>(m - 1, '|'));
    vector<vector<char>> width_wall(n - 1, vector<char>(m, '-'));
    vector<Node> node(n * m);
    
    for (int i = 0; i < n * m; i++) {
        node[i].parent = i;
        node[i].level = 0;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> randN(0, n - 1);
    uniform_int_distribution<int> randM(0, m - 1);
    uniform_int_distribution<int> randDir(0, 1);

    while (true) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (Find(node, i * m + j) == Find(node, 0)) count++;
            }
        }
        if (count == n * m) break;

        int rand_i = randN(gen);
        int rand_j = randM(gen);
        int direct = randDir(gen);

        if (direct == 0 && rand_j + 1 < m &&
            Find(node, rand_i * m + rand_j) != Find(node, rand_i * m + rand_j + 1)) {
            Union(node, rand_i * m + rand_j, rand_i * m + rand_j + 1);
            height_wall[rand_i][rand_j] = ' ';
        }
        else if (direct == 1 && rand_i + 1 < n &&
                 Find(node, rand_i * m + rand_j) != Find(node, rand_i * m + rand_j + m)) {
            Union(node, rand_i * m + rand_j, rand_i * m + rand_j + m);
            width_wall[rand_i][rand_j] = ' ';
        }
    }

    for (int i = 0; i < m; i++) cout << "+-";
    cout << "+\n";

    for (int i = 0; i < n; i++) {
        cout << "|";
        for (int j = 0; j < m - 1; j++) cout << " " << height_wall[i][j];
        cout << " |\n";
        
        if (i < n - 1) {
            for (int j = 0; j < m; j++) cout << "+" << width_wall[i][j];
            cout << "+\n";
        }
    }

    for (int i = 0; i < m; i++) cout << "+-";
    cout << "+\n";
    
    return 0;
}
