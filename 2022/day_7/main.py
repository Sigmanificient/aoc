import pathlib
from typing import List, Tuple, Optional


class Directory:

    def __init__(self, parent):
        self.parent = parent

        self.sub_dirs = {}
        self.files = {}

    @property
    def root(self):
        if self.parent is None:
            return self
        return self.parent.root

    @property
    def size(self):
        return sum(self.files.values()) + sum(sub.size for sub in self.sub_dirs.values())

    def __repr__(self):
        return f'<[{self.size}]>'


def change_directory(tree: Directory, new_dir: str) -> Directory:
    if new_dir == '..':
        return tree.parent

    if new_dir not in tree.sub_dirs:
        raise ValueError(f'No such directory {new_dir}')

    tree = tree.sub_dirs[new_dir]
    return tree


def list_directory(tree: Directory, lines: List[str], index: int, total: int) -> Tuple[Directory, int]:
    while index < total and not (line := lines[index]).startswith('$'):
        index += 1

        if line.startswith('dir'):
            tree.sub_dirs[line[4:]] = Directory(parent=tree)
            continue

        size, name = line.split(' ')
        tree.files[name] = int(size)
    return tree, index - 1


def parse_file(lines):
    tree = Directory(parent=None)
    tree.sub_dirs["/"] = Directory(parent=tree)

    i = 0
    total = len(lines)

    while i < total:
        if not (line := lines[i]).startswith('$'):
            raise ValueError(f'Must start with a command')

        _, command, *args = line.split(' ')
        if command == 'cd':
            tree = change_directory(tree, args[0])
        elif command == 'ls':
            tree, i = list_directory(tree, lines, i + 1, total)
        else:
            raise ValueError(f'Unknown command {command}')

        i += 1
    return tree.root


def get_all_directories_with_size_below(tree: Directory, size: int, collected: List[str] = None) -> List[Directory]:
    if not collected:
        collected = []

    if tree.size <= size:
        collected.append(tree)

    for sub in tree.sub_dirs.values():
        collected.extend(get_all_directories_with_size_below(sub, size))

    return collected


def get_sum_of_all_directories_with_size_below(tree: Directory, size: int) -> int:
    return sum(d.size for d in get_all_directories_with_size_below(tree, size))


def main():
    content = pathlib.Path('./input.txt').read_text()

    tree = parse_file(content.splitlines())

    print('Part 1:', get_sum_of_all_directories_with_size_below(tree, 100_000))


if __name__ == '__main__':
    main()
