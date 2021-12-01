from wrapper import provide


@provide
def day_1_part_1(data):
    return sum(x < y for x, y in zip(data, data[1:]))


if __name__ == '__main__':
    day_1_part_1()
