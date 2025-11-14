import itertools

def part1(matrix):
    rows, cols = len(matrix), len(matrix[0])
    antennas_location = {}
    for y, row in enumerate(matrix):
        for x, char in enumerate(row):
            if char != '.':
                if char not in antennas_location:
                    antennas_location[char] = []
                antennas_location[char].append((x, y))
    antinodes = set()
    for key in antennas_location:
        antennas = antennas_location[key]
        combinations = list(itertools.combinations(antennas, 2))
        for combo in combinations:
            (first, second) = combo
            distance_x = abs(first[0] - second[0])
            distance_y = abs(first[1] - second[1])
            slope = None if second[0] - first[0] == 0 else (second[1] - first[1]) / (second[0] - first[0])
            if slope is None:  # Vertical line
                antinode1 = (first[0], first[1] - distance_y)
                antinode2 = (second[0], second[1] - distance_y)
            elif slope > 0:
                antinode1 = (first[0] - distance_x, first[1] - distance_y)
                antinode2 = (second[0] + distance_x, second[1] + distance_y)
            elif slope < 0:
                antinode1 = (first[0] + distance_x, first[1] - distance_y)
                antinode2 = (second[0] - distance_x, second[1] + distance_y)
            else:  # Horizontal line
                antinode1 = (first[0] - distance_x, first[1])
                antinode2 = (second[0] + distance_x, second[1])
            antinodes.update({
                node for node in [antinode1, antinode2]
                if 0 <= node[0] < cols and 0 <= node[1] < rows
            })
    return len(antinodes)

def part2(matrix):
    rows, cols = len(matrix), len(matrix[0])
    antennas_location = {}
    for y, row in enumerate(matrix):
        for x, char in enumerate(row):
            if char != '.':
                if char not in antennas_location:
                    antennas_location[char] = []
                antennas_location[char].append((x, y))
    antinodes = set()
    for key in antennas_location:
        antennas = antennas_location[key]
        combinations = list(itertools.combinations(antennas, 2))
        for combo in combinations:
            (first, second) = combo
            distance_x = abs(first[0] - second[0])
            distance_y = abs(first[1] - second[1])
            slope = None if second[0] - first[0] == 0 else (second[1] - first[1]) / (second[0] - first[0])
            if slope is None:  # Vertical line
                dx, dy = 0, distance_y
            elif slope > 0:
                dx, dy = distance_x, distance_y
            elif slope < 0:
                dx, dy = distance_x, -distance_y
            else:  # Horizontal line
                dx, dy = distance_x, 0
            for direction in [1, -1]:  # Forward and backward directions
                current_x, current_y = first[0], first[1]
                while 0 <= current_x < cols and 0 <= current_y < rows:
                    antinodes.add((current_x, current_y))
                    current_x += dx * direction
                    current_y += dy * direction
                current_x, current_y = second[0], second[1]
                while 0 <= current_x < cols and 0 <= current_y < rows:
                    antinodes.add((current_x, current_y))
                    current_x += dx * direction
                    current_y += dy * direction
    return len(antinodes)


if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        matrix = [list(line) for line in file.read().strip().split('\n')]
        print(part1(matrix))
        print(part2(matrix))
