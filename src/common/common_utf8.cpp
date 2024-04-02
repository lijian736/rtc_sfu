#include "common_utf8.h"

#include <locale>

bool is_utf8_chars(const uint8_t *str)
{
	const uint8_t *byte;
	uint32_t codepoint;
	uint32_t min;

	while (*str)
	{
		byte = str;
		codepoint = *(byte++);
		uint32_t top = (codepoint & 0x80) >> 1;
		if ((codepoint & 0xc0) == 0x80 || codepoint >= 0xFE)
		{
			return false;
		}
		while (codepoint & top)
		{
			int tmp = *(byte++) - 128;
			if (tmp >> 6)
			{
				return false;
			}
			codepoint = (codepoint << 6) + tmp;
			top <<= 5;
		}
		codepoint &= (top << 1) - 1;

		min = byte - str == 1 ? 0 : byte - str == 2 ? 0x80 : 1 << (5 * (byte - str) - 4);
		if (codepoint < min || codepoint >= 0x110000 ||
			codepoint == 0xFFFE ||
			(codepoint >= 0xD800 && codepoint <= 0xDFFF))
		{
			return false;
		}

		str = byte;
	}

	return true;
}

bool is_utf8_str(const std::string& str)
{
	//the character bytes count
	char bytesCount = 0;
	unsigned char chr;
	bool allAreAscii = true;

	std::string::const_iterator it;
	for (it = str.begin(); it != str.end(); it++)
	{
		chr = *it;

		if ((chr & 0x80) != 0)
		{
			allAreAscii = false;
		}

		if (bytesCount == 0)
		{
			if (chr >= 0x80)
			{
				if (chr >= 0xFC && chr <= 0xFD)
				{
					bytesCount = 6;
				}
				else if (chr >= 0xF8)
				{
					bytesCount = 5;
				}
				else if (chr >= 0xF0)
				{
					bytesCount = 4;
				}
				else if (chr >= 0xE0)
				{
					bytesCount = 3;
				}
				else if (chr >= 0xC0)
				{
					bytesCount = 2;
				}
				else
				{
					return false;
				}
				bytesCount--;
			}
		}
		else
		{
			if ((chr & 0xC0) != 0x80)
			{
				return false;
			}
			bytesCount--;
		}
	}

	//left bytes breaks the utf8 rules
	if (bytesCount > 0)
	{
		return false;
	}

	//all characters are ascii-coded, they are utf8
	if (allAreAscii)
	{
		return true;
	}

	return true;
}