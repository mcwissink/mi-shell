/**
 * CS-232
 * shelltests.cxx
 * @author Ian Adams
 * @version 03/04/18
 * Mark declined to use this for class testing
 */

#include "shelltests.hxx"
using namespace std;

void ShellTests::testAll() {
  cout << "Testing stuff..." << endl;
  testCommandLine();
  cout << "Tests passed..." << endl;
}

void ShellTests::testCommandLine() {
  // tests command line with input "emacs ruby.py &"
  cout << "Testing CommandLine... $";
  CommandLine cl(std::cin);
  assert(cl.getArgCount() == 3);
  assert(cl.getCommand()[0] == 'e');
  assert(cl.getCommand()[1] == 'm');
  assert(cl.getCommand()[2] == 'a');
  assert(cl.getCommand()[3] == 'c');
  assert(cl.getCommand()[4] == 's');
  assert(cl.getArgVector(0)[0] == 'e');
  assert(cl.getArgVector(0)[1] == 'm');
  assert(cl.getArgVector(0)[2] == 'a');
  assert(cl.getArgVector(0)[3] == 'c');
  assert(cl.getArgVector(0)[4] == 's');
  assert(cl.getArgVector(1)[0] == 'r');
  assert(cl.getArgVector(1)[1] == 'u');
  assert(cl.getArgVector(1)[2] == 'b');
  assert(cl.getArgVector(1)[3] == 'y');
  assert(cl.getArgVector(1)[4] == '.');
  assert(cl.getArgVector(1)[5] == 'p');
  assert(cl.getArgVector(1)[6] == 'y');
  assert(cl.getArgVector(2)[0] == '&');
  assert(!cl.noAmpersand());
  cout << "passed..." << endl;
  //note: all tests were passed
}
