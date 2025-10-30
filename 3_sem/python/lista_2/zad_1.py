def dhondt(votes_list: list[tuple[str, int]], space):
    votes_sum = sum(i for _, i in votes_list)

    ilorazy = []
    for name, num in votes_list:
        if num < votes_sum * 0.05:
            continue
        for i in range(1, space + 1):
            ilorazy.append((num // i, num, name))
    ilorazy.sort(reverse=True)
    mandate = {name: 0 for name, _ in votes_list}
    for i in range(space):
        name = ilorazy[i][2]
        mandate[name] += 1
    return mandate


if __name__ == "__main__":
    print(dhondt([("A", 720), ("B", 300), ("C", 480)], 8))
