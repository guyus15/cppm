#include <ppm/ppm_image.h>

#include <stack>

PpmImage::PpmImage(const PpmImageConfig config)
    : m_config{}
{
    m_config = config;

    m_data.resize(m_config.dimensions.height);
    for (auto& row : m_data)
    {
        row.resize(m_config.dimensions.width);
    }
}

void PpmImage::SetPixel(const uint32_t x, const uint32_t y, const uint32_t colour)
{
    const uint8_t r = colour >> 16 & 0x0000ff;
    const uint8_t g = colour >> 8 & 0x0000ff;
    const uint8_t b = colour >> 0 & 0x0000ff;

    const PpmImageColourValue colour_value{ r, g, b };

    SetPixel(x, y, colour_value);
}

void PpmImage::SetPixel(const uint32_t x, const uint32_t y, const PpmImageColourValue colour)
{
    m_data[y][x] = colour;
}

void PpmImage::FillPixels(const uint32_t x, const uint32_t y, const uint32_t colour)
{
    const PpmImageColourValue target_colour = GetPixel(x, y);

    const uint8_t r = colour >> 16 & 0x0000ff;
    const uint8_t g = colour >> 8 & 0x0000ff;
    const uint8_t b = colour >> 0 & 0x0000ff;
    const PpmImageColourValue new_colour{ r, g, b };

    std::stack<std::pair<int, int>> unvisited{};
    unvisited.push({ static_cast<int>(x), static_cast<int>(y) });

    while (!unvisited.empty())
    {
        auto& [sc, sr] = unvisited.top();
        unvisited.pop();
        SetPixel(sc, sr, colour);

        if (sr + 1 < static_cast<int>(m_data.size()) && m_data[sr + 1][sc] == target_colour)
            unvisited.push({ sc, sr + 1 });
        if (sr - 1 >= 0 && m_data[sr - 1][sc] == target_colour)
            unvisited.push({ sc, sr - 1 });

        if (sc + 1 < static_cast<int>(m_data[0].size()) && m_data[sr][sc + 1] == target_colour)
            unvisited.push({ sc + 1, sr });
        if (sc - 1 >= 0 && m_data[sr][sc - 1] == target_colour)
            unvisited.push({ sc - 1, sr });
    }
}

PpmImageColourValue PpmImage::GetPixel(const uint32_t x, const uint32_t y) const
{
    return m_data[y][x];
}

PpmImageDimensions PpmImage::GetDimensions() const
{
    return m_config.dimensions;
}

PpmImageType PpmImage::GetType() const
{
    return m_config.type;
}

PpmImageMaxValue PpmImage::GetMaxValue() const
{
    return m_config.max_value;
}

void PpmImage::FillPixel(const int x, const int y, const PpmImageColourValue target_colour, PpmImageColourValue new_colour)
{
    if (m_data[y][x] == new_colour)
    {
        return;
    }

    SetPixel(x, y, new_colour);

    if (y + 1 < static_cast<int>(m_data.size()) && m_data[y + 1][x] == target_colour)
    {
        FillPixel(y + 1, x, target_colour, new_colour);
    }
    if (y - 1 >= 0 && m_data[y - 1][x] == target_colour)
    {
        FillPixel(y - 1, x, target_colour, new_colour);
    }

    if (x + 1 < static_cast<int>(m_data[0].size()) && m_data[y][x + 1] == target_colour)
    {
        FillPixel(y, x + 1, target_colour, new_colour);
    }
    if (x - 1 >= 0 && m_data[y][x - 1] == target_colour)
    {
        FillPixel(y, x - 1, target_colour, new_colour);
    }
}
