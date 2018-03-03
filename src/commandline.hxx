#pragma once
#include <iostream>
#include <vector>
#include <cstring>

class CommandLine {
  public:
    CommandLine(istream& in);
    char* getCommand() const;
    int getArgCount() const;
    char** getArgVector() const;
    char* getArgVector(int i) const;
    bool noAmpersand() const;
  private:
    int argc;
    char** argv;
};
