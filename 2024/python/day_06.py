from enum import Enum


class Direction(Enum):
    UP = 1
    RIGHT = 2
    DOWN = 3
    LEFT = 4


rotation_map = {
    Direction.UP: Direction.RIGHT,
    Direction.RIGHT: Direction.DOWN,
    Direction.DOWN: Direction.LEFT,
    Direction.LEFT: Direction.UP,
}

moving_map = {
    Direction.UP: (-1, 0),
    Direction.RIGHT: (0, 1),
    Direction.DOWN: (1, 0),
    Direction.LEFT: (0, -1)
}


def part1(matrix):
    position = next((i, j) for i, row in enumerate(matrix) for j, char in enumerate(row) if char == '^')
    direction = Direction.UP
    rows, cols = len(matrix), len(matrix[0])
    steps_taken = {position}
    while True:
        x_current, y_current = position
        new_position = (x_current + moving_map[direction][0], y_current + moving_map[direction][1])
        x_new, y_new = new_position
        if not (0 <= x_new < rows and 0 <= y_new < cols):
            break
        if matrix[x_new][y_new] == '#':
            direction = rotation_map[direction]
        else:
            position = new_position
            steps_taken.add(position)
    return len(steps_taken)

def part2(matrix):
    rows, cols = len(matrix), len(matrix[0])
    start_position = next((i, j) for i, row in enumerate(matrix) for j, char in enumerate(row) if char == '^')
    start_direction = Direction.UP
    num_of_possible_loops = 0
    for i in range(rows):
        for j in range(cols):
            current_position = start_position
            current_direction = start_direction
            steps_taken = set()
            while True:
                x_current, y_current = current_position
                new_position = (x_current + moving_map[current_direction][0], y_current + moving_map[current_direction][1])
                x_new, y_new = new_position
                if not (0 <= x_new < rows and 0 <= y_new < cols):
                    break
                if matrix[x_new][y_new] == '#' or new_position == (i,j):
                    current_direction = rotation_map[current_direction]
                else:
                    current_position = new_position
                    step_key = (new_position, current_direction)
                    if step_key in steps_taken:
                        num_of_possible_loops += 1
                        break
                    steps_taken.add(step_key)

    return num_of_possible_loops


if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        matrix = [list(line) for line in file.read().strip().split('\n')]
        print(part1(matrix))
        print(part2(matrix))
