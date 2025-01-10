from collections import deque

def BFS():
    n, m = map(int, input().split())
    maze = []
    for i in range(n):
        maze.append(list(map(int, input().strip())))

    visit = [[0] * m for i in range(n)]

    x_move = [1, -1, 0, 0]
    y_move = [0, 0, 1, -1]

    queue = deque()
    queue.append((0, 0, 1))
    visit[0][0] = 1

    while queue:
        curr_x, curr_y, curr_steps = queue.popleft()

        if curr_x == n - 1 and curr_y == m - 1:
            print(curr_steps)
            return

        for i in range(4):
            new_x = curr_x + x_move[i]
            new_y = curr_y + y_move[i]

            if 0 <= new_x < n and 0 <= new_y < m and not visit[new_x][new_y] and maze[new_x][new_y] == 1:
                visit[new_x][new_y] = 1
                queue.append((new_x, new_y, curr_steps + 1))

BFS()
# boj 2178
