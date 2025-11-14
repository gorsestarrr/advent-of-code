from collections import Counter


def part1(left_list, right_list):
    return sum([abs(l - r) for l, r in zip(sorted(left_list), sorted(right_list))])


def part2(left_list, right_list):
    count_map = dict(Counter(right_list))
    result = 0
    for val in left_list:
        result += val * count_map.get(val, 0)
    return result


if __name__ == '__main__':
    left_list = []
    right_list = []
    with open('input.txt', 'r') as file:
        for line in file:
            a, b = map(int, line.split())
            left_list.append(a)
            right_list.append(b)
    print("Part 1:", part1(left_list, right_list))
    print("Part 2:", part2(left_list, right_list))
