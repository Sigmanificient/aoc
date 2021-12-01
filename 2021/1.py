from wrapper import provide


def _count_larger_sum(first_seq, offset):
    return sum(
        x < y
        for x, y in zip(first_seq, offset)
    )


@provide
def day_1_part_1(data):
    return _count_larger_sum(data, 1)


@provide
def day_1_part_2(data):
    return _count_larger_sum(data, 3)


if __name__ == '__main__':
    day_1_part_1()
    day_1_part_2()
