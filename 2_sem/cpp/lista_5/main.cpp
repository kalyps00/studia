#include <iostream>
#include "color.hpp"
#include "colorpixel.hpp"
#include "colortransparentnamed.hpp"
#include "pixel.hpp"
#include "vector.hpp"

void test_color()
{
    std::cout << "\n=== Testing Color Class ===\n";
    try
    {
        // Test constructors
        Color default_color;
        std::cout << "Default color (should be 0,0,0): "
                  << default_color.get_red() << ","
                  << default_color.get_green() << ","
                  << default_color.get_blue() << std::endl;

        Color c1(100, 150, 200);
        std::cout << "Color c1(100,150,200): "
                  << c1.get_red() << ","
                  << c1.get_green() << ","
                  << c1.get_blue() << std::endl;

        // Test setters
        c1.set_red(50);
        c1.set_green(100);
        c1.set_blue(150);
        std::cout << "After setters: "
                  << c1.get_red() << ","
                  << c1.get_green() << ","
                  << c1.get_blue() << std::endl;

        // Test lighten/darken
        c1.lighten(20);
        std::cout << "After lighten(20): "
                  << c1.get_red() << ","
                  << c1.get_green() << ","
                  << c1.get_blue() << std::endl;

        c1.darken(50);
        std::cout << "After darken(20): "
                  << c1.get_red() << ","
                  << c1.get_green() << ","
                  << c1.get_blue() << std::endl;

        // Test mix
        Color c2(200, 200, 200);
        Color mixed = Color::mix(c1, c2);
        std::cout << "Mixed color: "
                  << mixed.get_red() << ","
                  << mixed.get_green() << ","
                  << mixed.get_blue() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error in color test: " << e.what() << std::endl;
    }
}

void test_transparent_color()
{
    std::cout << "\n=== Testing TransparentColor Class ===\n";
    try
    {
        Transparentcolor tc(255, 0, 0, 128);
        std::cout << "Transparent red color with alpha=128: "
                  << tc.get_red() << ","
                  << tc.get_green() << ","
                  << tc.get_blue() << ","
                  << tc.get_alpha() << std::endl;

        tc.set_alpha(200);
        std::cout << "After setting alpha to 200: " << tc.get_alpha() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error in transparent color test: " << e.what() << std::endl;
    }
}

void test_colorpixel()
{
    std::cout << "\n=== Testing ColorPixel Class ===\n";
    try
    {
        ColorPixel cp(100, 100, 255, 0, 0);
        std::cout << "Created red pixel at (100,100)" << std::endl;

        Vector v(50, 50);
        cp.move_pixel(v);
        std::cout << "After moving by vector(50,50): ("
                  << cp.get_x() << ","
                  << cp.get_y() << ")" << std::endl;

        // Test invalid movement
        try
        {
            Vector big_v(2000, 2000);
            cp.move_pixel(big_v);
        }
        catch (const std::exception &e)
        {
            std::cout << "Caught expected error: " << e.what() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Error in color pixel test: " << e.what() << std::endl;
    }
}

void test_colortransparentnamed()
{
    std::cout << "\n=== Testing ColorTransparentNamed Class ===\n";
    try
    {
        ColorTransparentNamed ctn("czerwony", 255, 0, 0, 128);
        std::cout << "Created named transparent red: "
                  << ctn.get_name() << " ("
                  << ctn.get_red() << ","
                  << ctn.get_green() << ","
                  << ctn.get_blue() << ","
                  << ctn.get_alpha() << ")" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error in color transparent named test: " << e.what() << std::endl;
    }
}

void test_vector()
{
    std::cout << "\n=== Testing Vector Class ===\n";
    try
    {
        // Test constructors
        Vector v1;
        std::cout << "Default vector (should be 0,0): (" << v1.get_dx() << ", " << v1.get_dy() << ")\n";

        Vector v2(3.5, -2.5);
        std::cout << "Vector v2(3.5, -2.5): (" << v2.get_dx() << ", " << v2.get_dy() << ")\n";

        // Test setters
        v2.set_dx(5.0);
        v2.set_dy(7.0);
        std::cout << "After setters: (" << v2.get_dx() << ", " << v2.get_dy() << ")\n";

        // Test edge cases
        Vector v3(-1e9, 1e9);
        std::cout << "Vector with extreme values: (" << v3.get_dx() << ", " << v3.get_dy() << ")\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "Error in vector test: " << e.what() << std::endl;
    }
}

void test_color_extended()
{
    std::cout << "\n=== Extended Testing for Color Class ===\n";
    try
    {
        Color c1(255, 255, 255);
        std::cout << "Initial color (255,255,255): "
                  << c1.get_red() << "," << c1.get_green() << "," << c1.get_blue() << std::endl;

        // Test darken to black
        c1.darken(100);
        std::cout << "After darken(100): "
                  << c1.get_red() << "," << c1.get_green() << "," << c1.get_blue() << std::endl;

        // Test lighten to white
        c1.lighten(100);
        std::cout << "After lighten(100): "
                  << c1.get_red() << "," << c1.get_green() << "," << c1.get_blue() << std::endl;

        // Test invalid lighten/darken percentages
        try
        {
            c1.lighten(150);
        }
        catch (const std::exception &e)
        {
            std::cout << "Caught expected error for lighten(150): " << e.what() << std::endl;
        }

        try
        {
            c1.darken(-10);
        }
        catch (const std::exception &e)
        {
            std::cout << "Caught expected error for darken(-10): " << e.what() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Error in extended color test: " << e.what() << std::endl;
    }
}

void test_pixel()
{
    std::cout << "\n=== Testing Pixel Class ===\n";
    try
    {
        Pixel p1;
        std::cout << "Default pixel (should be at 1,1): (" << p1.get_x() << ", " << p1.get_y() << ")\n";

        Pixel p2(100, 200);
        std::cout << "Pixel p2(100,200): (" << p2.get_x() << ", " << p2.get_y() << ")\n";

        // Test setters
        p2.set_x(300);
        p2.set_y(400);
        std::cout << "After setters: (" << p2.get_x() << ", " << p2.get_y() << ")\n";

        // Test border distances
        std::cout << "Left border distance: " << p2.left_border_distance() << "\n";
        std::cout << "Right border distance: " << p2.right_border_distance() << "\n";
        std::cout << "Top border distance: " << p2.top_border_distance() << "\n";
        std::cout << "Bottom border distance: " << p2.bottom_border_distance() << "\n";

        // Test distance between pixels
        Pixel p3(500, 600);
        std::cout << "Distance between p2 and p3: " << Pixel::distance_between_pixels(p2, p3) << "\n";

        // Test invalid pixel creation
        try
        {
            Pixel invalid_pixel(2000, 2000);
        }
        catch (const std::exception &e)
        {
            std::cout << "Caught expected error: " << e.what() << "\n";
        }
        // test pixelcolor
        ColorPixel *cp = new ColorPixel(100, 100, 255, 0, 0);
        Pixel *p = cp;
        bool test = (p->get_x() == 100 && p->get_y() == 100);
        std::cout << "Pixel color test: " << (test ? "Passed" : "Failed") << "\n";
        delete cp;    // Clean up
        cp = nullptr; // Avoid dangling pointer
    }
    catch (const std::exception &e)
    {
        std::cout << "Error in pixel test: " << e.what() << "\n";
    }
}
int main()
{
    test_color();
    test_transparent_color();
    test_colorpixel();
    test_colortransparentnamed();
    test_vector();
    test_color_extended();
    test_pixel();

    std::cout << "\nAll tests completed.\n";
    return 0;
}