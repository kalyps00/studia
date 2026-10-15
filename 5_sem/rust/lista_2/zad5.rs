fn count_bits(n: i64) -> u32 {
    //return n.count_ones();
    let mut count = 0;
    let mut num = n;
    while num > 0 {
        count += (num & 1) as u32;
        num >>= 1;
    }
    return count;
}

fn main() {
    println!("{}", count_bits(1));
}
#[cfg(test)]
mod tests {
    use super::*;

    fn do_test(n: i64, expected: u32) {
        let actual = count_bits(n);
        assert_eq!(actual, expected,
            "expected {} but got {} for n = {}",
            expected, actual, n
        );
    }

    #[test]
    fn sample_tests() {
        do_test(0, 0);
        do_test(4, 1);
        do_test(7, 3);
        do_test(77231418, 14);
        do_test(12525589, 11);
        do_test(31, 5);
        do_test(417862, 7);
        do_test(89, 4);
        do_test(674259, 10);
        do_test(i64::MAX, 63)
    }
    #[test]
    fn mytest1(){
        do_test(5, 2);

    }
    #[test]
    fn mytest2() {
        do_test(10, 2);
    }
    #[test]
    fn mytest3() {
        do_test(15, 4);
    }
    #[test]
    fn mytest4() {
        do_test(0, 0);
    }
}