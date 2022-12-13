import functools
import operator
import pathlib
from typing import Final, List, Tuple

BOARD_SIZE: Final[int] = 99


def get_neighbours_tree(board: List[str], x: int, y: int) -> Tuple[str, str, str, str]:
    return (
        board[y][:x][::-1],
        board[y][x + 1:],
        ''.join(line[x] for line in board[:y])[::-1],
        ''.join(line[x] for line in board[y + 1:])
    )


def count_visible(board: List[str]) -> int:
    def is_visible(x, y) -> bool:
        return any(
            board[y][x] > max(trees)
            for trees in get_neighbours_tree(board, x, y)
        )

    return sum(
        is_visible(x, y)
        for x in range(1, BOARD_SIZE - 1)
        for y in range(1, BOARD_SIZE - 1)
    ) + (BOARD_SIZE - 1) * 4


def get_highest_scenic_score(board: List[str]) -> int:
    def scenic_core(x: int, y: int) -> int:
        return functools.reduce(
            operator.mul,
            (
                get_first_non_visible_from(board[y][x], trees)
                for trees in get_neighbours_tree(board, x, y)
            )
        )

    def get_first_non_visible_from(h: str, trees: str) -> int:
        for idx, tree in enumerate(trees, start=1):
            if tree >= h:
                return idx
        return len(trees)

    return max(
        scenic_core(x, y)
        for x in range(BOARD_SIZE)
        for y in range(BOARD_SIZE)
    )


def main():
    content = pathlib.Path('./input.txt').read_text()
    board = [line for line in content.splitlines()]

    print('Part 1:', count_visible(board))
    print('Part 2:', get_highest_scenic_score(board))


if __name__ == '__main__':
    main()
