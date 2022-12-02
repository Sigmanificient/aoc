import pathlib
from typing import List


def get_group_scores(data: List[str]) -> List[int]:
    elves = [0]

    for line in data:
        if line:
            elves[-1] += int(line)
        else:
            elves.append(0)

    return sorted(elves)


def main():
    content = pathlib.Path('./input.txt').read_text()
    elves = get_group_scores(content.splitlines())

    print('Part 1:', elves[-1])
    print('Part 2:', sum(elves[-3:]))


if __name__ == '__main__':
    main()
