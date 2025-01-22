import heapq

MAX = 99999
n = 15

graph = {
    0: [(1, 165), (7, 127), (14, 351)],
    1: [(0, 165), (7, 285), (13, 385)],
    2: [(5, 371), (11, 359)],
    3: [(4, 370), (6, 247), (10, 447), (13, 331)],
    4: [(3, 370), (8, 383), (12, 138), (14, 335)],
    5: [(2, 371), (9, 218)],
    6: [(3, 247), (8, 364), (10, 325), (11, 380), (12, 307)],
    7: [(0, 127), (1, 285), (14, 401)],
    8: [(4, 383), (6, 364), (12, 291)],
    9: [(5, 218)],
    10: [(3, 447), (6, 325), (11, 185)],
    11: [(2, 359), (6, 380), (10, 185)],
    12: [(4, 138), (6, 307), (8, 291), (13, 201), (14, 405)],
    13: [(1, 385), (3, 331), (12, 201), (14, 430)],
    14: [(0, 351), (4, 335), (7, 401), (12, 405), (13, 430)]
}

def dijkstra(start):
    distance = [MAX] * n
    distance[start] = 0

    pq = []
    heapq.heappush(pq, (0, start))  # (distance, node)

    while pq:
        current_dist, current_node = heapq.heappop(pq)

        if current_dist > distance[current_node]:
            continue

        for neighbor, weight in graph.get(current_node, []):
            new_dist = current_dist + weight
            if new_dist < distance[neighbor]:
                distance[neighbor] = new_dist
                heapq.heappush(pq, (new_dist, neighbor))

    return distance

for i in range(n):
    distances = dijkstra(i)
    for d in distances:
        if d == MAX:
            print("inf", end="\t")
        else:
            print(d, end="\t")
    print()
