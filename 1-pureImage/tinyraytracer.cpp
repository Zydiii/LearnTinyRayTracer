#include "geometry.h"

#include <fstream>
#include <vector>

void renderPureBlackImage()
{
    const int width = 1024;
    const int height = 768;
    std::vector<vec3> framebuffer(width * height);

    std::ofstream ofs; // save the framebuffer to file
    ofs.open("./outPureBlackImage.ppm", std::ios::binary);
    ofs << "P6\n"
        << width << " " << height << "\n255\n";
    for (vec3 &c : framebuffer)
    {
        ofs << (char)(c[0]) << (char)(c[1]) << (char)(c[2]);
    }

    ofs.close();
}

void renderPureColorImage()
{
    const int width = 1024;
    const int height = 768;
    std::vector<vec3> framebuffer(width * height);

    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            framebuffer[i + j * width] = vec3{j / float(height), i / float(width), 0};
        }
    }

    std::ofstream ofs; // save the framebuffer to file
    ofs.open("./outPureColorImage.ppm", std::ios::binary);
    ofs << "P6\n"
        << width << " " << height << "\n255\n";
    for (size_t i = 0; i < height * width; ++i)
    {
        for (size_t j = 0; j < 3; j++)
        {
            ofs << (char)(255 * framebuffer[i][j]);
        }
    }
    ofs.close();
}

int main()
{
    renderPureBlackImage();
    renderPureColorImage();
    return 0;
}
