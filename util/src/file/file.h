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
 * @namespace galaxy_crawler::util::file
 * @brief     Providing some useful file functions.
 * Change Log:
 */

#ifndef _GALAXY_CRAWLER_UTIL_FILE_FILE_H_
#define _GALAXY_CRAWLER_UTIL_FILE_FILE_H_

#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <set>

namespace galaxy_crawler { namespace util { namespace file {

/// all functions here are static, so we use a namespace to warp these functions and make it looks like a class
namespace File {
  /// load file to string
  /// @param[in] path File name to be read
  /// @param[in] start_offset Start point to read
  /// @param[out] pcontent The string loaded
  /// @return Content load from file
  bool LoadFile(const std::string &path, size_t start_offset, std::string *pcontent);

  /// load list file, each line as a std::string, put instd::vector
  /// @note The algorithm is that: load whole file to memory, and segment the content to vector
  /// @param[in] path The file to be load
  /// @param[in] start_offset The start offset of file to load
  /// @param[out] presult The lines loaded
  bool LoadListFromFile(const std::string &path, size_t start_offset, std::vector< std::string > *presult);

  /// load lisr file, each line as a std::string, put instd::set
  /// @note The algorithm is that: load whole file to memory, and segment the content to set
  /// @param[in] path The file to be load
  /// @param[in] start_offset The start offset of file to load
  /// @param[out] presult The lines loaded
  bool LoadListFromFile(const std::string &path, size_t start_offset, std::set<std::string> *presult);

  /// check whether file is file or not
  /// @param[in] file file to be checked
  /// @return true:exist false:not
  bool IsFileExist(const std::string &file);
}
} } }   // end of namespace galaxy_crawler::util::text::file
#endif  ///< _GALAXY_CRAWLER_UTIL_FILE_FILE_H_

