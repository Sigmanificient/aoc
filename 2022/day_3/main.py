import pathlib


def get_priority(items):
    item = set.intersection(*map(set, items)).pop()
    i = ord(item)  # magic done here :3
    return (i | 32) - 70 - (26 * (i & 32) >> 5)


def get_compartments_priorities_sum(rucksacks):
    def cut_line(line):
        half = len(line) // 2
        return map(set, (line[:half], line[half:]))

    return sum(map(get_priority, map(cut_line, rucksacks)))


def get_badge_priorities_sum(rucksacks):
    def chunk(lst, size):
        return [lst[i:i + size] for i in range(0, len(lst), size)]

    return sum(map(get_priority, chunk(rucksacks, 3)))


def main():
    content = pathlib.Path('./input.txt').read_text()
    lines = content.splitlines()

    print("Part 1:", get_compartments_priorities_sum(lines))
    print("Part 2:", get_badge_priorities_sum(lines))


if __name__ == '__main__':
    main()
