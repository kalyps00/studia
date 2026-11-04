use std::fs::File;
use std::io::Write;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Color {
    pub r: u8,
    pub g: u8,
    pub b: u8,
}

pub struct Image {
    pub height: usize,
    pub width: usize,
    pub pixels: Vec<Color>,
}

impl Image{
    pub fn new(width: usize, height: usize) -> Self {
        let pixels = vec![Color{r: 0, g: 0, b: 0}; height * width];
        Self { height, width, pixels }
    }
    //(0,0) is the top left corner of the image
    pub fn set_pixel(&mut self, x: usize, y: usize, color: Color) {
        if x < self.width && y < self.height {
            let index = y * self.width + x;
            self.pixels[index] = color;
        }
    }

    pub fn save_to_ppm(&self, filename: &str) -> std::io::Result<()>{
        let mut file =File::create(filename)?;
        writeln!(file, "P3")?;
        writeln!(file, "{} {}", self.width, self.height)?;
        writeln!(file, "255")?;
        for pixel in self.pixels.iter(){
            writeln!(file, "{} {} {}", pixel.r, pixel.g, pixel.b)?;
        }
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::{Color, Image};
    use std::fs;

    #[test]
    fn stores_pixels_and_ignores_out_of_bounds_coordinates() {
        let mut image = Image::new(2, 3);
        let color = Color { r: 12, g: 34, b: 56 };

        image.set_pixel(1, 2, color);
        image.set_pixel(2, 3, Color { r: 255, g: 255, b: 255 });

        assert_eq!(image.pixels[5], color);
        assert_eq!(image.pixels[0], Color { r: 0, g: 0, b: 0 });
    }

    #[test]
    fn writes_a_valid_text_ppm_header_and_pixels() {
        let path = std::env::temp_dir().join("fractal_image_test.ppm");
        let mut image = Image::new(2, 1);
        image.set_pixel(0, 0, Color { r: 1, g: 2, b: 3 });
        image.save_to_ppm(path.to_str().unwrap()).unwrap();

        let contents = fs::read_to_string(&path).unwrap();
        assert_eq!(contents, "P3\n2 1\n255\n1 2 3\n0 0 0\n");
        fs::remove_file(path).unwrap();
    }
}
