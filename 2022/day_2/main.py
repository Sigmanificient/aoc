from __future__ import annotations

import pathlib
from enum import IntEnum
from typing import Tuple, List, Dict

WIN_SCORE = 6
DRAW_SCORE = 3


class PlayMove(IntEnum):
    ROCK = 1
    PAPER = 2
    SCISSORS = 3

    @property
    def win(self) -> PlayMove:
        return PlayMove((self + 1) % 4 or 1)

    @property
    def lose(self) -> PlayMove:
        return PlayMove((self - 1) or 3)


class Target(IntEnum):
    LOSE = 1
    DRAW = 2
    WIN = 3

    def score_from_enemy(self, enemy: PlayMove) -> int:
        if self == Target.LOSE:
            return enemy.lose

        return (
            enemy.win + WIN_SCORE
            if self == Target.WIN
            else enemy + DRAW_SCORE
        )


TRANSLATION_MAP: Dict[str, PlayMove] = {
    'A': PlayMove.ROCK,
    'B': PlayMove.PAPER,
    'C': PlayMove.SCISSORS,

    'X': PlayMove.ROCK,
    'Y': PlayMove.PAPER,
    'Z': PlayMove.SCISSORS,
}


def get_part_one_score(moves: List[Tuple[PlayMove, ...]]) -> int:
    return sum(
        (
            my_move
            + (enemy_move.win == my_move) * WIN_SCORE
            + (my_move == enemy_move) * DRAW_SCORE
        ) for enemy_move, my_move in moves
    )


def get_part_two_score(moves: List[Tuple[PlayMove, ...]]) -> int:
    return sum(
        Target(target).score_from_enemy(enemy_move)
        for enemy_move, target in moves
    )


def main():
    content = pathlib.Path('./input.txt').read_text()

    moves: List[Tuple[PlayMove, ...]] = [
        tuple(map(TRANSLATION_MAP.get, line.split()))
        for line in content.splitlines()
    ]

    print("Part 1:", get_part_one_score(moves))
    print("Part 2:", get_part_two_score(moves))


if __name__ == '__main__':
    main()
