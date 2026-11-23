#![allow(dead_code)]
#![cfg_attr(not(test), no_main)]

use std::collections::HashSet;

pub fn execute(code: &str) -> String {
    let mut chars = code.chars().peekable();
    let (mut pos, mut dir) = ((0i32, 0i32), (1i32, 0i32));
    let mut visited = HashSet::from([pos]);

    while let Some(cmd) = chars.next() {
        let count = std::iter::from_fn(|| chars.next_if(char::is_ascii_digit))
            .collect::<String>()
            .parse::<usize>()
            .unwrap_or(1);

        match cmd {
            'L' => (0..count % 4).for_each(|_| dir = (dir.1, -dir.0)),
            'R' => (0..count % 4).for_each(|_| dir = (-dir.1, dir.0)),
            'F' => (0..count).for_each(|_| {
                pos = (pos.0 + dir.0, pos.1 + dir.1);
                visited.insert(pos);
            }),
            _ => {}
        }
    }

    let (min_x, max_x) = (
        visited.iter().map(|&(x, _)| x).min().unwrap(),
        visited.iter().map(|&(x, _)| x).max().unwrap(),
    );
    let (min_y, max_y) = (
        visited.iter().map(|&(_, y)| y).min().unwrap(),
        visited.iter().map(|&(_, y)| y).max().unwrap(),
    );

    (min_y..=max_y)
        .map(|y| {
            (min_x..=max_x)
                .map(|x| if visited.contains(&(x, y)) { '*' } else { ' ' })
                .collect::<String>()
        })
        .collect::<Vec<_>>()
        .join("\r\n")
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_empty_and_zero_steps() {
        expect_equal!(execute(""), "*");
        expect_equal!(execute("F0"), "*");
        expect_equal!(execute("L5R10"), "*");
    }

    #[test]
    fn test_straight_lines_and_multidigit() {
        expect_equal!(execute("F10"), "***********");
        expect_equal!(execute("LF3"), "*\r\n*\r\n*\r\n*");
    }

    #[test]
    fn test_square_loop() {
        expect_equal!(
            execute("F5LF5LF5LF5L"),
            "******\r\n*    *\r\n*    *\r\n*    *\r\n*    *\r\n******"
        );
    }

    #[test]
    fn test_shorthand_and_negative_coords() {
        expect_equal!(
            execute("LF5RF3RF3RF7"),
            "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   "
        );
    }

    #[test]
    fn test_large_rotations_and_backtracking() {
      
        expect_equal!(execute("R4F2L2F2"), "***");
    }
}