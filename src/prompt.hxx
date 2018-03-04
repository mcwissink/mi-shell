#pragma once
#include <string>

class Prompt {
  public:
    Prompt();
    std::string get() const;
  private:
    std::string fullPath;
};

