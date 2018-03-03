#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>

class path {
  public:
    path();
    int find(const std::string& program) const;
    std::string getDirectory(int i) const;
};

