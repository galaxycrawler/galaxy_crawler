#include <stdio.h>
#include <string>
#include <stdint.h>
#include "../text.h"

using namespace galaxy_crawler::util::text;

int main() {
  std::string str;
  str = "123456";
  int32_t str_int = Text::StrToInt(str);
  printf("%d\n", str_int);
  return 0;
}
