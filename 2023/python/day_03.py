def part1(mtx):
    result = 0
    for i in range(len(mtx)):
        for j in range(len(mtx[i])):
            char = mtx[i][j]
            if not char.isdigit() and char != '.':
                nums = [get_adjacent_number(i, j - 1, mtx), get_adjacent_number(i, j + 1, mtx)]
                top = get_adjacent_number(i - 1, j, mtx)
                if top is None:
                    nums.append(get_adjacent_number(i - 1, j - 1, mtx))
                    nums.append(get_adjacent_number(i - 1, j + 1, mtx))
                else:
                    nums.append(top)

                bot = get_adjacent_number(i + 1, j, mtx)
                if bot is None:
                    nums.append(get_adjacent_number(i + 1, j - 1, mtx))
                    nums.append(get_adjacent_number(i + 1, j + 1, mtx))
                else:
                    nums.append(bot)

                filtered = [i for i in nums if i is not None]
                result += sum(filtered)

    return result


def part2(mtx):
    result = 0
    for i in range(len(mtx)):
        for j in range(len(mtx[i])):
            char = mtx[i][j]
            if char == '*':
                nums = [get_adjacent_number(i, j - 1, mtx), get_adjacent_number(i, j + 1, mtx)]

                top = get_adjacent_number(i - 1, j, mtx)
                if top is None:
                    nums.append(get_adjacent_number(i - 1, j - 1, mtx))
                    nums.append(get_adjacent_number(i - 1, j + 1, mtx))
                else:
                    nums.append(top)

                bot = get_adjacent_number(i + 1, j, mtx)
                if bot is None:
                    nums.append(get_adjacent_number(i + 1, j - 1, mtx))
                    nums.append(get_adjacent_number(i + 1, j + 1, mtx))
                else:
                    nums.append(bot)

                filtered = [i for i in nums if i is not None]
                if len(filtered) == 2:
                    result += filtered[0] * filtered[1]

    return result


def get_adjacent_number(i, j, mtx):
    if not (0 <= i < len(mtx) and 0 <= j < len(mtx[0])):
        return None
    if not mtx[i][j].isdigit():
        return None
    number = ''
    start_j = j
    while j >= 0 and mtx[i][j].isdigit():
        number = mtx[i][j] + number
        j -= 1
    j = start_j + 1
    while j < len(mtx[i]) and mtx[i][j].isdigit():
        number += mtx[i][j]
        j += 1
    return int(number) if number != '' else None


if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        lines = file.readlines()
        matrix = [list(line.strip()) for line in lines]
        rv1 = part1(matrix)
        rv2 = part2(matrix)
        print(rv1)
        print(rv2)
