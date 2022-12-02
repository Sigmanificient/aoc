import pathlib
from collections import defaultdict


def main():
    content = pathlib.Path('./input.txt').read_text()

    elves = defaultdict(int)
    idx = 0

    for line in content.split('\n'):
        if not line:
            idx += 1
        else:
            elves[idx] += int(line)

    print('Part 1:', max(elves.values()))


if __name__ == '__main__':
    main()
