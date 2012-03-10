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
 * @namespace galaxy_crawler::util::fmd5
 * @brief     Providing file md5 functions.
 * Change Log:
 */

#ifndef _GALAXY_CRAWLER_UTIL_FILE_FMD5_H_
#define _GALAXY_CRAWLER_UTIL_FILE_FMD5_H_

#include <string>
#include <string.h>
#include <stdio.h>

using std::string;

namespace galaxy_crawler { namespace util { namespace file {

namespace FMD5 {

///   md5加密
void md5();

/// 计算文件内容md5值,应用程序直接调用此函数可以得到一个文件内容的MD5值
/// @param[in] file_name：文件名
/// @param[out] file_content  文件内容的md5值
void FileContetMd5(const string &file_name, string &file_content);


}

} } }

#endif ///< GALAXY_CRAWLER_UTIL_FILE_FMD5_H_

