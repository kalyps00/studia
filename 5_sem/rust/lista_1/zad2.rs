fn count_red_beads(n: u32) -> u32 {
    if n < 2 {
        return 0;
    }
    else {
        return (n - 1) * 2;
    }
}

fn main() {
    println!("{}", count_red_beads(5));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn no_beads() {
        assert_eq!(count_red_beads(0), 0);
    }

    #[test]
    fn one_blue_bead() {
        assert_eq!(count_red_beads(1), 0);
    }

    #[test]
    fn two_blue_beads() {
        assert_eq!(count_red_beads(2), 2);
    }

    #[test]
    fn three_blue_beads() {
        assert_eq!(count_red_beads(3), 4);
    }

    #[test]
    fn five_blue_beads() {
        assert_eq!(count_red_beads(5), 8);
    }
}