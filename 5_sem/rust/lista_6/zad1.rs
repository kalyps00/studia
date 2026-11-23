#![allow(dead_code)]
#![cfg_attr(not(test), no_main)]
fn capitalize(s: &str) -> Vec<String> {
    (0..2)
        .map(|p| {
            s.chars()
                .enumerate()
                .map(|(i, c)| {
                    if i % 2 == p {
                        c.to_uppercase().to_string()
                    } else {
                        c.to_string()
                    }
                })
                .collect()
        })
        .collect()
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn example_tests() {
        assert_eq!(capitalize("abcdef"),["AbCdEf", "aBcDeF"]);
        assert_eq!(capitalize("codewars"),["CoDeWaRs", "cOdEwArS"]);
        assert_eq!(capitalize("abracadabra"),["AbRaCaDaBrA", "aBrAcAdAbRa"]);
        assert_eq!(capitalize("codewarriors"),["CoDeWaRrIoRs", "cOdEwArRiOrS"]);
    }
    #[test]
    fn mytest1(){
        assert_eq!(capitalize(""),["", ""]);
    }
    #[test]
    fn mytest2(){
        assert_eq!(capitalize("a"),["A", "a"]);
    }
    #[test]
    fn mytest3(){
        assert_eq!(capitalize("ab"),["Ab", "aB"]);
    }
    #[test]
    fn mytest4(){
        assert_eq!(capitalize("abc"),["AbC", "aBc"]);
    }
}
