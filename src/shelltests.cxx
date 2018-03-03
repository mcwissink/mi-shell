#include "shelltests.hxx"
using namespace std;

void ShellTests::testAll() {
  cout << "Testing stuff..." << endl;
  testCommandLine();
  testPath();
  testPrompt();
  cout << "Tests passed..." << endl;
}

void ShellTests::testPath() {

}

void ShellTests::testPrompt() {

}

void ShellTests::testCommandLine() {
  cout << "Testing CommandLine... ";
  CommandLine cl((char*)"emacs ruby.py &");
  assert(cl.getArgCount() == 3);
  assert(cl.getCommand() == "emacs");
  assert(cl.getArgVector(0) == "emacs");
  assert(cl.getArgVector(1) == "ruby.py");
  assert(cl.getArgVector(2) == "&");
  assert(!cl.noAmpersand());
  cout << "passed..." << endl;
}
