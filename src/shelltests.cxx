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
  cout << "1" << endl;
  assert(cl.getArgCount() == 3);
  cout << "2" << endl;
  assert(cl.getCommand() == "emacs");
  cout << "3" << endl;
  assert(cl.getArgVector(0) == "emacs");
  cout << "4" << endl;
  assert(cl.getArgVector(1) == "ruby.py");
  cout << "5" << endl;
  assert(cl.getArgVector(2) == "&");
  cout << "6" << endl;
  assert(!cl.noAmpersand());
  cout << "passed..." << endl;
}
