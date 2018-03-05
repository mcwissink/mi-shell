/**
 * CS-232
 * path.cxx
 * @author Mark Wissink
 * @version 03/03/18
 */

#include "path.hxx"
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <iostream>

/**
 * Constructor builds a vector of all directories in the PATH
 */
Path::Path() {
  // Get the PATH environment variable
  char *path = getenv("PATH");
  char *token;
  // Tokenize the string and store it in dirs
  while ((token = strtok_r(path, ":", &path)))
    dirs.push_back(token);
}

/**
 * Finds the directory in PATH that has the program
 * @param the name of a program
 * @return the index of the directory that stores the program
 */
int Path::find(const std::string& program) const {
  DIR *dir;
  struct dirent *dp;

  // Loop through all the directories in our path
  for (size_t i = 0; i < dirs.size(); i++) {
    // Open the directory
    opendir(dirs[i].c_str());

    // Run until we close the directory
    while (dp = readdir(dir)) {
        // Compare the name in the dirent structure to program
        if (dp->d_name == program) {
          closedir(dir);
          return i;
        }
    }
    closedir(dir);
  }
  return -1;
};

std::string Path::getDirectory(int i) const {
  return dirs[i];
};
