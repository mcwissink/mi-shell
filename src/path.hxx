#pragma once
#include <vector>
#include <string>

class Path {
  public:
    Path();
    int find(const std::string& program) const;
    std::string getDirectory(int i) const;
  private:
    std::vector<std::string> dirs;
};

