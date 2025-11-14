from collections import deque


def parse(lines):
    graph, grid = {}, {}
    start_node = None
    for column, line in enumerate(lines):
        for row, char in enumerate(line.strip()):
            moves = {
                ".": [],
                "|": [(row, column - 1), (row, column + 1)],
                "-": [(row - 1, column), (row + 1, column)],
                "L": [(row, column - 1), (row + 1, column)],
                "J": [(row - 1, column), (row, column - 1)],
                "7": [(row - 1, column), (row, column + 1)],
                "F": [(row + 1, column), (row, column + 1)],
                "S": [(row - 1, column), (row + 1, column), (row, column - 1), (row, column + 1)],
            }
            # Remove moves with negative values
            filtered_moves = {key: [coord for coord in value if all(c >= 0 for c in coord)] for key, value in
                              moves.items()}
            graph[row, column] = filtered_moves[char]
            grid[row, column] = char
            if char == "S":
                start_node = (row, column)

    return graph, grid, start_node


def bfs(graph, start_node):
    queue = deque([start_node])
    visited = set([start_node])

    while queue:
        current_node = queue.popleft()
        for neighbor in graph[current_node]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)

    return list(visited)

if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        lines = file.readlines()
        graph, grid, start_node = parse(lines)
        path = bfs(graph, start_node)
        print(len(path) // 2)
        count = 0
        for y in range(len(lines[0])):
            p = 0
            for x in range(len(lines)):
                if (x, y) not in path:
                    if p % 2 == 1:
                        count += 1
                    continue
                if grid[(x,y)] in ['|', 'L', 'J']:
                    p += 1
        print(count)
