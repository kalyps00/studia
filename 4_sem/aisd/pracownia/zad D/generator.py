import random
import sys
import argparse


def generate_test(args):
    # Determine the number of test cases T
    T = random.randint(1, args.max_t) if args.t is None else args.t

    print(T)
    for _ in range(T):
        # Determine the length of the tram
        n = random.randint(1, args.max_n) if args.n is None else args.n
        print(n)

        # Decide on the type of test case
        mode = random.choices(
            ["random", "mostly_increasing", "decreasing", "flat"],
            weights=[60, 20, 10, 10],
            k=1,
        )[0]

        max_val = args.max_val

        if mode == "random":
            arr = [random.randint(1, max_val) for _ in range(n)]

        elif mode == "mostly_increasing":
            # Mostly increasing sequence, good for testing the removal of a middle bad segment
            arr = []
            cur = random.randint(1, max_val // 100)
            for _ in range(n):
                if random.random() < 0.1:  # 10% chance to break the increasing sequence
                    cur = random.randint(1, max_val // 2)
                arr.append(cur)
                # Increment by a random step
                cur += random.randint(1, max_val // n + 1)
                if cur > max_val:
                    cur = max_val

        elif mode == "decreasing":
            # Strictly decreasing
            arr = sorted([random.randint(1, max_val) for _ in range(n)], reverse=True)

        elif mode == "flat":
            # All elements equal (increasing sequence length is 1)
            v = random.randint(1, max_val)
            arr = [v] * n

        # Join array into space-separated string
        print(" ".join(map(str, arr)))


def main():
    parser = argparse.ArgumentParser(
        description="Generator testów do zadania D. Tramwaje"
    )
    parser.add_argument(
        "-t",
        type=int,
        default=None,
        help="Dokładna liczba testów (T). Domyślnie losowa (1-10).",
    )
    parser.add_argument(
        "--max-t", type=int, default=10, help="Maksymalna liczba testów (domyślnie 10)."
    )
    parser.add_argument(
        "-n", type=int, default=None, help="Dokładna długość każdego tramwaju (n)."
    )
    parser.add_argument(
        "--max-n",
        type=int,
        default=1000,
        help="Maksymalna długość tramwaju (domyślnie 1000, limit z zadania to 2*10^6).",
    )
    parser.add_argument(
        "--max-val",
        type=int,
        default=10**9,
        help="Maksymalna klasa wagonu (domyślnie 10^9).",
    )

    args = parser.parse_args()
    generate_test(args)


if __name__ == "__main__":
    main()
