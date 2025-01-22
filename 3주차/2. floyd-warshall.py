MAX = 99999
n = 15
map = [[MAX for _ in range(n)] for _ in range(n)]

graph = [
    (0, 1, 165), (0, 7, 127), (0, 14, 351), (1, 7, 285), (1, 13, 385),
    (2, 5, 371), (2, 11, 359), (3, 4, 370), (3, 6, 247), (3, 10, 447),
    (3, 13, 331), (4, 8, 383), (4, 12, 138), (4, 14, 335), (5, 9, 218),
    (6, 8, 364), (6, 10, 325), (6, 11, 380), (6, 12, 307), (7, 14, 401),
    (8, 12, 291), (10, 11, 185), (12, 13, 201), (12, 14, 405), (13, 14, 430)
]

for u, v, cost in graph:
    map[u][v] = cost
    map[v][u] = cost

for i in range(n): map[i][i] = 0

# Floyd-Warshall algorithm
for k in range(n):
    for i in range(n):
        for j in range(n):
            new_dis = map[i][k] + map[k][j]
            if new_dis < map[i][j]:
                map[i][j] = new_dis

for i in range(n):
    for j in range(n):
        if map[i][j] == 99999:
            print("inf", end="\t")
        else:
            print(map[i][j], end="\t")
    print("\n")
