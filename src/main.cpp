#include <ppm/ppm_image.h>
#include <ppm/ppm_writer.h>

int main()
{
    PpmImageConfig config{};
    config.dimensions = { 100, 100 };
    config.type = PPM_IMAGE_TYPE_NORMAL;
    config.max_value = 255;

    PpmImage image{ config };

    for (uint32_t i = 0; i < 100; i++)
    {
        image.SetPixel(i, i, 0x28c023);
    }

    //image.FillPixels(0, 25, 0xff0000);
    image.FillPixels(75, 25, 0x0000ff);

    const PpmWriter writer{ "test_file.pbm" };
    writer.Write(image);

    return 0;
}