// C++ Program to Implement KD Tree
// KD Tree를 이용해서 KNN 구하기(초근접 노드 찾기)
// 여기선 입력값이 트리에 존재하는지 여부를 판단
#include <iostream>
#include <array>
#include <cmath>
using namespace std;

// Template class for KDTree with K dimensions
template <size_t K> // unsigned int(4bytes) 보다 데이터 관리에 효율적이다
                    // size_t는 malloc하고 연동되고, 8bytes 크기다

class KDTree {

private:
    // Node structure representing each point in the KDTree
    struct Node {
        // Point in K dimensions
        array<double, K> point; //고정된 크기의 배열
        // Pointer to left child
        Node* left;
        // Pointer to right child
        Node* right;

        // Constructor to initialize a Node
        Node(const array<double, K>& pt) : point(pt), left(nullptr), right(nullptr) {}
    };

    Node* root; // Root of the KDTree

    // Recursive function to insert a point into the KDTree
    Node* insertRecursive(Node* node, const array<double, K>& point, int depth) {
        // Base case: If node is null, create a new node
        if (node == nullptr) return new Node(point);

        // Calculate current dimension (cd)
        int cd = depth % K;

        // Compare point with current node and decide to go left or right
        if (point[cd] < node->point[cd])
            node->left = insertRecursive(node->left, point, depth + 1);
        else
            node->right = insertRecursive(node->right, point, depth + 1);

        return node;
    }

    // Recursive function to search for a point in the KDTree
    bool searchRecursive(Node* node, const array<double, K>& point, int depth) const {
        // Base case: If node is null, the point is not found
        if (node == nullptr) return false;

        // If the current node matches the point, return true
        if (node->point == point) return true;

        // Calculate current dimension (cd)
        int cd = depth % K;

        // Compare point with current node and decide to go left or right
        if (point[cd] < node->point[cd])
            return searchRecursive(node->left, point, depth + 1);
        else
            return searchRecursive(node->right, point, depth + 1);
    }

    // Recursive function to print the KDTree
    void printRecursive(Node* node, int depth) const {
        // Base case: If node is null, return
        if (node == nullptr) return;

        // Print current node with indentation based on depth
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << "(";
        for (size_t i = 0; i < K; i++) {
            cout << node->point[i];
            if (i < K - 1) cout << ", ";
        }
        cout << ")" << endl;

        // Recursively print left and right children
        printRecursive(node->left, depth + 1);
        printRecursive(node->right, depth + 1);
    }

public:
    // Constructor to initialize the KDTree with a null root
    KDTree() : root(nullptr) {}

    // Public function to insert a point into the KDTree
    void insert(const array<double, K>& point) {
        root = insertRecursive(root, point, 0);
    }

    // Public function to search for a point in the KDTree
    bool search(const array<double, K>& point) const {
        return searchRecursive(root, point, 0);
    }

    // Public function to print the KDTree
    void print() const {
        printRecursive(root, 0);
    }
};

int main() {
    // Create a KDTree with 2 dimensions
    KDTree<2> tree;

    // Insert points into the KDTree
    tree.insert({ 3, 6 });
    tree.insert({ 2, 2 });
    tree.insert({ 4, 7 });
    tree.insert({ 1, 3 });
    tree.insert({ 2, 4 });
    tree.insert({ 5, 4 });
    tree.insert({ 7, 2 });

    // Print the KDTree structure
    cout << "KD Tree structure:" << endl;
    tree.print();

    // Search for specific points in the KDTree
    array<double, 2> searchPoint = { 2, 4 };
    cout << "\nSearching for point (2, 4): "
        << (tree.search(searchPoint) ? "Found" : "Not found") << endl;

    searchPoint = { 6, 3 };
    cout << "Searching for point (6, 3): "
        << (tree.search(searchPoint) ? "Found" : "Not found") << endl;

    return 0;
}
