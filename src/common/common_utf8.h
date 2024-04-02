#ifndef _H_COMMON_UTF8_H_
#define _H_COMMON_UTF8_H_

#include <string>
#include <stdint.h>

/**
* @brief check if the string is utf8 string
* @param str - the character array
*
* @return true - utf8 string 
* @return false -- other strings
*/
bool is_utf8_chars(const uint8_t *str);

/**
* @brief check if the string is utf8 string
* @param str - the string
*
* @return true - utf8 string
* @return false -- other strings
*/
bool is_utf8_str(const std::string& str);

#endif