from __future__ import annotations

from collections import namedtuple
import pathlib

from typing import Final, List, Optional


Point = namedtuple('Point', ('x', 'y'))

ELEVATIONS: Final[str] = "_abcdefghijklmnopqrstuvwxyz_"

def find_on(world: List[str], symbol: str, rep: str) -> Optional[Point]:
    for y, line in enumerate(world):
        if symbol not in line:
            continue

        x: int = line.index(symbol)
        world[y] = line.replace(symbol, rep, 1)
        return Point(x, y)
    return None


def get_possible_neighbors(world: List[str], me: Point) -> List[Point]:
    elevation: str = world[me.y][me.x]

    _e_id: int = ELEVATIONS.index(elevation)
    accept: str = ELEVATIONS[_e_id - 1] + ELEVATIONS[_e_id + 1]

    # Todo: Iter 4 neighbor -> check bound -> check elevation -> yield
    return []



def shortest_path(
    world: List[str],
    me: Point,
    target: Point,
    path: Optional[List[Point]] = None
) -> List[Point]:
    if not path:
        path = [me]

    if not world or (me == target):
        return path

    for neighbor in get_possible_neighbors(world, me):
        return shortest_path(world, me, target, path + [neighbor])

    return path


def main() -> None:
    content: str = pathlib.Path('./input.txt').read_text()
    world_map: List[str] = content.splitlines()

    me: Optional[Point] = find_on(world_map, 'S', rep='a')
    if me is None:
        return None
    target: Optional[Point] = find_on(world_map, 'E', rep='z')
    if target is None:
        return None

    print(me, '->', target)
    print(shortest_path(world_map, me, target))


if __name__ == '__main__':
    main()
