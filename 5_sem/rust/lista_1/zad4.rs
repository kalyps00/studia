fn dna_strand(dna: &str) -> String {
    let mut result = String::new();
    for c in dna.chars() {
        match c {
            'A' => result.push('T'),
            'T' => result.push('A'),
            'C' => result.push('G'),
            'G' => result.push('C'),
            _ => panic!("bład"),
        }
    }
    result
}


fn main(){
    println!("{}", dna_strand("AAAA"));
}
#[cfg(test)]
mod tests {
    use super::dna_strand;

    #[test]
    fn a_to_t() {
        assert_eq!(dna_strand("A"), "T");
    }

    #[test]
    fn t_to_a() {
        assert_eq!(dna_strand("T"), "A");
    }

    #[test]
    fn c_to_g() {
        assert_eq!(dna_strand("C"), "G");
    }

    #[test]
    fn g_to_c() {
        assert_eq!(dna_strand("G"), "C");
    }

    #[test]
    fn longer_strand_is_changed_in_order() {
        assert_eq!(dna_strand("ATTGC"), "TAACG");
    }
}