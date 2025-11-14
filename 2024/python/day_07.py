import itertools


def generate_operators(n, operators_set):
    return [list(combination) for combination in itertools.product(operators_set, repeat=n)]


def execute_operator(operator, x, y):
    if operator == 0:
        return x + y
    if operator == 1:
        return x * y
    return int(str(x) + str(y))


def solve(equations, operators_set):
    result_sum = 0
    for equation in equations:
        target, numbers = equation
        for operator in generate_operators(len(numbers), operators_set):
            execution = numbers[0]
            for index, number in enumerate(numbers[1:], start=1):
                execution = execute_operator(operator[index - 1], execution, number)
            if execution == target:
                result_sum += execution
                break
    return result_sum


def part1(equations):
    return solve(equations, [0, 1])


def part2(equations):
    return solve(equations, [0, 1, 2])


if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        lines = file.readlines()
    equations = []
    for line in lines:
        target, numbers = line.strip().split(':')
        equations.append((int(target), list(map(int, numbers.strip().split()))))
    print(part1(equations))
    print(part2(equations))
