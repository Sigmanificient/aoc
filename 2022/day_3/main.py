import pathlib


def get_letter_index(char: str) -> int:
    i = ord(char) # magic done here :3
    return (i | 32) - 70 - (26 * (i & 32) >> 5)


def main():
    content = pathlib.Path('./input.txt').read_text()
    total = 0

    for line in content.splitlines():
        half = len(line) // 2
        left, right = map(set, (line[:half], line[half:]))
        total += get_letter_index(left.intersection(right).pop())

    print("Part 1:", total)


if __name__ == '__main__':
    main()
