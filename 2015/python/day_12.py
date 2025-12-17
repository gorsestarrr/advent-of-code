import json


def part1(s: str) -> int:
    n = len(s)
    i = 0
    result = 0
    buffer = []
    while i < n:
        while s[i].isdigit() or s[i] == '-':
            buffer.append(s[i])
            i += 1
        if buffer:
            result += int("".join(buffer))
            buffer.clear()
        i += 1

    return result

def remove_red(obj):
    if isinstance(obj, dict):
        if 'red' in obj.values():
            return None
        cleaned = {}
        for k, v in obj.items():
            result = remove_red(v)
            if result is not None:
                cleaned[k] = result
        return cleaned
    elif isinstance(obj, list):
        cleaned = []
        for v in obj:
            res = remove_red(v)
            if res is not None:
                cleaned.append(res)
        return cleaned
    return obj


def part2(s: str) -> int:
    return part1(json.dumps(remove_red(json.loads(s))))

if __name__ == '__main__':
    with open('input.txt') as f:
        lines = f.readline()
        print(part1(lines))
        print(part2(lines))