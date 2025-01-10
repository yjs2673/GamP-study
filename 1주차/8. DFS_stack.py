def DFS(graph, start, order):
    stack = [start]
    visit = [0] * (n + 1)
    order_num = 1

    while stack:
        node = stack.pop()
        if visit[node] == 0:
            order[node] = order_num
            order_num += 1
            visit[node] = 1

            for adjacent in sorted(graph[node], reverse = True):
                if visit[adjacent] == 0: stack.append(adjacent)
        
n, m, r = map(int, input().split())
graph = [[] for i in range(n + 1)]
for i in range(n):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

order = [0] * (n + 1)

DFS(graph, r, order)

for i in range(1, n + 1):
    print(order[i])
# boj 24479
