/* Copyright (C) 2012-2012 galaxycrawler.org

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

/**
 * @namespace galaxy_crawler::util::text
 * @brief     Providing some useful text functions.
 * Change Log:
 */

#ifndef _GALAXY_CRAWLER_UTIL_TEXT_TEXT_H_
#define _GALAXY_CRAWLER_UTIL_TEXT_TEXT_H_

#include <stdint.h>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <utility>

namespace galaxy_crawler { namespace util { namespace text {

/// all functions here are static, so we use a namespace to warp these functions and make it looks like a class
namespace Text {
  /// Convert string type to other type.(note:type should support << operator)
  /// @param[in] s, converted string
  /// @param[in] radix, base of the conversion, 16, 8, or default 10
  /// @return The result converted from string
  template <typename T> T FromString(const std::string &s, uint16_t radix);

  /// @brief Convert T type(note:type should support << operator) to string type
  /// @param[in] t, converted T's instance
  /// @param[in] radix, base of the conversion, 16, 8, or default 10
  /// @return The result, converted from string
  template <typename T> std::string ToString(const T &t, uint16_t radix);

  /// Convert string to int32_t
  /// @param[in] value, string of integer
  /// @return int32_t, converted from string
  int32_t StrToInt(const std::string &str_value);

  /// Convert string to int64_t
  /// @param[in] value, string of integer
  /// @return int64_t, converted from string
  int64_t StrToInt64(const std::string &str_value);

  /// @brief convert string to double
  /// @param[in] value, string of double
  /// @return double, converted from string
  double StrToDouble(const std::string &str_value);

  /// Convert int32_t to string
  /// @param[in] value, a int32_t integer
  /// @return string of int32_t value
  std::string IntToStr(int32_t value);

  /// Convert uint32_t to string
  /// @param[in] value, a int32_t integer
  /// @return string of uint32_t value
  std::string UIntToStr(uint32_t value);

  /// Convert int64_t to string
  /// @param[in] value, a int64_t integer
  /// @return string of int64_t value
  std::string Int64ToStr(int64_t value);

  /// Convert uint64_t to string
  /// @param[in] value, a uint64_t integer
  /// @return string of uint64_t value
  std::string UInt64ToStr(uint64_t value);

  /// Convert double to string
  /// @param[in] value, a double value
  /// @return string of double value
  std::string DoubleToStr(double value);

  /// @brief split string by specified char seperator.
  /// @param[in] input,  string to be split
  /// @param[in] seperator, char seperator
  /// @param[out] segments, split result, string vector
  /// @return void
  void Segment(const std::string &input, char seperator, std::vector<std::string> *segments);

  /// Same as Segment function, the only difference is that you can use string seperator.
  void Segment(const std::string &input, const std::string &seperator, std::vector<std::string> *segments);

  /// trim space(\r\n\t) behind and before string
  /// @param[in,out] str is source string
  /// @return void
  void Trim(std::string *pstr);

  /// trim specified string behind and before string
  /// @param[in] remstr is the char set should be removed at head and tail parts
  /// @param[in,out] str is source string
  /// @return void
  void Trim(const std::string &remstr, std::string *pstr);

  /// @brief Remove all leading occurrences of a set of specified characters from the source string(all_str) in-place.
  /// @param[in] all_str is the char set should be removed at head and tail parts
  /// @param[in,out] pstr is source string
  /// @return void
  void LTrimAll(const std::string &all_str, std::string *pstr);

  /// @brief Remove all tail occurrences of a set of specified characters from the source string(all_str) in-place.
  /// @param[in] all_str is the char set should be removed at head and tail parts
  /// @param[in,out] pstr is source string
  /// @return void
  void RTrimAll(const std::string &all_str, std::string *pstr);

  /// @brief Remove all leading and tail occurrences of a set of specified characters from the source string(all_str) in-place.
  /// @param[in] all_str is the char set should be removed at head and tail parts
  /// @param[in,out] *pstr is source string
  /// @return void
  void TrimAll(const std::string &allstr, std::string *pstr);

  /// replace str_pattern to str_replace in string, str_pattern and str_replace with the same length.
  /// @param[in] str_pattern is the sub string to be str_pattern
  /// @param[in] str_replace is the string which is ued to replace the orign string
  /// @param[in,out] pstr is source string
  /// @return Return the number of str_pattern string. If str or str_pattern is empty, return -1
  int  ReplaceStrStrSameLen(const std::string &str_pattern, const std::string &str_replace, std::string *pstr);

  /// replace str_pattern to str_replace in string,
  /// @param[in] str_pattern is the sub string to be str_pattern
  /// @param[in] str_replace is the string which is ued to replace the orign string
  /// @param[in,out] pstr is source string
  /// @return Return the number of str_pattern string. If str or str_pattern is empty, return -1
  int  ReplaceStrStr(const  std::string &str_pattern, const std::string &str_replace, std::string *pstr);

  /// replace a string
  /// @param[in] vec_replaced is the sub string set to be str_pattern
  /// @param[in] str_replace is the string which is ued to replace the orign string
  /// @param[in] ntype specify whether use safe method. If ntype is nonzero, use safe method
  /// @param[in,out] str is source string
  /// @return Return the number of str_pattern string. If str or str_pattern is empty, return -1
  int  ReplaceStrVec(const  std::vector<std::string>  &vec_pattern, const std::string &str_replace, std::string *pstr);

  /// count str_word appears times in str_content
  int GetWordCount(const std::string &str_content, const std::string &str_word);

  template <typename T> T FromString(const std::string &s, uint16_t radix) {
    std::istringstream iss(s);
    T t = 0; //default value is 0, by david
    if (16 == radix)
      iss >> std::hex >> t;
    else if (8 == radix)
      iss >> std::oct >> t;
    else
      iss >> t;
    return t;
  };

  template <typename T> std::string ToString(const T &t, uint16_t radix) {
    std::ostringstream oss;
    if (16 == radix)
      oss << std::hex << t;
    else if (8 == radix)
      oss << std::oct << t;
    else
      oss << t;
    return oss.str();
  };

  /// @brief string left rotated
  /// @param[in/out] p_str rotated string
  /// @param[in] rotate_step
  void LeftRotate(std::string *p_str, int rotate_step);

  /// @brief Reverse a string
  /// @param[in/out] p_str reversed string
  void ReverseStr(std::string *p_str);

  /// @brief Lower letters in string
  /// @param[in/out] p_str
  void ToLower(std::string *p_str);

  /// @brief Upper letters in string
  /// @param[in/out] p_str
  void ToUpper(std::string *p_str);

}
} } }   // end of namespace galaxy_crawler::util::text::Text
#endif  // _GALAXY_CRAWLER_UTIL_TEXT_TEXT_H_

