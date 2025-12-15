def is_number(s):
    try:
        int(s)
        return True
    except ValueError:
        return False

def eval(rules, memo, wire):
    if is_number(wire):
        return int(wire)

    if wire in memo:
        return memo[wire]

    rule = rules[wire]

    if "AND" in rule:
        a, b = rule.split("AND")
        result = eval(rules, memo, a.strip()) & eval(rules, memo, b.strip())

    elif "OR" in rule:
        a, b = rule.split("OR")
        result = eval(rules, memo, a.strip()) | eval(rules, memo, b.strip())

    elif "LSHIFT" in rule:
        a, b = rule.split("LSHIFT")
        result = eval(rules, memo, a.strip()) << eval(rules, memo, b.strip())

    elif "RSHIFT" in rule:
        a, b = rule.split("RSHIFT")
        result = eval(rules, memo, a.strip()) >> eval(rules, memo, b.strip())

    elif rule.startswith("NOT"):
        a = rule.split("NOT")[1].strip()
        result = ~eval(rules, memo, a)
    else:
        result = eval(rules, memo, rule)

    result &= 0xFFFF
    memo[wire] = result

    return result


def solve(rules, wire):
    return eval(rules, {}, wire)

if __name__ == '__main__':
    with open('input.txt') as f:
        lines = f.readlines()
        rules = {}
        for line in lines:
            l = line.split('->')
            rules[l[1].strip()] = l[0].strip()
    print(solve(rules, "a"))
