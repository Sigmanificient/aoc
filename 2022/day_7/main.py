from __future__ import annotations

import pathlib
from typing import List, Callable, Optional, Dict

DISK_SIZE = 70_000_000
REQUIRED_SPACE = 30_000_000


class FileTree:

    def __init__(self, parent: Optional[FileTree] = None):
        self.parent = parent
        self.sub_dirs: Dict[str, FileTree] = {}
        self.files: Dict[str, int] = {}

    @property
    def root(self) -> FileTree:
        return self if self.parent is None else self.parent.root

    @property
    def size(self) -> int:
        return sum(self.files.values()) + sum(sub.size for sub in self.sub_dirs.values())

    def move_to(self, target: str) -> FileTree:
        if target == '..':
            return self.parent or self

        if target not in self.sub_dirs:
            raise ValueError(f'No such directory: {target}')

        return self.sub_dirs[target]

    def from_lines(self, lines: List[str], index: int, total: int) -> int:
        while index < total and not (line := lines[index]).startswith('$'):
            index += 1

            if line.startswith('dir'):
                self.sub_dirs[line[4:]] = FileTree(parent=self)
                continue

            size, name = line.split(' ')
            self.files[name] = int(size)
        return index - 1

    def filter_children(self, func: Callable[[FileTree], bool]) -> List[FileTree]:
        collected = []

        if func(self):
            collected.append(self)

        for sub in self.sub_dirs.values():
            collected.extend(sub.filter_children(func))

        return collected


def parse_file(lines):
    tree = FileTree()
    tree.sub_dirs["/"] = FileTree(parent=tree)

    total = len(lines)
    i = 0

    while i < total:
        if not (line := lines[i]).startswith('$'):
            raise ValueError(f'Must start with a command')

        _, command, *args = line.split(' ')
        if command == 'cd':
            tree = tree.move_to(args[0])
        elif command == 'ls':
            i = tree.from_lines(lines, i + 1, total)
        else:
            raise ValueError(f'Unknown command {command}')

        i += 1
    return tree.root


def get_sum_of_sizes_below(tree: FileTree, size) -> int:
    dirs = tree.filter_children(func=lambda f: f.size <= size)
    return sum(d.size for d in dirs)


def get_min_size_above(tree: FileTree, needed) -> int:
    dirs = tree.filter_children(func=lambda f: f.size > needed)
    return min(dirs, key=lambda d: d.size).size


def main():
    content = pathlib.Path('./input.txt').read_text()

    tree = parse_file(content.splitlines())
    print("Part 1:", get_sum_of_sizes_below(tree, 100_000))

    needed = REQUIRED_SPACE - (DISK_SIZE - tree.root.size)
    print("Part 2:", get_min_size_above(tree, needed))


if __name__ == '__main__':
    main()
