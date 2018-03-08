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
 * copies argv into a c string vector
 * cargv, a vector of char*
 */
 std::vector<char*> CommandLine::getArgVector() const {
   std::vector<char*> cargv;
   // Copy vector of strings into vector of char* for C
   for (size_t i = 0; i < argv.size(); i++) {
     if (argv[i] != "&")
       cargv.push_back(strdup(argv[i].c_str()));
   }
   // Push back null since that is expected at end of C argv
   cargv.push_back(NULL);
   return cargv;
 }

/* noAmpersand() const
 * returns a bool: true if the last entry of argv is an ampersand, else false
 * no parameters
 */
bool CommandLine::noAmpersand() const {
  return std::find(argv.begin(), argv.end(), "&") == argv.end();
}
