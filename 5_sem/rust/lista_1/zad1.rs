fn string_to_number(s: &str) -> i32 {
    s.parse::<i32>().unwrap()
}
fn main(){
    println!("{}", string_to_number("1234"));
}

#[cfg(test)]
mod tests {
    use super::string_to_number;

    #[test]
    fn converts_positive_number() {
        assert_eq!(string_to_number("1234"), 1234);
    }

    #[test]
    fn converts_small_number() {
        assert_eq!(string_to_number("5"), 5);
    }

    #[test]
    fn converts_zero() {
        assert_eq!(string_to_number("0"), 0);
    }

    #[test]
    fn converts_negative_number() {
        assert_eq!(string_to_number("-7"), -7);
    }

    #[test]
    fn converts_number_with_leading_minus() {
        assert_eq!(string_to_number("-605"), -605);
    }
}