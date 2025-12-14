import string


def part1(lines):
    count = 0
    vowels = ['a', 'e', 'i', 'o', 'u']
    for line in lines:
        if "ab" in line:
            continue
        if "cd" in line:
            continue
        if "pq" in line:
            continue
        if "xy" in line:
            continue

        vowel_count = 0
        for c in line:
            if c in vowels:
                vowel_count += 1

        if vowel_count < 3:
            continue

        for i in range(len(line) - 1):
            if line[i] == line[i + 1]:
                count += 1
                break
    return count

def has_non_overlapping_pair(s: str) -> bool:
    for i in range(len(s) - 1):
        pair = s[i:i+2]
        if pair in s[i+2:]:
            return True
    return False

def has_repeat_with_one_between(s: str) -> bool:
    for i in range(len(s) - 2):
        if s[i] == s[i + 2]:
            return True
    return False

def part2(lines):
    count = 0
    for line in lines:
        if not has_non_overlapping_pair(line):
            continue
        if has_repeat_with_one_between(line):
            count += 1

    return count

if __name__ == '__main__':
    with open('input.txt') as f:
        lines = f.readlines()
        print(part1(lines))
        print(part2(lines))