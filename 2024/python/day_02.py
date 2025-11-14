def part1(level):
    down_limit = 1
    up_limit = 3
    if all(up_limit >= level[i + 1] - level[i] >= down_limit for i in range(len(level) - 1)):
        return True
    elif all(up_limit >= level[i] - level[i + 1] >= down_limit for i in range(len(level) - 1)):
        return True
    return False


def part2(level):
    down_limit = 1
    up_limit = 3
    if part1(level[1:]):
        return True
    is_asc = level[1] - level[0] > 0
    for i in range(len(level) - 1):
        if is_asc:
            if not (up_limit >= level[i + 1] - level[i] >= down_limit):
                if part1(level[:i] + level[i+1:]):
                    return True
                return part1(level[:i+1] + level[i+2:])
        else:
            if not (up_limit >= level[i] - level[i+1] >= down_limit):
                if part1(level[:i] + level[i+1:]):
                    return True
                return part1(level[:i +1] + level[i+2:])
    return True


if __name__ == '__main__':
    sum1 = 0
    sum2 = 0
    with open('input.txt', 'r') as file:
        for line in file:
            level = list(map(int, line.split()))
            rv1 = part1(level)
            rv2 = part2(level)
            sum1 += rv1 if rv1 else 0
            sum2 += rv2 if rv2 else 0
    print("Part 1:", sum1)
    print("Part 2:", sum2)
