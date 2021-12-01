def provide(func):
    def wrapped():
        with open("../input.data") as f:
            row_data = f.read()

        print(
            func.__name__,
            '->',
            func(list(map(int, row_data.splitlines())))
        )

    return wrapped
