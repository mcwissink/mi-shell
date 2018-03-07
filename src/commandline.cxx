/**
 * CS-232
 * commandline.cxx
 * @author Ian Adams
 * @version 03/04/18
 */

#include "commandline.hxx"
#include "util.hxx"
#include <sstream>
#include <algorithm>
extern "C" {
  #include <stdlib.h>
}

/* CommandLine constructor
 * Params: istream& in
 * Creates an instance of CommandLine
 * Initializes argv and argc
 */
CommandLine::CommandLine(std::istream& in) {
  std::string command;
  std::getline(in, command);
  argv = util::split(command, ' ');
  argc = argv.size();
}

/* getArgVector() const
 * returns argv
 * no parameters
 */
std::vector<char*> CommandLine::getArgVector() const {
  std::vector<char*> c_argv;

  for (size_t i = 0; i < argv.size(); i++) {
    if (argv[i] != "&")
      c_argv.push_back(strdup(argv[i].c_str()));
  }

  c_argv.push_back(NULL);
  return c_argv;
}

/* noAmpersand() const
 * returns a bool: true if the last entry of argv is an ampersand, else false
 * no parameters
 */
bool CommandLine::noAmpersand() const {
  return std::find(argv.begin(), argv.end(), "&") == argv.end();
}
