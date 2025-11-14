import re


def part1(lines):
    sum = 0
    for line in lines:
        game_id = int(parse_game(line))
        is_possible = check_line(line)
        if is_possible:
            sum += game_id
    return sum


def part2(lines):
    sum = 0
    for line in lines:
        game_parts = parse_parts(line)
        r = 0
        g = 0
        b = 0
        for part in game_parts:
            r = max(r, parse_sum_by_color('red', part))
            g = max(g, parse_sum_by_color('green', part))
            b = max(b, parse_sum_by_color('blue', part))
        m = r * g * b
        sum += m

    return sum


def check_line(line):
    game_parts = parse_parts(line)
    for part in game_parts:
        if not check_part(part):
            return False
    return True


def parse_parts(parts):
    pattern = re.compile(r'[^;]+')
    return pattern.findall(parts)


def check_part(part) -> bool:
    max_dict = {'red': 12, 'green': 13, 'blue': 14}

    for key in max_dict.keys():
        if parse_sum_by_color(key, part) > max_dict.get(key):
            return False

    return True


def parse_game(text):
    return re.compile(r'Game (\d+)').findall(text)[0]


def parse_sum_by_color(color, text):
    pattern = re.compile(fr'(\d+) {color}')
    matches = pattern.findall(text)
    return sum([int(m) for m in matches])


if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        lines = file.readlines()
        print(part1(lines))
        print(part2(lines))
