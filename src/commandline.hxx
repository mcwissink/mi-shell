#pragma once

#include <iostream>
#include <vector>
#include <cstring>

class CommandLine {
  public:
    CommandLine(char *teststring);
    char* getCommand() const;
    int getArgCount() const;
    char** getArgVector() const;
    char* getArgVector(int i) const;
    bool noAmpersand() const;
  private:
    void setArgC(char *commandString);
    void fillArgVector(char *commandString);
    int argc;
    char** argv;
};
