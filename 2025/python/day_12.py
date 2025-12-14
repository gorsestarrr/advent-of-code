import re
from typing import List


def read_input(path: str) -> tuple[list[str], list[list[int]]]:
    with open(path, "r", encoding="utf-8") as file:
        raw_data = file.read().strip()

    *shapes, regions_block = raw_data.split("\n\n")
    regions = parse_regions(regions_block)

    return shapes, regions


def parse_regions(block: str) -> List[List[int]]:
    return [
        list(map(int, re.findall(r"\d+", line)))
        for line in block.splitlines()
    ]

def bad_input() -> None:
    print("Bad Input")

def region_score(
    width: int,
    height: int,
    counts: List[int],
    shapes: List[str]
) -> int:
    max_capacity = (width // 3) * (height // 3)
    total_items = sum(counts)

    if max_capacity >= total_items:
        return 1

    weighted_sum = sum(
        count * shape.count("#")
        for count, shape in zip(counts, shapes)
    )

    if weighted_sum > width * height:
        return 0

    bad_input()
    return 0


def solve(path: str) -> int:
    shapes, regions = read_input(path)

    return sum(
        region_score(w, h, nums, shapes)
        for w, h, *nums in regions
    )


if __name__ == "__main__":
    result = solve("input.txt")
    print("Part 1:", result)
