/**
 * CS-232
 * commandline.cxx
 * @author Ian Adams
 * @version 03/04/18
 */

#include "commandline.hxx"
#include <stdlib.h>
#include <sstream>

/* CommandLine constructor
 * Params: istream& in
 * Creates an instance of CommandLine
 * Initializes argv and argc
 */
CommandLine::CommandLine(std::istream& in) {
  std::string command;
  std::getline(in, command);
  std::vector<char*> results;
  //https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
  //thanks to stack overflow for assistance splitting the command
  size_t pos = 0;
  std::string token;
  while ((pos = command.find(" ")) != std::string::npos) {
    token = command.substr(0, pos);
    char* char_token = (char*) calloc(token.length()+1, 1);
    results.push_back(strcpy(char_token, token.c_str()));
    command.erase(0, pos + 1);
  }
  char* char_token = (char*) calloc(command.length()+1, 1);
  results.push_back(strcpy(char_token, command.c_str()));
  results.push_back(NULL);

  argc = results.size();
  argv = results.data();
}


/* getCommand() const
 * returns the address in the first entry of argv (char*)
 * No parameters
 */
char* CommandLine::getCommand() const {
  return argv[0];
}

/* getArgCount() const
 * returns argc (int)
 * no parameters
 */
int CommandLine::getArgCount() const {
  return argc;
}

/* getArgVector() const
 * returns argv
 * no parameters
 */
char** CommandLine::getArgVector() const {
  return argv;
}

/* getArgVector(int i) const
 * returns the address at the ith entry in argv
 * parameters: i, an integer
 */
char* CommandLine::getArgVector(int i) const {
  return argv[i];
}

/* noAmpersand() const
 * returns a bool: true if the last entry of argv is an ampersand, else false
 * no parameters
 */
bool CommandLine::noAmpersand() const {
  if (argv[argc-1][0] == '&') {
    return false;
  }
  return true;
}
/*
CommandLine::~CommandLine() {
  for(int i=0; argv[i] != NULL; i++) {
    free(argv[i]);
  }
  free(argv);
}*/
