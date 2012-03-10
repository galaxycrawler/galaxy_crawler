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

#include "text.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

using std::string;
using std::vector;

namespace galaxy_crawler { namespace util { namespace text { namespace Text {

int32_t StrToInt(const string &str_value) {
  return atoi(str_value.c_str());
}

int64_t StrToInt64(const string &str_value) {
  return atoll(str_value.c_str());
}

double StrToDouble(const std::string &str_value) {
  return atof(str_value.c_str());
}

string IntToStr(int32_t value) {
  char sz_buf[20];
  memset(sz_buf, 0, sizeof(sz_buf));
  snprintf(sz_buf, sizeof(sz_buf), "%d", static_cast<int32_t>(value));
  return sz_buf;
}

string UIntToStr(uint32_t value) {
  char sz_buf[20];
  memset(sz_buf, 0, sizeof(sz_buf));
  snprintf(sz_buf, sizeof(sz_buf), "%u", static_cast<int32_t>(value));
  return sz_buf;
}

string Int64ToStr(int64_t value) {
  char sz_buf[40];
  memset(sz_buf, 0, sizeof(sz_buf));
  snprintf(sz_buf, sizeof(sz_buf), "%ld", static_cast<int64_t>(value));
  return sz_buf;
}

string UInt64ToStr(uint64_t value) {
  char sz_buf[40];
  memset(sz_buf, 0, sizeof(sz_buf));
  snprintf(sz_buf, sizeof(sz_buf), "%lu", static_cast<uint64_t>(value));
  return sz_buf;
}

string DoubleToStr(double value) {
  char sz_buf[60];
  memset(sz_buf, 0, sizeof(sz_buf));
  snprintf(sz_buf, sizeof(sz_buf), "%f", static_cast<double>(value));
  return sz_buf;
}

void Segment(const string &input, char seperator, vector<string> *segments) {
  if (NULL == segments) {
    return;
  }
  if (input.empty()) {
    return;
  }
  segments->resize(0);
  segments->reserve(input.size()/20);

  size_t start_pos = 0;
  size_t pos = string::npos;
  for (pos = input.find(seperator, start_pos); pos != string::npos; start_pos = pos + 1, pos = input.find(seperator, start_pos)) {
    segments->push_back(input.substr(start_pos, pos - start_pos));
  }
  segments->push_back(input.substr(start_pos));
}

void Segment(const string &input, const string &seperator, vector<string> *segments) {
  if (NULL == segments) {
    return;
  }
  if (input.empty()) {
    return;
  }
  if (seperator.empty()) {
    return;
  }
  segments->resize(0);
  segments->reserve(input.size()/20);
  size_t start_pos = 0;
  size_t pos = string::npos;
  for (pos = input.find(seperator, start_pos); pos != string::npos; start_pos = pos + seperator.size(), pos = input.find(seperator, start_pos)) {
    segments->push_back(input.substr(start_pos, pos - start_pos));
  }
  segments->push_back(input.substr(start_pos));
}

/// no considering gbk yet!
void Trim(string *pstr) {
  assert(pstr != NULL);
  static const string kStrset = "\r\n\t ";
  int start = pstr->find_first_not_of(kStrset);
  if (start == string::npos) {
    *pstr = "";
    return;
  }
  int end = pstr->find_last_not_of(kStrset);
  *pstr = pstr->substr(start, end - start + 1);
}

void Trim(const string &remstr, string *pstr) {
  assert(pstr != NULL);
  pstr->erase(0, pstr->find_first_not_of(remstr));
  pstr->erase(pstr->find_last_not_of(remstr) + 1);
}

void LTrimAll(const string &all_str, string *pstr) {
  assert(pstr != NULL);
  string &str = *pstr;
  if (str.empty()) {
    return;
  }
  size_t begin_pos = 0;
  while (begin_pos < str.length()) {
    char ch = str[begin_pos];
    if (all_str.find(ch) == string::npos) {
      break;
    }
    ++begin_pos;
  }
  str = str.substr(begin_pos);
}

void RTrimAll(const string &all_str, string *pstr) {
  assert(pstr != NULL);
  string & str = *pstr;
  if (str.empty()) {
    return;
  }
  size_t end_pos = str.length()-1;
  while (end_pos>0) {
    char ch = str[end_pos];
    if (all_str.find(ch) == string::npos) {
      break;
    }
    --end_pos;
  };
  if (end_pos == 0) {
    if (all_str.find(str[end_pos]) != string::npos) {
      str = "";
      return;
    }
  }
  str = str.substr(0, end_pos+1);
}

void TrimAll(const string & allstr, string *pstr) {
  LTrimAll(allstr, pstr);
  RTrimAll(allstr, pstr);
}

int ReplaceStrStrSameLen(const string &str_pattern, const string &str_replace, string *pstr) {
  string &str = *pstr;
  int num = 0;
  size_t pos_start = 0;
  while ((pos_start = str.find(str_pattern, pos_start)) != string::npos) {
    str.replace(pos_start, str_pattern.length(), str_replace);
    pos_start += str_replace.size();
    ++num;
  }
  return num;
}

int ReplaceStrStr(const string &str_pattern, const string &str_replace, string *pstr) {
  assert(pstr != NULL);
  string &str = *pstr;
  if (str.empty() || str_pattern.empty())
    return -1;

  if (str_pattern.length() == str_replace.length())
    return ReplaceStrStrSameLen(str_pattern, str_replace, pstr);

  int num = 0;
  string str2 = str;
  str.clear();
  size_t pos_start = 0, pos_find = 0;
  while ((pos_find = str2.find(str_pattern, pos_start)) != string::npos) {
    str += str2.substr(pos_start, pos_find - pos_start);
    str += str_replace;
    pos_start = pos_find + str_pattern.size();
    ++num;
  }
  if (pos_start < str2.size()) {
    str += str2.substr(pos_start);
  }
  return num;
}

int ReplaceStrVec(const vector<std::string> &vec_pattern, const string &str_replace, string *pstr) {
  assert(pstr != NULL);
  int num = 0;
  for (size_t i = 0; i < vec_pattern.size(); ++i) {
    num += ReplaceStrStr(vec_pattern[i], str_replace, pstr);
  }
  return num;
}

int GetWordCount(const string &str_content, const string &str_word) {
  if (str_word.empty())
    return 0;

  int word_count = 0;
  size_t pos = 0;
  while ((pos = str_content.find(str_word, pos)) != string::npos) {
    ++word_count;
    pos += str_word.size();
  }
  return word_count;
}

/// Pre-condition: rotate_step <= p_str->size()
void LeftRotate(std::string *p_str, int rotate_step) {
  if (p_str->empty())
    return;

  assert(rotate_step <= p_str->size());

  ReverseStr(p_str);

  int cut_pos = p_str->size() - rotate_step;
  string str1 = p_str->substr(0, cut_pos);
  string str2 = p_str->substr(cut_pos);

  ReverseStr(&str1);
  ReverseStr(&str2);

  *p_str = str1 + str2;
}

void ReverseStr(std::string *p_str) {
  int len = p_str->size();
  for (int i = 0; i < len/2; i++) {
    char temp = (*p_str)[i];
    (*p_str)[i] = (*p_str)[len-i-1];
    (*p_str)[len-i-1] = temp;
  }
}

void ToLower(string *p_str) {
  if (!p_str)
    return;

  string &str = *p_str;
  for (size_t i = 0; i < str.size(); i++) {
    if ((str[i] >= 'A') && (str[i] <= 'Z')) {
      str[i] += 'a' - 'A';
    }
  }
}

void ToUpper(string *p_str) {
  if (!p_str)
    return;

  string &str = *p_str;
  for (size_t i = 0; i < str.size(); i++) {
    if ((str[i] >= 'a') && (str[i] <= 'z')) {
      str[i] += 'A' - 'a';
    }
  }
}
} } } }   ///< end of namespace galaxy_crawler::util::text::Text

