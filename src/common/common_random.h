#ifndef _H_COMMON_RANDOM_H_
#define _H_COMMON_RANDOM_H_

#include <stdint.h>
#include <stdio.h>

class Random
{
public:
    Random();
    ~Random();

    /**
     * @brief Get a unsigned octet random value
     * 
     * @return uint8_t 
     */
    uint8_t get_random8();

    /**
     * @brief Get a two-octet unsigned random value
     * 
     * @return uint16_t 
     */
    uint16_t get_random16();

    /**
     * @brief Get a four-octet unsigned random value
     * 
     * @return uint32_t 
     */
    uint32_t get_random32();

    /**
     * @brief Get a random double between 0 and 1, 0 included, 1 not included
     * 
     * @return double 
     */
    double get_random_double();

private:
    FILE* m_file;
};

#endif