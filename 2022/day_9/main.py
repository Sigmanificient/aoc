from __future__ import annotations

import pathlib
from dataclasses import dataclass
from typing import Literal, cast, Set, Tuple


@dataclass
class Point:
    x: int
    y: int

    def is_touching(self, other: Point) -> bool:
        return (
            self.x == other.x and self.y == other.y
            or (
                abs(self.x - other.x) < 2
                and abs(self.y - other.y) < 2
            )
        )

    def move(self, x: int, y: int):
        self.x += x
        self.y += y


class Rope:

    def __init__(self):
        self.head = Point(0, 0)
        self.tail = Point(0, 0)

        self.prints: Set[Tuple[int, int]] = set()

    def move_head(self, direction: Literal['L', 'R', 'U', 'D']):
        dx: int = (direction == 'L') - (direction == 'R')
        dy: int = (direction == 'U') - (direction == 'D')

        self.head.move(dx, dy)
        if not self.tail.is_touching(self.head):
            self.tail = Point(self.head.x - dx, self.head.y - dy)

        self.prints.add((self.tail.x, self.tail.y))


def main():
    content = pathlib.Path('./input.txt').read_text()
    lines = content.splitlines()

    rope = Rope()

    for line in lines:
        move = cast(Literal['L', 'R', 'U', 'D'], line[0])
        value = int(line[1:])

        for i in range(value):
            rope.move_head(move)

    print(len(rope.prints))


if __name__ == '__main__':
    main()
