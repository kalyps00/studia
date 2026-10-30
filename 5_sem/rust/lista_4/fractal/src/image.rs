use::std::fs::File;
use::std::io::Write;

#[derive(Clone, Copy)]
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
    pub fn new(height: usize, width: usize) -> Self {
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
