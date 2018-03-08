/**
 * CS-232
 * path.cxx
 * @author Mark Wissink
 * @version 03/03/18
 */

#include "path.hxx"
#include "util.hxx"
#include <iostream>
extern "C" {
  #include <errno.h>
  #include <string.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <dirent.h>
  #include <sys/types.h>
}

/**
 * Constructor builds a vector of all directories in the PATH
 */
Path::Path() {
  dirs = util::split(getenv("PATH"), ':');
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
    util::syserr((dir = opendir(dirs[i].c_str())) == NULL);
    // Run until we close the directory
    while ((dp = readdir(dir))) {
      // Compare the name in the dirent structure to program
      if (dp->d_name == program) {
        util::syserr(closedir(dir) == -1);
        // Return the index of the current directory
        return i;
      }
    }
    // Close the dir
    util::syserr(closedir(dir) == -1);
  }
  // Return -1 since we didn't find any
  return -1;
};

std::string Path::buildPath(const std::string& path, const std::string& program) const {
  return path + '/' + program;
}
