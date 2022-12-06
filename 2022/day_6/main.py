import pathlib


def get_first_non_repeating(sequence: str, buffer_size: int) -> int:
    buf = [''] * buffer_size
    idx = 0
    while len(set(x for x in buf if x)) != buffer_size:
        buf.pop(0)
        buf.append(sequence[idx])
        idx += 1
    return idx


def main():
    content = pathlib.Path('./input.txt').read_text()
    print('Part 1:', get_first_non_repeating(content, 4))
    print('Part 2:', get_first_non_repeating(content, 14))


if __name__ == '__main__':
    main()
