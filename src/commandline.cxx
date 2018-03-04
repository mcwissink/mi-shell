/**
 * CS-232
 * commandline.cxx
 * @author Mark Wissink
 * @version 03/03/18
 */
 
#include "commandline.hxx"
#include <stdlib.h>
#include <sstream>

CommandLine::CommandLine(std::istream& in) {
  std::string command; // The entire command
  std::string arg; // For storing args of the command
  std::vector<char*> args; // Array of args

  std::getline(in, command);
  std::istringstream iss(command);
  while (iss >> arg) {
    char char_arg[arg.length() + 1];
    args.push_back(strcpy(char_arg, arg.c_str()));
    // cout for debuggin
    std::cout << arg << std::endl;
  }

  argc = args.size();
  argv = args.data();

  std::cout << argc << ", " << argv << std::endl;
}

CommandLine::CommandLine(char* teststring) {
  //char* command >> in;
  //char *command = teststring;
  //setArgC(command);
  //argv = (char**)calloc(argc, sizeof(char*));
}

void CommandLine::setArgC(char* commandString) {
  argc = 0;
  char previousChar = ' ';
  char currentChar;
  for(int i=0; i<sizeof(commandString); i++) {
    currentChar = commandString[i];
    if(previousChar == ' ') {
      if(currentChar != ' ') {
        argc += 1;
      }
    }
    previousChar = currentChar;
  }
}

void CommandLine::fillArgVector(char* commandString) {
  int i = 0;
  char* token = strtok(commandString, " ");
  while(token != NULL) {
    argv[i] = token;
    i++;
    token = strtok(NULL, " ");
  }
}

char* CommandLine::getCommand() const {
  return argv[0];
}

int CommandLine::getArgCount() const {
  return argc;
}

char** CommandLine::getArgVector() const {
  return argv;
}

char* CommandLine::getArgVector(int i) const {
  return argv[i];
}

bool CommandLine::noAmpersand() const {
  for(int i=0; i<argc; i++) {
    if(*argv[i] == '&') {
      return false;
    }
  }
  return true;
}
