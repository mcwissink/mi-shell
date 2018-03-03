#include "commandine.hxx"

CommandLine::CommandLine(char* teststring) {
  char* command >> in;
  setArgC(command);
  argv = calloc(argc, 64);
  fillArgVector(command);
}

private void CommandLine::setArgC(char* commandString) {
  char previousChar = " ";
  char currentChar;
  for(i=0; i<sizeof(commandString); i++) {
    currentChar = commandString[i];
    if(previousChar == " ") {
      if(currentChar != " ") {
        argc += 1
      }
    }
    previousChar = currentChar;
  }
  return argc;
}

private void CommandLine::fillArgVector(char* commandString) {
  int i = 0;
  char* token = strtok(command, " ");
  while(token != NULL) {
    argv[i] = token;
    i++;
    token = strtok(NULL, " ");
  }
}

public char* CommandLine::getCommand() const {
  return argv[0];
}

public int CommandLine::getArgCount() const {
  return argc;
}

public char** CommandLine::getArgVector() const {
  return argv;
}

public char* CommandLine::getArgVector(int i) const {
  return argv[i];
}

public bool CommandLine::noAmpersand() const {
  for(i=0; i<argc; i++) {
    if(argv[i] == "&") {
      return false;
    }
  }
  return true;
}
