import pathlib
import re
from typing import cast, List, Tuple

MOVE_REGEX = re.compile(r'^move (\d+) from (\d+) to (\d+)$')


def parse_initial_state(state_lines):
    stack_ids = list(map(int, state_lines.pop().split()))
    stacks = {i: [] for i in sorted(stack_ids)}

    def split_x(chunk_size):
        return [line[i:i + chunk_size] for i in range(0, len(line), chunk_size + 1)]

    for line in reversed(state_lines):
        for create, stack in zip(split_x(3), stack_ids):
            if create == '   ':
                continue

            stacks[stack].append(create)
    return stacks


def parse_moves(lines) -> List[Tuple[int, int, int]]:
    return cast(
        List[Tuple[int, int, int]],
        [
            tuple(map(int, re.match(MOVE_REGEX, line).groups()))
            for line in lines
        ]
    )


def parse(lines):
    split_idx = lines.index('')
    return (
        parse_initial_state(lines[:split_idx]),
        parse_moves(lines[split_idx + 1:])
    )


def solve(state, moves):
    for n, from_, to in moves:
        for i in range(n):
            state[to].append(state[from_].pop())
    return state


def collect_output(state):
    return ''.join(g[-1][1] for g in state.values())


def main():
    content = pathlib.Path('./input.txt').read_text()
    initial_state, moves = parse(content.splitlines())

    print("Part 1:", collect_output(solve(initial_state, moves)))


if __name__ == '__main__':
    main()
