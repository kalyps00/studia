fn longest(a1: &str, a2: &str) -> String {
    let mut chars: Vec<char> =  format!("{}{}", a1, a2).chars().collect();
    chars.sort();
    chars.dedup();
    chars.into_iter().collect()
}       

fn main(){
    println!("{}", longest("x", "xy"));
}

#[cfg(test)]
    mod tests {
    use super::*;
   
    fn testing(s1: &str, s2: &str, exp: &str) -> () {
        println!("s1:{:?} s2:{:?}", s1, s2);
        println!("{:?} {:?}", longest(s1, s2), exp);
        println!("{}", longest(s1, s2) == exp);
        assert_eq!(&longest(s1, s2), exp)
    }
    #[test]
    fn mytest1() {
        testing("x", "xy", "xy");
    }
    #[test]
    fn mytest2(){
        testing("x", "x", "x");
    }
    #[test]
    fn mytest3(){
        testing("abc", "cde", "abcde");
    }
    #[test]
    fn mytest4(){
        testing("a", "b", "ab");
    }
}