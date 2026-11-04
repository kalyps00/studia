mod image;
mod complex;

use image::{Image, Color};
use complex::Complex;

fn calculate_color(iter: usize, max_iter: usize) -> Color {
    if iter == max_iter {
        return Color { r: 0, g: 0, b: 0 };
    }
    let t = iter as f64 / max_iter as f64;
    let r = (9.0 * (1.0 - t) * t * t * t * 255.0) as u8;
    let g = (15.0 * (1.0 - t) * (1.0 - t) * t * t * 255.0) as u8;
    let b = (8.5 * (1.0 - t) * (1.0 - t) * (1.0 - t) * t * 255.0) as u8;
    Color { r, g, b }
}

fn generate_mandelbrot(
    filename: &str,
    width: usize,
    height: usize,
    x_min: f64,
    x_max: f64,
    y_min: f64,
    y_max: f64,
) -> std::io::Result<()> {
    let mut img = Image::new(width, height);
    let max_iter = 1000;

    for y in 0..height {
        let im = y_min + (y_max - y_min) * (y as f64) / (height as f64);
        for x in 0..width {
            let re = x_min + (x_max - x_min) * (x as f64) / (width as f64);
            
            let c = Complex::new(re, im);
            let mut z = Complex::new(0.0, 0.0);
            let mut iter = 0;

            while z.norm_sqr() <= 4.0 && iter < max_iter {
                z = z * z + c;
                iter += 1;
            }

            img.set_pixel(x, y, calculate_color(iter, max_iter));
        }
    }

    img.save_to_ppm(filename)
}

fn main() -> std::io::Result<()> {
    generate_mandelbrot("mandelbrot_full.ppm", 800, 800, -2.0, 0.5, -1.25, 1.25)?;
    generate_mandelbrot("mandelbrot_seahorse.ppm", 800, 800, -0.75, -0.73, 0.09, 0.11)?;
    generate_mandelbrot("mandelbrot_elephant.ppm", 800, 800, 0.25, 0.35, -0.05, 0.05)?;
    generate_mandelbrot("mandelbrot_deep_zoom.ppm", 1000, 1000, -1.7499, -1.7489, -0.0005, 0.0005)?;
    generate_mandelbrot("mandelbrot_crown.ppm", 800, 600, -0.15, 0.05, -1.05, -0.9)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::generate_mandelbrot;
    use std::fs;

    fn read_ppm(path: &std::path::Path) -> (usize, usize, Vec<[u8; 3]>) {
        let contents = fs::read_to_string(path).unwrap();
        let mut tokens = contents.split_whitespace();

        assert_eq!(tokens.next(), Some("P3"));
        let width = tokens.next().unwrap().parse().unwrap();
        let height = tokens.next().unwrap().parse().unwrap();
        assert_eq!(tokens.next(), Some("255"));

        let values: Vec<u8> = tokens.map(|token| token.parse().unwrap()).collect();
        assert_eq!(values.len(), width * height * 3);

        let pixels = values
            .chunks_exact(3)
            .map(|rgb| [rgb[0], rgb[1], rgb[2]])
            .collect();
        (width, height, pixels)
    }

    #[test]
    fn generates_mandelbrot_at_two_resolutions() {
        let directory = std::env::temp_dir();
        let small = directory.join("fractal_mandelbrot_small.ppm");
        let large = directory.join("fractal_mandelbrot_large.ppm");

        generate_mandelbrot(small.to_str().unwrap(), 32, 24, -2.0, 0.5, -1.25, 1.25).unwrap();
        generate_mandelbrot(large.to_str().unwrap(), 64, 48, -0.9, -0.5, -0.2, 0.2).unwrap();

        let (width, height, pixels) = read_ppm(&small);
        assert_eq!((width, height), (32, 24));
        assert!(pixels.iter().any(|pixel| *pixel == [0, 0, 0]));
        assert!(pixels.iter().any(|pixel| *pixel != [0, 0, 0]));

        let (width, height, pixels) = read_ppm(&large);
        assert_eq!((width, height), (64, 48));
        assert!(pixels.iter().any(|pixel| *pixel != [0, 0, 0]));
        fs::remove_file(small).unwrap();
        fs::remove_file(large).unwrap();
    }

    #[test]
    fn generates_mandelbrot_zoom() {
        let path = std::env::temp_dir().join("fractal_mandelbrot_zoom.ppm");

        generate_mandelbrot(path.to_str().unwrap(), 100, 70, -0.75, -0.65, 0.05, 0.15).unwrap();

        let (width, height, pixels) = read_ppm(&path);
        assert_eq!((width, height), (100, 70));
        assert_eq!(pixels.len(), 100 * 70);
        fs::remove_file(path).unwrap();
    }

    #[test]
    fn distinguishes_a_point_inside_and_outside_mandelbrot_set() {
        let path = std::env::temp_dir().join("fractal_mandelbrot_known_points.ppm");

        generate_mandelbrot(path.to_str().unwrap(), 2, 1, 0.0, 2.0, 0.0, 1.0).unwrap();

        let (_, _, pixels) = read_ppm(&path);
        assert_eq!(pixels[0], [0, 0, 0]);
        assert_ne!(pixels[1], [0, 0, 0]);
        fs::remove_file(path).unwrap();
    }
}