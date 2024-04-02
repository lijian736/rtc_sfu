#ifndef _H_APP_CONFIG_H_
#define _H_APP_CONFIG_H_

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

/**
 * the application configuration class
 */
class AppConfig
{
	friend std::ostream& operator<<(std::ostream& os, const AppConfig& config);
private:
	AppConfig() {};
public:
	virtual ~AppConfig();

	static AppConfig* get_instance();

	/**
	* @brief initialize
	* @param fileName -- the config file name
	*        delimiter -- the delimiter between key and value
	*        comment -- the config comments start code
	* @return true - successful, false - fail
	*/
	bool initialize(const std::string& fileName, const std::string& delimiter = "=", const std::string& comment = "#");

	/**
	* @brief if the config file exists
	*
	* @return true - exists, false - the file does not exists.
	*/
	bool is_config_file_exists();

	/**
	* @brief read the config file content and parse
	*
	* @return true -- read and parse successfully. false - failed
	*/
	bool read_and_parse();

	/**
	* @brief get the value by key
	* 
	* @param key -- the config key
	*        defaultValue -- if the key does not exists, then return the default value
	* @return the value, if the key does not exists, return ""
	*/
	std::string get_by_key(const std::string& key, std::string defaultValue = "");

private:
	//the config file name
	std::string m_config_file_name;
	//the delimiter between key and value
	std::string m_delimiter;
	//the delimiter between value and comments
	std::string m_comment;

	//the configuration contents
	std::map<std::string, std::string> m_configs;
};



#endif