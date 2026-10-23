fn even_numbers(array: &Vec<i32>, number: usize) -> Vec<i32> {
    array.iter()
    .filter(|&x| x%2 == 0)
    .rev()
    .take(number)
    .collect::<Vec<&i32>>()
    .into_iter()
    .rev()
    .map(|x| *x )
    .collect()
}

fn main() {
    println!("{:?}", even_numbers(&vec!(2), 1));
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn sample_tests() {
        assert_eq!(even_numbers(&vec!(1, 2, 3, 4, 5, 6, 7, 8, 9), 3), vec!(4, 6, 8));
        assert_eq!(even_numbers(&vec!(-22, 5, 3, 11, 26, -6, -7, -8, -9, -8, 26), 2), vec!(-8, 26));
        assert_eq!(even_numbers(&vec!(6, -25, 3, 7, 5, 5, 7, -3, 23), 1), vec!(6));
    }
    #[test]
    fn mytest1() {
        assert_eq!(even_numbers(&vec!(2, 4, 6, 8, 10), 3), vec!(6, 8, 10));
    }
    #[test]
    fn mytest2() {
        assert_eq!(even_numbers(&vec!(-2, -4, -6, -8, -10), 2), vec!(-8, -10));
    }
    #[test]
    fn mytest3() {
        assert_eq!(even_numbers(&vec!(1, 3, 5, 7, 9), 2), vec!());
    }
    #[test] 
    fn mytest4() {
        assert_eq!(even_numbers(&vec!(0, 1, 2, 3, 4, 5), 4), vec!(0, 2, 4));
    }
}