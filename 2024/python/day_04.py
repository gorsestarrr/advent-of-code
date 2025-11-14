def part1(grid):
    rows = len(grid)
    cols = len(grid[0])
    directions = [
        (-1, -1), (-1, 0), (-1, 1),
        (0, -1), (0, 1),
        (1, -1), (1, 0), (1, 1)
    ]

    def check_word(grid, word, row, col, dx, dy):
        for i in range(len(word)):
            r = row + i * dx
            c = col + i * dy
            if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] != word[i]:
                return False
        return True

    def count(grid, word, directions):
        count = 0
        for row in range(rows):
            for col in range(cols):
                for dx, dy in directions:
                    if check_word(grid, word, row, col, dx, dy):
                        count += 1
        return count

    return count(grid, 'XMAS', directions)


def part2(grid):
    rows = len(grid)
    cols = len(grid[0])
    count = 0
    for row in range(rows):
        for col in range(cols):
            if not (1 <= row < rows - 1 and 1 <= col < cols - 1):
                continue
            if grid[row][col] != "A":
                continue
            left_diag = grid[row - 1][col - 1] + grid[row + 1][col + 1]
            right_diag = grid[row - 1][col + 1] + grid[row + 1][col - 1]
            if left_diag in {'SM', 'MS'} and right_diag in {'SM', 'MS'}:
                count += 1
    return count


if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        grid = [list(line.strip()) for line in file if line.strip()]
        print(part1(grid))
        print(part2(grid))
