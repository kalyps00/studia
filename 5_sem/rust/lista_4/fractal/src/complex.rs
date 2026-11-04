use std::ops::{Add, Div, Mul, Sub};

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Complex {
    pub re: f64,
    pub im: f64,
}
impl Complex{
    pub fn new(re: f64, im:f64) -> Self{
        Self{re, im}
    }
    pub fn norm_sqr(&self) -> f64 {
        self.re * self.re + self.im * self.im
    }
    #[allow(dead_code)]
    pub fn abs_components(self) -> Self {
        Self {
            re: self.re.abs(),
            im: self.im.abs(),
        }
    }

}
impl Add for Complex {
    type Output = Self;

    fn add(self, other: Self) -> Self {
        Self {
            re: self.re + other.re,
            im: self.im + other.im,
        }
    }
}
impl Sub for Complex {
    type Output = Self;

    fn sub(self, other: Self) -> Self {
        Self {
            re: self.re - other.re,
            im: self.im - other.im,
        }
    }
}
impl Mul for Complex {
    type Output = Self;
    fn mul(self, other: Self) -> Self{
        Self { 
            re: self.re*other.re - self.im*other.im, 
            im: self.re*other.im + self.im*other.re
        }
        
    }
    
}
impl Div for Complex{
    type Output = Self;
    fn div(self, other: Self) -> Self{
        Self {
              re: (self.re * other.re + self.im * other.im) / (other.re*other.re + other.im*other.im),
              im: (self.im*other.re - self.re*other.im)/(other.re*other.re + other.im*other.im) 
            }
    }
}

#[cfg(test)]
mod tests {
    use super::Complex;

    #[test]
    fn implements_basic_arithmetic() {
        let first = Complex::new(3.0, 2.0);
        let second = Complex::new(1.0, -4.0);

        assert_eq!(first + second, Complex::new(4.0, -2.0));
        assert_eq!(first - second, Complex::new(2.0, 6.0));
        assert_eq!(first * second, Complex::new(11.0, -10.0));
        assert_eq!(first / second, Complex::new(-0.29411764705882354, 0.8235294117647058));
    }

    #[test]
    fn calculates_squared_norm_and_component_absolute_values() {
        let value = Complex::new(-3.0, 4.0);

        assert_eq!(value.norm_sqr(), 25.0);
        assert_eq!(value.abs_components(), Complex::new(3.0, 4.0));
    }
}