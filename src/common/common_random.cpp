#include "common_random.h"

#include <stdlib.h>

Random::Random()
{
    m_file = fopen("/dev/urandom", "rb");
}

Random::~Random()
{
    if (m_file)
    {
        fclose(m_file);
        m_file = nullptr;
    }
}

uint8_t Random::get_random8()
{
    if (!m_file)
    {
        return 0;
    }

    uint8_t value;
    fread(&value, sizeof(uint8_t), 1, m_file);

    return value;
}

uint16_t Random::get_random16()
{
    if (!m_file)
    {
        return 0;
    }

    uint16_t value;
    fread(&value, sizeof(uint16_t), 1, m_file);

    return value;
}

uint32_t Random::get_random32()
{
    if (!m_file)
    {
        return 0;
    }

    uint32_t value;
    fread(&value, sizeof(uint32_t), 1, m_file);

    return value;
}

double Random::get_random_double()
{
    if (!m_file)
    {
        return 0;
    }

    uint32_t value;
    fread(&value, sizeof(uint32_t), 1, m_file);
    value &= 0x7FFFFFFF;

    return (double)value * 4.656612873077393e-10;
}