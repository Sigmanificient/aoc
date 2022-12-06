from __future__ import annotations

import pathlib
from typing import List, Tuple, cast


class LinearRange:

    def __init__(self, start, stop):
        self.start = start
        self.stop = stop

    def is_subset_of(self, other: LinearRange) -> bool:
        return self.start <= other.start and self.stop >= other.stop

    def is_overlapping(self, other: LinearRange) -> bool:
        return (
            self.start <= other.start <= self.stop
            or self.start <= other.stop <= self.stop
            or other.start <= self.start <= other.stop
        )

    @classmethod
    def from_string(cls, string: str) -> LinearRange:
        start, stop = map(int, string.split('-'))
        return cls(start, stop)

    def __repr__(self):
        return f'<{self.start} -> {self.stop}>'


def retrieve_groups(lines: List[str]) -> List[Tuple[LinearRange, LinearRange]]:
    return cast(
        List[Tuple[LinearRange, LinearRange]],
        [
            tuple(map(LinearRange.from_string, line.split(',')))
            for line in lines if line.count(',') == 1
        ]
    )


def count_checked_group(group, func):
    return sum(func(left, right) or func(right, left) for left, right in group)


def main():
    content = pathlib.Path('./input.txt').read_text()
    groups = retrieve_groups(content.splitlines())

    print("Part 1:", count_checked_group(groups, LinearRange.is_subset_of))
    print("Part 2:", count_checked_group(groups, LinearRange.is_overlapping))


if __name__ == '__main__':
    main()
