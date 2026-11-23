#![allow(dead_code)]
#![cfg_attr(not(test), no_main)]
fn largest_difference(data: &[i32]) -> usize {
    data.iter()
        .enumerate()
        .flat_map(|(i, &val_i)| {
            data.iter()
                .enumerate()
                .filter(move |&(j, &val_j)| i <= j && val_i <= val_j)
                .map(move |(j, _)| j - i)
        })
        .max()
        .unwrap_or(0)
}
#[cfg(test)]
mod tests {
    use super::largest_difference;

    const ERR_MSG: &str = "\nYour result (left) did not match the expected output (right)";
    
    fn dotest(data: &[i32], expected: usize) {
        assert_eq!(largest_difference(data), expected, "{ERR_MSG} with data = {data:?}")
    }

    #[test]
    fn sample_tests() {
        dotest(&[9, 4, 1, 10, 3, 4, 0, -1, -2], 4);
        dotest(&[3, 2, 1], 0);
        dotest(&[1, 2, 3], 2);
        dotest(&[9, 4, 1, 2, 3, 0, -1, -2], 2);
        dotest(&[9, 4, 1, 2, 3, 4, 0, -1, -2], 4);
        dotest(&[78, 88, 64, 94, 17, 91, 57, 69, 38, 62, 13, 17, 35, 15, 20], 10);
        dotest(&[4, 3, 3, 1, 5, 2], 4);
    }
    #[test]
    fn mytest1() {
        dotest(&[1, 2, 3, 4, 5], 4);
    }
    #[test]
    fn mytest2() {
        dotest(&[5, 4, 3, 2, 1], 0);
    }
    #[test]
    fn mytest3() {
        dotest(&[1, 3, 2, 4, 5], 4);
    }
    #[test]
    fn mytest4() {
        dotest(&[1, 2, 3, 0, 0],2);
    }
}
