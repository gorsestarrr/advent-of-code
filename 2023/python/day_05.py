import re

# Brute Forced ha-ha

def parse(file):
    line = file.read().strip().split('\n\n')
    seeds = [int(x) for x in re.findall('\d+', line[0])]
    ranges = []
    for x in line[1:]:
        y = x.split('\n')
        ranges.append([[int(w) for w in re.findall('\d+', z)] for z in y[1:]])
    return seeds, ranges


def process(val, ranges):
    for range in ranges:
        for d, s, w in range:
            if s <= val < (s + w):
                val = val - s + d
                break
    return val


def part1(seeds, ranges):
    return min([process(seed, ranges) for seed in seeds])


def part2(seeds_with_width, ranges):
    seeds = [seeds_with_width[i] for i in range(len(seeds_with_width)) if i % 2 == 0]
    width = [seeds_with_width[i] for i in range(len(seeds_with_width)) if i % 2 != 0]
    total = []
    for i in range(len(seeds)):
        total.append((seeds[i], width[i]))
    ranges = [r[::-1] for r in ranges[::-1]]
    for r in ranges:
        for t in r:
            temp = t[0]
            t[0] = t[1]
            t[1] = temp
    location = 0
    while True:
        possible_seed = process(location, ranges)
        for s in total:
            if s[0] <= possible_seed < s[0] + s[1]:
                return location
        location = location + 1


if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        seeds, ranges = parse(file)
        rv1 = part1(seeds, ranges)
        rv2 = part2(seeds, ranges)
        print(rv1)
        print(rv2)
