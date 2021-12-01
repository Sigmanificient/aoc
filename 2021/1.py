from typing import List

from wrapper import provide


def _count_larger_sum(
    first_seq: List[int], offset: int
) -> int:
    """
    Parameters
    ----------
    first_seq : List[int]
        The first sequence of numbers.
    offset : int
        The offset to apply to the first sequence.

    Returns
    -------
    int
        The number of elements in the first sequence that are larger than their
        offset-th element.
    """
    return sum(
        x < y
        for x, y in zip(
            first_seq, first_seq[offset:]
        )
    )


@provide
def day_1_part_1(data: List[int]) -> int:
    """
    Parameters
    ----------
    data : List[int]
        The input data provided by Aoc.

    Returns
    -------
    int
        The solution to part 1.
    """
    return _count_larger_sum(data, 1)


@provide
def day_1_part_2(data: List[int]) -> int:
    """
    Parameters
    ----------
    data : List[int]
        The input data provided by Aoc.

    Returns
    -------
    int
        The solution to part 2.
    """
    # Since we are comparing 2 sliding windows, a + b + c > b + c + d
    # is the equivalent of doing a > c, so we can just just adjust the
    # offset to be the length of the sequence.
    return _count_larger_sum(data, 3)


if __name__ == '__main__':
    day_1_part_1()
    day_1_part_2()
