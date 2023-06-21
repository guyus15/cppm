#ifndef PPM_IMAGE_H
#define PPM_IMAGE_H

#include <cstdint>
#include <vector>

typedef uint16_t PpmImageMaxValue;

struct PpmImageColourValue
{
    uint8_t r, g, b;

    bool operator==(const PpmImageColourValue& other) const
    {
        return r == other.r &&g == other.g && b == other.b;
    }
};

struct PpmImageDimensions
{
    uint32_t width, height;
};

enum PpmImageType
{
    PPM_IMAGE_TYPE_NORMAL
};

struct PpmImageConfig
{
    PpmImageDimensions dimensions;
    PpmImageType type;
    PpmImageMaxValue max_value;
};

class PpmImage
{
public:
    explicit PpmImage(PpmImageConfig config);

    void SetPixel(uint32_t x, uint32_t y, uint32_t colour);
    void SetPixel(uint32_t x, uint32_t y, PpmImageColourValue colour);
    void FillPixels(uint32_t x, uint32_t y, uint32_t colour);

    [[nodiscard]] PpmImageColourValue GetPixel(uint32_t x, uint32_t y) const;
    [[nodiscard]] PpmImageDimensions GetDimensions() const;
    [[nodiscard]] PpmImageType GetType() const;
    [[nodiscard]] PpmImageMaxValue GetMaxValue() const;

private:
    PpmImageConfig m_config;
    std::vector<std::vector<PpmImageColourValue>> m_data;

    void FillPixel(int x, int y, PpmImageColourValue target_colour, PpmImageColourValue new_colour);
};

#endif // PPM_IMAGE_H