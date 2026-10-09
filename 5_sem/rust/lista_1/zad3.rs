fn square_area_to_circle(size:f64) -> f64 {
    size * std::f64::consts::PI / 4.0
}

fn main() {
    println!("{}", square_area_to_circle(9.0));
}

fn assert_close(a:f64, b:f64, epsilon:f64) {
    assert!( (a-b).abs() < epsilon, "Expected: {}, got: {}",b,a);
}

#[test]
fn calculates_area_for_zero() {
    assert_close(square_area_to_circle(0.0), 0.0, 1e-8);
}

#[test]
fn calculates_area_for_one() {
    assert_close(square_area_to_circle(1.0), 0.7853981633974483, 1e-8);
}

#[test]
fn calculates_area_for_four() {
    assert_close(square_area_to_circle(4.0), 3.141592653589793, 1e-8);
}

#[test]
fn calculates_area_for_nine() {
    assert_close(square_area_to_circle(9.0), 7.0685834705770345, 1e-8);
}

#[test]
fn calculates_area_for_twenty() {
    assert_close(square_area_to_circle(20.0), 15.70796326794897, 1e-8);
}