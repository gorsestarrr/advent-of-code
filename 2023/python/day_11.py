def parse_grid(lines):
    rows_expanded = []
    columns_expanded = []
    for i in range(len(lines)):
        if '#' not in lines[i]:
            rows_expanded.append(i)
    for col_index in range(len(lines[0]) - 1):
        current_column = ""
        for row in lines:
            current_column += row[col_index]
        if '#' not in current_column:
            columns_expanded.append(col_index)
    grid = {}
    num = 1
    for y, line in enumerate(lines):
        for x, char in enumerate(line):
            if char == '#':
                grid[num] = (x, y)
                num += 1
    return grid, rows_expanded, columns_expanded


def distance(grid, rows_expanded, columns_expanded, expansion_dist):
    sums = []
    for f in range(1, len(grid) + 1):
        for s in range(f + 1, len(grid) + 1):
            current_sum = 0
            x_additional = 0
            y_additional = 0
            x_edges = sorted([grid[s][0], grid[f][0]])
            y_edges = sorted([grid[s][1], grid[f][1]])
            for x in range(x_edges[0], x_edges[1]):
                if x in columns_expanded:
                    x_additional += expansion_dist
            for y in range(y_edges[0], y_edges[1]):
                if y in rows_expanded:
                    y_additional += expansion_dist
            current_sum += y_edges[1] - y_edges[0] + y_additional + x_edges[1] - x_edges[0] + x_additional
            sums.append(current_sum)
    return sum(sums)


if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        lines = file.readlines()
        grid, rows_expanded, columns_expanded = parse_grid(lines)
        print(distance(grid, rows_expanded, columns_expanded, 1))
        print(distance(grid, rows_expanded, columns_expanded, 1000000 - 1))
