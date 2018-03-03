#include "path.hxx"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

Path::Path() {
  char *path = getenv("PATH");
  char *token;
  while ((token = strtok_r(path, ":", &path))) {
    dirs.push_back(token);
  }

  for (size_t n = 0; n < dirs.size(); n++)
    std::cout << dirs[n] << std::endl;
}

//int Path::find(const std::string& program) const {};

std::string Path::getDirectory(int i) const {
  return dirs[i];
};
