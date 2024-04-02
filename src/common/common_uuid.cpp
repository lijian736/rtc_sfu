#include "common_uuid.h"

std::string get_uuid()
{
	char buffer[64] = { 0 };
	uuid_t uu;
	uuid_generate(uu);

	int32_t index = 0;
	for (int32_t i = 0; i < 16; i++)
	{
		int32_t len = i < 15 ? sprintf(buffer + index, "%02X-", uu[i]) : sprintf(buffer + index, "%02X", uu[i]);
		if (len < 0)
		{
			return std::string("");
		}

		index += len;
	}

	return std::string(buffer);
}