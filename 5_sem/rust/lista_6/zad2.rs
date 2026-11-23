#![allow(dead_code)]
#![cfg_attr(not(test), no_main)]
fn coin_combo(cents: u64) -> [u64; 4] {
    [1, 5, 10, 25]
        .iter()
        .rfold((cents, [0; 4]), |(remaining, mut acc), &coin| {
            acc = [
                if coin == 1 { remaining / coin } else { acc[0] },
                if coin == 5 { remaining / coin } else { acc[1] },
                if coin == 10 { remaining / coin } else { acc[2] },
                if coin == 25 { remaining / coin } else { acc[3] },
            ];
            (remaining % coin, acc)
        })
        .1
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn basic() {
        assert_eq!(coin_combo(1), [1, 0, 0, 0], "takes 1 and returns, 1 penny");

        assert_eq!(coin_combo(2), [2, 0, 0, 0], "takes 2 and returns, 2 penny.");

        assert_eq!(
            coin_combo(5),
            [0, 1, 0, 0],
            "takes 5 and returns, 1 nickel."
        );

        assert_eq!(
            coin_combo(6),
            [1, 1, 0, 0],
            "takes 6 and returns, 1 penny, 1 nickel."
        );

        assert_eq!(
            coin_combo(10),
            [0, 0, 1, 0],
            "takes 10 and returns, 1 dime."
        );

        assert_eq!(
            coin_combo(11),
            [1, 0, 1, 0],
            "takes 11 and returns, 1 dime, 1 penny."
        );

        assert_eq!(
            coin_combo(15),
            [0, 1, 1, 0],
            "takes 15 and returns, 1 dime, 1 nickel."
        );

        assert_eq!(
            coin_combo(17),
            [2, 1, 1, 0],
            "takes 17 and returns, 1 dime, 1 nickel, 2 penny."
        );

        assert_eq!(
            coin_combo(25),
            [0, 0, 0, 1],
            "takes 25 and returns, 1 quarter."
        );

        assert_eq!(
            coin_combo(30),
            [0, 1, 0, 1],
            "takes 30 and returns, 1 quarter, 1 nickel."
        );

        assert_eq!(
            coin_combo(36),
            [1, 0, 1, 1],
            "takes 36 and returns, 1 quarter, 1 dime, 1 penny."
        );

        assert_eq!(
            coin_combo(43),
            [3, 1, 1, 1],
            "takes 43 and returns, 1 quarter, 1 dime, 1 nickel, 3 pennies."
        );
    }
    #[test]
    fn mytest1() {
        assert_eq!(coin_combo(0), [0, 0, 0, 0]);
    }
    #[test]
    fn mytest2() {
        assert_eq!(coin_combo(99), [4, 0, 2, 3]);
    }
    #[test]
    fn mytest3() {
        assert_eq!(coin_combo(100), [0, 0, 0, 4]);
    }
    #[test]
    fn mytest4() {
        assert_eq!(coin_combo(101), [1, 0, 0, 4]);
    }
}
