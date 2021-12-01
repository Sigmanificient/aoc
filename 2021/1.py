from wrapper import provide


@provide
def day_1_part_1(data):
    return sum(x < y for x, y in zip(data, data[1:]))


@provide
def day_1_part_2(data):
    return sum(a < d for a, d in zip(data, data[3:]))


if __name__ == '__main__':
    day_1_part_1()
    day_1_part_2()
