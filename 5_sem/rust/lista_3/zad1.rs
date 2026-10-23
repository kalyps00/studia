fn open_or_senior(data: Vec<(i32, i32)>) -> Vec<String> {
   /*  let mut result: Vec<String> = Vec::new();
    for (age, handicap) in data {
        if age>=55 && handicap>7 {
            result.push("Senior".to_string());
        } else {
            result.push("Open".to_string());
        }
    }
    result */
    data.iter().map(|(age, handicap)| {
        if *age >= 55 && *handicap > 7 {
            "Senior".to_string()
        } else {
            "Open".to_string()
        }
    }).collect()
}

fn main(){
    print!("{:?}", open_or_senior(vec![(45, 12)]));
}

// See https://doc.rust-lang.org/stable/rust-by-example/testing/unit_testing.html
#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn returns_expected() {
        assert_eq!(open_or_senior(vec![(45, 12), (55,21), (19, -2), (104, 20)]), vec!["Open", "Senior", "Open", "Senior"]);
        assert_eq!(open_or_senior(vec![(3, 12), (55,1), (91, -2), (54, 23)]), vec!["Open", "Open", "Open", "Open"]);
    }
    #[test]
    fn mytest1(){
        assert_eq!(open_or_senior(vec![(55, 8)]), vec!["Senior"]);
    }
    #[test]
    fn mytest2() {
        assert_eq!(open_or_senior(vec![(54, 8)]), vec!["Open"]);
    }
    #[test]
    fn mytest3() {
        assert_eq!(open_or_senior(vec![(55, 7)]), vec!["Open"]);
    }
    #[test]
    fn mytest4() {
        assert_eq!(open_or_senior(vec![(60, 10), (50, 5), (55, 8)]), vec!["Senior", "Open", "Senior"]);
    }
}