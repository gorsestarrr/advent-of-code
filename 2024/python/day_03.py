import re


def part1(line):
    pattern = r'mul\((\d+),(\d+)\)'
    matches = re.findall(pattern, line)
    results = [(int(a), int(b), int(a) * int(b)) for a, b in matches]
    return sum(product for _, _, product in results)


def part2(line):
    line = f"do(){line}don't()"
    do_found = False
    for i in range(len(line) - 3):
        if line[i:i+4] == 'do()':
            if do_found:
                line = line[:i] + line[i + 4:]
            do_found = True
        elif line[i:i+7] == 'don\'t()':
            do_found = False
    matches = re.findall(r'do\(\)(.*?)don\'t\(\)', line, re.DOTALL)
    return sum(part1(match) for match in matches)


if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        text = file.read()
        print(part1(text))
        print(part2(text))
