
def DFS(graph, start, visit, order, order_num):
    visit[start] = 1
    order[start] = order_num
    order_num += 1

    for node in sorted(graph[start]):
        if visit[node] == 0:
            DFS(graph, node, visit, order, order_num)

import sys
sys.setrecursionlimit(150000)
            
n, m, r = map(int, input().split())
graph = [[] for i in range(n + 1)]
for i in range(n):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

visit = [0] * (n + 1)
order = [0] * (n + 1)
order_num = 1

DFS(graph, r, visit, order, order_num)

for i in range(1, n + 1):
    print(order[i])
# boj 24479
