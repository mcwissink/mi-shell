/**
 * CS-232
 * commandline.hxx
 * @author Mark Wissink
 * @version 03/03/18
 * CommandLine
 * Handles command and arguements input
 */

#pragma once

#include <iostream>
#include <vector>
#include <cstring>

class CommandLine {
 public:
    CommandLine(std::istream& in);
    char* getCommand() const;
    int getArgCount() const;
    std::vector<char*> getArgVector() const;
    char* getArgVector(int i) const;
    bool noAmpersand() const;
  private:
    int argc;
    std::vector<std::string> argv;
};
