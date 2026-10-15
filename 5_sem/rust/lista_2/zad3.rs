fn printer_error(s: &str) -> String {
    let erors = s.chars().filter(|&c| c < 'a' || c > 'm').count();
    return format!("{}/{}", erors, s.len());
}
fn main(){
    print!("{}", printer_error("a"));
}
#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn should_pass_all_the_tests_provided() {
        assert_eq!(&printer_error("aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "3/56");
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "6/60");
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyzuuuuu"), "11/65");
    }
    #[test]
    fn my_tests1(){
        assert_eq!(&printer_error("a"), "0/1");
    }
    #[test]
    fn my_tests2() {
        assert_eq!(&printer_error("z"), "1/1");
    }
    #[test]
    fn my_tests3() {
        assert_eq!(&printer_error("abcdefghijklm"), "0/13");
    }
    #[test]
    fn my_tests4() {
        assert_eq!(&printer_error("nopqrstuvwxyz"), "13/13");
    }
}