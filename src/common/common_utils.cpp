#include "common_utils.h"

#include <algorithm>
#include <cctype>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

bool is_little_endian()
{
	uint16_t a = 0x1122;
	uint8_t b = *(uint8_t *)&a;
	if (b == 0x22)
	{
		return true;
	}

	return false;
}

bool check_path_exists(const std::string &path)
{
	struct stat st;
	if (stat(path.c_str(), &st) == 0)
	{
		return true;
	}

	return false;
}

bool create_directory_recursively(const std::string &directory)
{
	if (check_path_exists(directory))
	{
		return true;
	}

	size_t pos = directory.rfind("/");
	if (pos != std::string::npos)
	{
		std::string parent = directory.substr(0, pos);
		bool ret = create_directory_recursively(parent);
		if (!ret)
		{
			return false;
		}
	}

	mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	mode_t oldMask = umask(0);
	int mkdirRet = mkdir(directory.c_str(), mode);
	umask(oldMask);
	if (mkdirRet != 0)
	{
		if (errno == EEXIST)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

std::vector<std::string> string_split(const std::string& str, const std::string& seperator)
{
	std::vector<std::string> result;
	if (seperator.empty())
	{
		result.push_back(str);
		return result;
	}

	std::size_t pos_begin = 0;
	std::size_t pos_seperator = str.find(seperator);
	while (pos_seperator != std::string::npos)
	{
		result.push_back(str.substr(pos_begin, pos_seperator - pos_begin));
		pos_begin = pos_seperator + seperator.length();
		pos_seperator = str.find(seperator, pos_begin);
	}

	result.push_back(str.substr(pos_begin));

	return result;
}

bool string_starts_with(const std::string& str, const std::string& substr)
{
	return str.find(substr) == 0;
}

bool string_ends_with(const std::string& str, const std::string& substr)
{
	size_t pos = str.rfind(substr);
	return (pos != std::string::npos) && (pos == str.length() - substr.length());
}

void string_trim_end(std::string& str)
{
	str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch){
		return !std::isspace(ch);
	}).base(), str.end());
}

void string_trim_start(std::string& str)
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch){
		return !std::isspace(ch);
	}));
}

void string_trim(std::string& str)
{
	str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch){
		return !std::isspace(ch);
	}).base(), str.end());

	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch){
		return !std::isspace(ch);
	}));
}

void string_to_lower(std::string& str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void string_to_upper(std::string& str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
}

void string_replace(std::string& str, const std::string& search, const std::string& replacement)
{
	if (search == replacement)
	{
		return;
	}

	if (search == "")
	{
		return;
	}

	std::string::size_type pos;
	std::string::size_type lastPos = 0;
	while ((pos = str.find(search, lastPos)) != std::string::npos)
	{
		str.replace(pos, search.length(), replacement);
		lastPos = pos + replacement.length();
	}
}