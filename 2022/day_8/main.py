import functools
import operator
import pathlib

BOARD_SIZE = 99


def is_visible(board, x, y):
    return any(
        board[y][x] > max(trees)
        for trees in get_neighbours_tree(board, x, y)
    )


def count_visible(board):
    return sum(
        is_visible(board, x, y)
        for x in range(1, BOARD_SIZE - 1)
        for y in range(1, BOARD_SIZE - 1)
    ) + (BOARD_SIZE - 1) * 4


def get_neighbours_tree(board, x, y):
    return (
        board[y][:x][::-1],
        board[y][x + 1:],
        tuple(line[x] for line in board[:y])[::-1],
        tuple(line[x] for line in board[y + 1:])
    )


def get_first_non_visible_from(h, trees):
    for idx, tree in enumerate(trees, start=1):
        if tree >= h:
            return idx
    return len(trees)


def scenic_core(board, x, y):
    return functools.reduce(
        operator.mul,
        (
            get_first_non_visible_from(board[y][x], trees)
            for trees in get_neighbours_tree(board, x, y)
        )
    )


def get_highest_scenic_score(board):
    return max(
        scenic_core(board, x, y)
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
