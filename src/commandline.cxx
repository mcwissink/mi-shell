#include "CommandLine.h"

class CommandLine {
  int argc;
  vector<char*> argv;

  CommandLine(istream& in) {
    char* command >> in;
    argc = 0;
    token = strtok (command, " ")
    while (token != NULL)
    {
       argv.push_back(token)
       token = strtok (NULL, " ,.-");
       argc += 1;
    }
  }

  char* getCommand() const {
    return argv[0];
  }

  int getArgCount() const {
    return argc;
  }

  vector<char*> getArgVector() const {
    return argv;
  }

  char* getArgVector(int i) const {
    return argv[i];
  }

  bool noAmpersand() const {
    for(i=0; i<argc; i++) {
      if(argv[i] == "&") {
        return false;
      }
    }
    return true;
  }

  int runTests() {

  }
}
