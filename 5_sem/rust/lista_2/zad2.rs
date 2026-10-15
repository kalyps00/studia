fn number(bus_stops:&[(i32,i32)]) -> i32 {
    /* let mut people = 0;
    for (on, off) in bus_stops{
        people += on - off;
    }
    people */
    bus_stops.iter().fold(0, |acc, &(on, off)| acc + on - off)
}

fn main() {
    println!("{}", number(&[(10,0),(3,5),(5,8)]));
}
#[cfg(test)]
mod tests {
    use super::number;
    #[test]
    fn returns_expected() {
    assert_eq!(number(&[(10,0),(3,5),(5,8)]), 5);
    assert_eq!(number(&[(3,0),(9,1),(4,10),(12,2),(6,1),(7,10)]), 17);
    assert_eq!(number(&[(3,0),(9,1),(4,8),(12,2),(6,1),(7,8)]), 21);
    }
    #[test]
    fn my_tests1(){
        assert_eq!(number(&[(3,0),(9,1),(4,10),(12,2),(6,1),(7,10)]), 17);
    }
    #[test]
    fn my_tests2() {
        assert_eq!(number(&[]), 0);
    }
    #[test]
    fn my_tests3() {
        assert_eq!(number(&[(0,0),(0,0),(0,0)]), 0);
    }
    #[test]
    fn my_tests4() {
        assert_eq!(number(&[(1,0),(2,0),(3,0)]), 6);
    }
    #[test]
    fn my_tests5() {
        assert_eq!(number(&[(0,1),(0,2),(0,3)]), -6);
    }
}   