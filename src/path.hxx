/**
 * CS-232
 * path.cxx
 * @author Mark Wissink
 * @version 03/03/18
 * Path
 * Handles the PATH environement variable
 */

#pragma once

#include <vector>
#include <string>

class Path {
  public:
    Path();
    int find(const std::string& program) const;
    std::string getDirectory(int i) const { return dirs[i]; };
  private:
    std::vector<std::string> dirs;
};
