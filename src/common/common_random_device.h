#ifndef _H_COMMON_RANDOM_DEVICE_H_
#define _H_COMMON_RANDOM_DEVICE_H_

#include <random>
#include <stdint.h>

class RandomDevice
{
public:
	RandomDevice(const RandomDevice &) = delete;
	RandomDevice &operator=(const RandomDevice &) = delete;
	RandomDevice(const RandomDevice &&) = delete;
	RandomDevice &operator=(const RandomDevice &&) = delete;

	RandomDevice();
	~RandomDevice();

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
	std::random_device m_device;
	std::default_random_engine m_engine;
	std::uniform_int_distribution<uint32_t> m_distri_int;
	std::uniform_real_distribution<double> m_distri_double;
};

#endif