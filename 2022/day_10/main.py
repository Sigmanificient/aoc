import pathlib


def main():
    content = pathlib.Path('./input.txt').read_text()
    lines = content.splitlines()

    cycles = [1]
    for line in lines:
        if line == 'noop':
            cycles.append(cycles[-1])
            continue

        n = int(line.split()[1])
        cycles.append(cycles[-1])
        cycles.append(cycles[-1] + n)

    t = 0
    for cycle_n in (20, 60, 100, 140, 180, 220):
        t += cycles[cycle_n - 1] * cycle_n

    print(t)


if __name__ == '__main__':
    main()
