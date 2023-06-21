#include <cppm/ppm_writer.h>

#include <fstream>
#include <iostream>
#include <sstream>

PpmWriter::PpmWriter(std::string path)
{
    m_path = std::move(path);
}

void PpmWriter::Write(const PpmImage& image) const
{
    std::ofstream image_file;
    image_file.open(m_path);

    if (!image_file.is_open())
    {
        throw std::runtime_error{ "Could not open file '" + m_path + "'." };
    }

    image_file << GetMagicNumberString(image.GetType()) << " ";
    image_file << GetDimensionsString(image.GetDimensions()) << " ";
    image_file << GetMaxValueString(image.GetMaxValue()) << " ";
    image_file << GetDataString(image) << "\n";

    image_file.close();
}

std::string GetDataString(const PpmImage& image)
{
    std::stringstream data_string{};

    const auto [width, height] = image.GetDimensions();

    for (uint32_t y = 0; y < height; y++)
    {
        for (uint32_t x = 0; x < width; x++)
        {
            const auto [r, g, b] = image.GetPixel(x, y);

            if (image.GetMaxValue() >= 256)
            {
                data_string << std::hex << r << g << b << 0;
            }
            else
            {
                data_string << std::hex << r << g << b;
            }

        }
    }

    return data_string.str();
}

std::string GetDimensionsString(const PpmImageDimensions image_dimensions)
{
    std::stringstream image_dimensions_stream;
    image_dimensions_stream << image_dimensions.width << " " << image_dimensions.height;
    return image_dimensions_stream.str();
}

std::string GetMaxValueString(const PpmImageMaxValue image_max_value)
{
    std::stringstream image_max_value_stream;
    image_max_value_stream << image_max_value;
    return image_max_value_stream.str();
}

std::string GetMagicNumberString(const PpmImageType image_type)
{
    switch (image_type)
    {
    case PPM_IMAGE_TYPE_NORMAL:
        return "P6";
    }

    throw std::invalid_argument{ "Cannot determine magic number "
                                 "from the given image type." };
}
