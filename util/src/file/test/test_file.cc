#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "../file.h"
#include "../fmd5.h"

using namespace galaxy_crawler::util::file;

int main() {
  std::string file_path = "./test/test_file.txt";
  std::string file_content;
  File::LoadFile(file_path, 0, &file_content);
  printf("LoadFile:%s\n", file_path.c_str());
  printf("LoadContent:%s\n", file_content.c_str());
  return 0;
}

