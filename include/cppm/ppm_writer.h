#ifndef PPM_WRITER_H
#define PPM_WRITER_H

#include <cppm/ppm_image.h>

#include <string>

class PpmWriter
{
public:
    explicit PpmWriter(std::string path);

    void Write(const PpmImage& image) const;

private:
    std::string m_path;
};

std::string GetDataString(const PpmImage& image);
std::string GetDimensionsString(PpmImageDimensions image_dimensions);
std::string GetMaxValueString(PpmImageMaxValue image_max_value);
std::string GetMagicNumberString(PpmImageType image_type);

#endif // PPM_WRITER_H