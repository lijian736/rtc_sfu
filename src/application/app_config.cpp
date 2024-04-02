#include "app_config.h"

#include "common_utils.h"

std::ostream& operator<<(std::ostream& os, const AppConfig& config)
{
	std::map<std::string, std::string>::const_iterator it;
	for (it = config.m_configs.begin(); it != config.m_configs.end(); it++)
	{
		os << it->first << config.m_delimiter << it->second << std::endl;
	}

	return os;
}

AppConfig* AppConfig::get_instance()
{
	static AppConfig g_config;

	return &g_config;
}

bool AppConfig::initialize(const std::string& fileName, const std::string& delimiter, const std::string& comment)
{
	m_config_file_name = fileName;
	m_delimiter = delimiter;
	m_comment = comment;

	return true;
}

AppConfig::~AppConfig()
{
}

bool AppConfig::is_config_file_exists()
{
	std::ifstream in(m_config_file_name.c_str(), std::ios::in);
	if (in)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AppConfig::read_and_parse()
{
	std::ifstream is(m_config_file_name.c_str(), std::ios::in);
	if (!is)
	{
		return false;
	}

	const std::string& delimiter = m_delimiter;
	const std::string& comment = m_comment;
	const std::string::size_type skipLen = delimiter.length();

	std::string line;
	while (is)
	{
		std::getline(is, line);
		line = line.substr(0, line.find(comment));
		std::string::size_type delimPos = line.find(delimiter);

		if (delimPos != std::string::npos)
		{
			std::string key = line.substr(0, delimPos);
			std::string value = line.substr(delimPos + skipLen);

			string_trim(key);
			string_trim(value);
			m_configs[key] = value;
		}
	}

	return true;
}

std::string AppConfig::get_by_key(const std::string& key, std::string defaultValue)
{
	std::map<std::string, std::string>::const_iterator it = m_configs.find(key);
	if (it != m_configs.end())
	{
		return m_configs[key];
	}

	return defaultValue;
}