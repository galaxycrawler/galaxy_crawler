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

#include "file.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

using std::string;
using std::vector;
using std::set;

namespace galaxy_crawler { namespace util { namespace file { namespace File {

bool LoadFile(const string &path, size_t start_offset, string *pcontent) {
  assert(pcontent != NULL);
  string &content = *pcontent;
  content = "";
  FILE *f = fopen(path.c_str(), "rb");
  if (f == NULL) {
    return false;
  } else {
    fseek(f, start_offset, SEEK_SET);
    char buf[65536];
    int readLen = 0;
    while ((readLen = fread(buf, 1, 65536, f)) > 0) {
      content.append(buf, readLen);
    }
    fclose(f);
    return true;
  }
}

bool LoadListFromFile(const string &path, size_t start_offset, vector<string> *presult) {
  assert(presult != NULL);
  presult->clear();
  string content;
  if (LoadFile(path, start_offset, &content) == false)
    return false;
  for (size_t start_pos = 0, stop_pos = 0; stop_pos < content.size(); ++stop_pos) {
    const char &ch = content[stop_pos];
    if (ch == '\r'|| ch == '\n' || stop_pos == content.size() - 1) {
      if (start_pos != stop_pos)
        presult->push_back(content.substr(start_pos, stop_pos-start_pos));
      start_pos = stop_pos + 1;
    }
  }
  return true;
}

bool LoadListFromFile(const string &path, size_t start_offset, set<string> *presult) {
  assert(presult != NULL);
  presult->clear();
  string content;
  if (LoadFile(path, start_offset, &content) == false)
    return false;
  for (size_t start_pos = 0, stop_pos = 0; stop_pos < content.size();++stop_pos) {
    const char &ch = content[stop_pos];
    if (ch == '\r'|| ch == '\n'|| stop_pos == content.size()-1) {
      if (start_pos != stop_pos)
        presult->insert(content.substr(start_pos, stop_pos-start_pos));
      start_pos = stop_pos+1;
    }
  }
  return true;
}

bool IsFileExist(const string &file) {
  struct stat info;
  if (0 == stat(file.c_str(), &info)) {
    return S_ISREG(info.st_mode);
  }
  return false;
}
} } } }   ///< end of namespace galaxy_crawler::util::file::File

