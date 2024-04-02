#include "common_random_device.h"

RandomDevice::RandomDevice()
	:m_distri_int(0, 4294967295), m_distri_double(0, 1)
{
	m_engine.seed(m_device());
}

RandomDevice::~RandomDevice()
{
}

uint8_t RandomDevice::get_random8()
{
	return (uint8_t)(m_distri_int(m_engine) & 0xFF);
}

uint16_t RandomDevice::get_random16()
{
	return (uint16_t)(m_distri_int(m_engine) & 0xFFFF);
}

uint32_t RandomDevice::get_random32()
{
	return m_distri_int(m_engine);
}

double RandomDevice::get_random_double()
{
	return m_distri_double(m_engine);
}