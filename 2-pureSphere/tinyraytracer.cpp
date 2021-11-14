#include "geometry.h"

#include <fstream>
#include <vector>

struct Sphere
{
    vec3 center;
    float radius;

    Sphere(const vec3 &c, const float &r) : center(c), radius(r) {}

    bool ray_intersect(const vec3 &orig, const vec3 &dir) const
    {
        vec3 L = center - orig;
        float tca = L * dir;
        float d2 = L * L - tca * tca;
        if (d2 > radius * radius)
            return false;
        return true;
    }
};

vec3 cast_ray(const vec3 &orig, const vec3 &dir, const Sphere &sphere)
{
    if (!sphere.ray_intersect(orig, dir))
    {
        return vec3{0.2, 0.7, 0.8}; // background color
    }
    return vec3{1.0, 0.42, 0.42};
}

void render(const Sphere &sphere)
{
    const int width = 1024;
    const int height = 768;
    const float fov = M_PI / 3.0;
    std::vector<vec3> framebuffer(width * height);

    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            float x = (i + 0.5) - width / 2.;
            float y = -(j + 0.5) + height / 2.;
            float z = -height / (2. * tan(fov / 2.));
            vec3 dir = vec3{x, y, z}.normalize();
            framebuffer[i + j * width] = cast_ray(vec3{0, 0, 0}, dir, sphere);
        }
    }

    std::ofstream ofs; // save the framebuffer to file
    ofs.open("./outPureSphereImage.ppm", std::ios::binary);
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
    Sphere sphere(vec3{-3, 0, -16}, 2);
    render(sphere);
    return 0;
}
