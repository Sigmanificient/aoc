import os
import pathlib
from typing import Tuple


def _count_larger_sum(first_seq: Tuple[int, ...], offset: int) -> int:
    return sum(x < y for x, y in zip(first_seq, first_seq[offset:]))


def day_1_part_1(data: Tuple[int, ...]) -> int:
    return _count_larger_sum(data, 1)


def day_1_part_2(data: Tuple[int, ...]) -> int:
    return _count_larger_sum(data, 3)


def main():
    content = pathlib.Path('./input.txt').read_text()
    data = tuple(map(int, content.splitlines()))

    print("Part 1:", day_1_part_1(data))
    print("Part 2:", day_1_part_2(data))


if __name__ == '__main__':
    main()
