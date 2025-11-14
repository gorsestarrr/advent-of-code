import math
import re
from functools import reduce


def parse(all_data_lines):
    directions_arr = all_data_lines[0].replace('L', '0').replace('R', '1').strip()
    instructions_dict = {}
    pattern = re.compile(r'(\w+)\s*=\s*\((.+)\)')
    for line in all_data_lines:
        match = pattern.match(line.strip())
        if match:
            instructions_dict[match.group(1)] = tuple(map(str.strip, match.group(2).split(',')))
    return directions_arr, instructions_dict


def solve_one(directions_arr, instructions_dict, start_from, ends_with):
    steps = index = 0
    current = instructions_dict[start_from]
    position = current[int(directions_arr[index])]
    while not position.endswith(ends_with):
        position = current[int(directions_arr[index])]
        current = instructions_dict[position]
        index = (index + 1) % len(directions_arr)
        steps += 1
    return steps


def part1(directions_arr, instructions_dict):
    return solve_one(directions_arr, instructions_dict, 'AAA', 'ZZZ')


def part2(directions_arr, instructions_dict):
    return reduce(
        math.lcm,
        [
            solve_one(directions_arr, instructions_dict, key, 'Z')
            for key in [key for key in instructions_dict.keys() if key.endswith('A')]
        ]
    )

if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        directions_arr, instructions_dict = parse(file.readlines())
        rv1 = part1(directions_arr, instructions_dict)
        print(rv1)
        rv2 = part2(directions_arr, instructions_dict)
        print(rv2)
