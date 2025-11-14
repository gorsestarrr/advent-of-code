import math
import re
import numpy as np

def parse_part1(file):
    times = re.findall('\d+', file.readline())
    distances = re.findall('\d+', file.readline())
    return tuple(zip(list(map(int, times)), list(map(int, distances))))

def part1(races):
    result = 1
    for race in races:
        roots = np.roots([1, -race[0], race[1]])
        diff = math.ceil(roots[0]) - math.floor(roots[1]) - 1
        result *= diff
    return result

def part2(time, dist):
    roots = np.roots([1, -time, dist])
    return math.ceil(roots[0]) - math.floor(roots[1]) - 1

if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        rv1 = part1(parse_part1(file))
        print(rv1)
        rv2 = part2(55999793, 401148522741405)
        print(rv2)
