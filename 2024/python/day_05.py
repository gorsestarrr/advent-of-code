from functools import cmp_to_key


def check_update(rules, update):
    left_set = set()
    for u in update:
        if u in left_set:
            return False
        if u in rules:
            left_set.update(r for r in rules[u])
    return True


def part1(rules, updates):
    return sum(update[len(update) // 2] for update in updates if check_update(rules, update))


def custom_comparator(x, y):
    def compare(x, y):
        if x in rules and x in rules[y]:
            return False
        if y in rules and y in rules[x]:
            return True
        for next_value in rules.get(x, []):
            if compare(next_value, y):
                return True
        return False
    if compare(x, y):
        return 1
    elif compare(y, x):
        return -1
    else:
        return 0


def part2(rules, updates):
    incorrect_updates = [u for u in updates if not check_update(rules, u)]
    return sum(sorted(update, key=cmp_to_key(custom_comparator))[len(update) // 2] for update in incorrect_updates)


if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        pairs, lists = file.read().strip().split("\n\n")
        rules = {}
        for line in pairs.splitlines():
            value, key = map(int, line.split('|'))
            if key not in rules:
                rules[key] = []
            rules[key].append(value)
        updates = [list(map(int, lst.split(','))) for lst in lists.splitlines()]
        print(part1(rules, updates))
        print(part2(rules, updates))
