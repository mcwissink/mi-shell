/**
 * CS-232
 * commandline.hxx
 * @author Ian Adams
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
    std::string getCommand() const { return argc ? argv[0] : ""; };
    int getArgCount() const { return argc; };
    void getArgVector(std::vector<char*>& cargv) const;
    const std::string& getArgVector(int i) const { return argv[i]; };
    bool noAmpersand() const;
  private:
    int argc;
    std::vector<std::string> argv;
};
