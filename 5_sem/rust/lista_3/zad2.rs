fn summy(strng: &str) -> i32 {
        strng.split_whitespace()
        .map(|s| {s.parse::<i32>().unwrap()})
        .sum()
}

fn main() {
    println!("{}", summy("1 2 3 4 5"));

}
#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn sample_tests() {
        assert_eq!(summy("1 2 3"), 6);
        assert_eq!(summy("1 2 3 4"), 10);
        assert_eq!(summy("1 2 3 4 5"), 15);
        assert_eq!(summy("10 10"), 20);
        assert_eq!(summy("0 0"), 0);
    }
    #[test]
    fn mytest1() {
        assert_eq!(summy("5 5 5 5"), 20);
    }
    #[test]
    fn mytest2() {
        assert_eq!(summy(""), 0);
    }
    #[test]
    fn mytest3(){
        assert_eq!(summy("-100 100"), 0);
    }
    #[test]
    fn mytest4(){
        assert_eq!(summy("1  2"), 3);
    }
}