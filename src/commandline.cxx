#include "commandline.hxx"

#include <stdlib.h>

CommandLine::CommandLine(char* teststring) {
  //char* command >> in;
  char *command = teststring;
  setArgC(command);
  argv = (char**)calloc(argc, sizeof(char*));
  fillArgVector(command);
}

void CommandLine::setArgC(char* commandString) {
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
    if(argv[i] == "&") {
      return false;
    }
  }
  return true;
}
