from collections import defaultdict
from functools import cmp_to_key


class Card:
    def __init__(self, value, joker_mode):
        self.value = value
        self.joker_mode = joker_mode
        self.powers = ['2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A']
        self.powers.insert(0 if self.joker_mode else 9, 'J')

    def comparator(self, other):
        if self.value == other.value:
            return 0
        return 1 if self.powers.index(self.value) > self.powers.index(other.value) else -1

    def __hash__(self):
        return hash(self.value)

    def __repr__(self):
        return self.value

    def __iter__(self):
        return iter(self.value)

    def __eq__(self, other):
        return self.comparator(other) == 0

    def __lt__(self, other):
        return self.comparator(other) == -1

    def __gt__(self, other):
        return self.comparator(other) >= 1


class Hand:
    def __init__(self, cards, bid, joker_mode):
        self.cards = cards
        self.bid = bid
        self.joker_mode = joker_mode

    def get_combination(self):
        freq = defaultdict(int)
        for c in self.cards:
            freq[c] += 1
        if self.joker_mode:
            if ''.join([char.value for char in self.cards]) == 'JJJJJ':
                return 6
            max_non_jokers = max(((k, v) for k, v in freq.items() if k.value != 'J'), key=lambda x: x[1])
            jokers_to_remove = []
            for key in freq.keys():
                if key.value == 'J':
                    freq[max_non_jokers[0]] += freq[key]
                    jokers_to_remove.append(key)
            freq = {key: value for key, value in freq.items() if key not in jokers_to_remove}
        if len(freq.keys()) == 1:
            return 6
        if len(freq.keys()) == 2:
            return 5 if max(freq.values()) == 4 else 4
        if len(freq.keys()) == 3:
            return 3 if max(freq.values()) == 3 else 2
        if len(freq.keys()) == 4:
            return 1
        return 0

    @staticmethod
    def comparator(a, b):
        if a.get_combination() > b.get_combination():
            return 1
        if a.get_combination() < b.get_combination():
            return -1
        for i in range(len(a.cards)):
            if a.cards[i] == b.cards[i]:
                continue
            if a.cards[i] > b.cards[i]:
                return 1
            return -1


def parse(data, joker_mode):
    decks = []
    for line in data:
        parsed = line.strip().split(" ")
        cards = [Card(char, joker_mode) for char in parsed[0]]
        bid = int(parsed[1])
        decks.append(Hand(cards, bid, joker_mode))
    return decks


def part1(data_arr):
    return solve(data_arr, False)


def part2(data_arr):
    return solve(data_arr, True)


def solve(data_arr, joker_mode):
    decks = parse(data_arr, joker_mode)
    decks = sorted(decks, key=cmp_to_key(Hand.comparator))
    rv = 0
    for i, deck in enumerate(decks):
        rv += deck.bid * (i + 1)
    return rv


if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        data_arr = file.readlines()
        print(part1(data_arr))
        print(part2(data_arr))
