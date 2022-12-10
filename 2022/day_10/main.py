import pathlib


def get_cycles_values(lines):
    cycles = [1]
    for line in lines:
        if line == 'noop':
            cycles.append(cycles[-1])
            continue

        n = int(line.split()[1])
        cycles.append(cycles[-1])
        cycles.append(cycles[-1] + n)

    cycles.pop()
    return cycles


def get_target_registers(cycles):
    return sum(
        cycles[cycle_n - 1] * cycle_n
        for cycle_n in (20, 60, 100, 140, 180, 220)
    )


def show_crt(cycles):
    def chunk(lst, size):
        return [lst[i:i + size] for i in range(0, len(lst), size)]

    return '\n' + '\n'.join(
        ''.join(
            ('##' if abs(idx - x) < 2 else '  ')
            for idx, x in enumerate(ctr_line)
        ) for ctr_line in chunk(cycles, 40)
    )


def main():
    content = pathlib.Path('./input.txt').read_text()
    cycles = get_cycles_values(content.splitlines())

    print('Part 1:', get_target_registers(cycles))
    print('Part 2:', show_crt(cycles))


if __name__ == '__main__':
    main()
