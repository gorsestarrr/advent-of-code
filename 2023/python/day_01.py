import string


def part1(line: string) -> int:
    first_digit = next(char for char in line if char.isdigit())
    last_digit = next(char for char in reversed(line) if char.isdigit())
    return int(str(first_digit) + str(last_digit))


def part2prepare(line: string) -> string:
    word_list = {
        "one": 1,
        "two": 2,
        "three": 3,
        "four": 4,
        "five": 5,
        "six": 6,
        "seven": 7,
        "eight": 8,
        "nine": 9,
    }
    for key, value in word_list.items():
        if key in line:
            line = line.replace(key, key[0] + str(value) + key[-1])
    return line


def part2(line: string) -> int:
    return part1(part2prepare(line))


if __name__ == '__main__':
    rv1 = 0
    rv2 = 0
    with open('input.txt', 'r') as file:
        lines = file.readlines()
        for line in lines:
            rv1 += part1(line)
            rv2 += part2(line)

    print(str(rv1))
    print(str(rv2))
