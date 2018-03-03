#include <iostream>
#include <vector>
#include <cstring>

class CommandLine {
  int argc;
  vector<char*> argv;
  CommandLine(istream& in);
  char* getCommand() const;
  int getArgCount() const;
  char** getArgVector() const;
  char* getArgVector(int i) const;
  bool noAmpersand() const;
}
