import pathlib

BOARD_SIZE = 99


def is_visible(board, x, y):
    return any(
        board[y][x] > max(trees)
        for trees in (
            board[y][:x],
            board[y][x + 1:],
            tuple(line[x] for line in board[:y]),
            tuple(line[x] for line in board[y + 1:])
        )
    )


def count_visible(board):
    return sum(
        is_visible(board, x, y)
        for x in range(1, BOARD_SIZE - 1) for y in range(1, BOARD_SIZE - 1)
    ) + (BOARD_SIZE - 1) * 4


def main():
    content = pathlib.Path('./input.txt').read_text()
    board = [line for line in content.splitlines()]

    print('Part 1:', count_visible(board))


if __name__ == '__main__':
    main()
