from __future__ import annotations

import pathlib
from typing import Literal, cast, Set, Tuple


class Point:

    def __init__(self, x, y):
        self.previous = None
        self.x = x
        self.y = y

    def is_touching(self, other: Point) -> bool:
        return (
            self.x == other.x and self.y == other.y
            or (
                abs(self.x - other.x) < 2
                and abs(self.y - other.y) < 2
            )
        )

    def move(self, x: int, y: int):
        self.previous = Point(self.x, self.y)
        self.x += x
        self.y += y

    def copy(self, other: Point):
        self.previous = Point(self.x, self.y)
        self.x = other.x
        self.y = other.y


class Rope:

    def __init__(self, knots: int):
        if knots < 2:
            raise ValueError('Rope must have at least 2 knots')

        self.knots = [Point(0, 0) for _ in range(knots)]
        self.prints: Set[Tuple[int, int]] = set()

    @property
    def head(self) -> Point:
        return self.knots[0]

    @property
    def tail(self) -> Point:
        return self.knots[-1]

    def move_head(self, direction: Literal['L', 'R', 'U', 'D']):
        dx: int = (direction == 'L') - (direction == 'R')
        dy: int = (direction == 'U') - (direction == 'D')

        self.head.move(dx, dy)
        self.propagate_movement()

        self.prints.add((self.tail.x, self.tail.y))

    def propagate_movement(self):
        for head, tail in zip(self.knots, self.knots[1:]):
            if not tail.is_touching(head):
                tail.copy(head.previous)

    def solve(self, lines) -> int:
        for line in lines:
            move = cast(Literal['L', 'R', 'U', 'D'], line[0])
            value = int(line[1:])

            for i in range(value):
                self.move_head(move)

        return len(self.prints)


def main():
    content = pathlib.Path('./input.txt').read_text()
    lines = content.splitlines()

    rope = Rope(2)
    print("Part 1:", rope.solve(lines))


if __name__ == '__main__':
    main()
