fn sum_two_smallest_numbers(numbers: &[u32]) -> u32 {
    let mut min1= u32::MAX;
    let mut min2= u32::MAX;
    for &n in numbers {
        min2 = min2.min(min1.max(n));
        min1 = min1.min(n);
    }
return min1 + min2;
    
}

fn main(){
    print!("{}", sum_two_smallest_numbers(&[2, 3]))
}
#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn sample_tests() {
        assert_eq!(sum_two_smallest_numbers(&[5, 8, 12, 19, 22]),  13, "Incorrect result for [5, 8, 12, 19, 22]");
        assert_eq!(sum_two_smallest_numbers(&[15, 28, 4, 2, 43]), 6, "Incorrect result for [15, 28, 4, 2, 43]");
        assert_eq!(sum_two_smallest_numbers(&[23, 71, 33, 82, 1]), 24, "Incorrect result for [23, 71, 33, 82, 1]");
        assert_eq!(sum_two_smallest_numbers(&[52, 76, 14, 12, 4]), 16, "Incorrect result for [52, 76, 14, 12, 4]");
        assert_eq!(sum_two_smallest_numbers(&[1, 1, 5, 5]),  2, "Incorrect result for [1, 1, 5, 5]");
    }
    #[test]
    fn my_tests1(){
        assert_eq!(sum_two_smallest_numbers(&[2, 3]), 5);
    }
    #[test]
    fn my_tests2() {
        assert_eq!(sum_two_smallest_numbers(&[1, 2, 3, 4, 5]), 3);
    }
    #[test]
    fn my_tests3() {
        assert_eq!(sum_two_smallest_numbers(&[10, 20, 30, 40, 50]), 30);
    }
    #[test]
    fn my_tests4() {    
        assert_eq!(sum_two_smallest_numbers(&[5, 5, 5, 5]), 10);
    }   
}