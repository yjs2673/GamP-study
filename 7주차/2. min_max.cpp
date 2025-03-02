#include <stdio.h>
#include <limits.h>
// 알파-베타 가지치기
// 노드 개수 (예제 트리)
#define N 16

// 트리 노드 값 (예제)
int tree[N] = {7, -3, 5, 9, 2, 6, -8, 4, 10, -6, 1, 3, -2, 8, -4, 0};

// 미니맥스 함수 (알파-베타 가지치기 적용)
int minimax(int depth, int index, int alpha, int beta) {
    // 리프 노드에 도달하면 값 반환
    if (depth == 4) return tree[index];

    // MAX 노드 (플레이어)
    if (depth % 2 == 0) {
        int best = INT_MIN;
        for (int i = 0; i < 2; i++) {
            int val = minimax(depth + 1, index * 2 + i, alpha, beta);
            best = val > best ? val : best;
            alpha = alpha > val ? alpha : best; // 최댓값 갱신

            // 가지치기 (α ≥ β 이면 탐색 중단)
            if (beta <= alpha) break;
        }
        return best;
    }
    // MIN 노드 (상대 플레이어)
    else {
        int best = INT_MAX;
        for (int i = 0; i < 2; i++) {
            int val = minimax(depth + 1, index * 2 + i, alpha, beta);
            best = val < best ? val : best;
            beta = beta < best ? beta : best;

            // 가지치기 (α ≥ β 이면 탐색 중단)
            if (beta <= alpha) break;
        }
        return best;
    }
}

int main() {
    int alpha = INT_MIN, beta = INT_MAX;
    int result = minimax(0, 0, alpha, beta);
    printf("최적의 값: %d\n", result);
    return 0;
}
