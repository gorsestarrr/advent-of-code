import re


def get_matches(win_deck, own_deck):
    counter = 0
    for card in own_deck:
        if card in win_deck:
            counter += 1
    return counter


def part1(game):
    result = 0
    for deck in game:
        matches = get_matches(deck[0], deck[1])
        result += 2 ** (matches - 1) if matches > 0 else 0

    return result


def part2(game):
    card_matching_nums = []
    for deck in game:
        card_matching_nums.append(get_matches(deck[0], deck[1]))

    card_amounts = [1] * len(card_matching_nums)
    for index, card in enumerate(card_matching_nums):
        for j in range(index + 1, index + card + 1):
            card_amounts[j] += card_amounts[index]
    return sum(card_amounts)


if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        lines = file.readlines()
        game = []
        for line in lines:
            pattern = r'\b\d+\b'
            after_colon = line.split(':')[-1]
            parts_before_pipe = after_colon.split('|')
            before_pipe = parts_before_pipe[0]
            matches_before_pipe = re.findall(pattern, before_pipe)
            digits_before_pipe = [int(match) for match in matches_before_pipe]
            after_pipe = parts_before_pipe[1]
            matches_after_pipe = re.findall(pattern, after_pipe)
            digits_after_pipe = [int(match) for match in matches_after_pipe]
            game.append((matches_before_pipe, matches_after_pipe))
            
        print(part1(game))
        print(part2(game))
