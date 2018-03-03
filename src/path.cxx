#include "path.hxx"

#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <iostream>

Path::Path() {
  char *path = getenv("PATH");
  char *token;
  // Tokenize the string and store it in dirs
  while ((token = strtok_r(path, ":", &path))) {
    dirs.push_back(token);
  }
}

int Path::find(const std::string& program) const {
  DIR *dir;
  struct dirent *dp;

  // Loop through all the directories in our path
  for (size_t i = 0; i < dirs.size(); i++) {
    // Open the directory
    if ((dir = opendir(dirs[i].c_str())) == NULL) {
      perror("Cannot open directory");
      return -1;
    }

    // Run until we close the directory
    while (dir) {
      if ((dp = readdir(dir)) != NULL) {
        // Compare the name in the dirent structure to program
        if (dp->d_name == program) {
          closedir(dir);
          // Return the index of the directory
          return i;
        }
      } else {
        if (errno == 0) {
          // File was not found
          closedir(dir);
          return -1;
        }
        // There was an error
        closedir(dir);
        perror("Read error");
        return -1;
      }
    }
  }
  return -1;
};

std::string Path::getDirectory(int i) const {
  return dirs[i];
};
