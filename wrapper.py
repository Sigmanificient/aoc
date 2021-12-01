from typing import List, Callable


def provide(func: Callable[[List[int]], None]) -> ():
    """
    Decorator to provide the data to the function
        and prints the result.

    Parameters
    ----------
    func : function
        The function to be decorated.

    Returns
    -------
    func : function
        The decorated function.
    """
    def wrapped() -> None:
        with open("../input.data") as f:
            row_data = f.read()

        print(
            func.__name__,
            '->',
            func(list(map(int, row_data.splitlines())))
        )

    return wrapped
