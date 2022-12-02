import pathlib
from enum import IntEnum


class PlayMove(IntEnum):
    ROCK = 1
    PAPER = 2
    SCISSORS = 3

    @property
    def win(self):
        return PlayMove((self + 1) % 3 or 1)


TRANSLATION_MAP = {
    'A': PlayMove.ROCK,
    'B': PlayMove.PAPER,
    'C': PlayMove.SCISSORS,

    'X': PlayMove.ROCK,
    'Y': PlayMove.PAPER,
    'Z': PlayMove.SCISSORS,
}


def get_part_one_score(moves):
    return sum(
        (
            my_move
            + (enemy_move.win == my_move) * 6
            + (my_move == enemy_move) * 3
        ) for enemy_move, my_move in moves
    )


def main():
    content = pathlib.Path('./input.txt').read_text()

    moves = [
        map(TRANSLATION_MAP.get, line.split())
        for line in content.splitlines()
    ]

    print("Part 1:", get_part_one_score(moves))


if __name__ == '__main__':
    main()
