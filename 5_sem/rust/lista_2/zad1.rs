fn get_count(string: &str) -> usize {
  let mut vowels_count: usize = 0;
    for s in string.chars(){
        match s {
            'a' | 'e' | 'i' | 'o' | 'u' => vowels_count += 1,
            _ => (),
        }
    }
  vowels_count
}

fn main() {
    println!("{}", get_count("abracadabra"));
}

#[cfg(test)]
mod tests {
    use super::get_count;

    #[test]
    fn my_tests() {
      assert_eq!(get_count("abracadabra"), 5);
    }
    #[test]
    fn my_tests1(){
        assert_eq!(get_count("hello world"), 3);
    }
    #[test]
    fn my_tests2() {
        assert_eq!(get_count(""), 0);
    }

    #[test]
    fn my_tests3() {
        assert_eq!(get_count("aeiou"), 5);
    }
    #[test]
    fn my_tests4() {
        assert_eq!(get_count("bcdfghjklmnpqrstvwxyz"), 0);
    }
}