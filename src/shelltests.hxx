#pragma once

#include "commandline.hxx"
#include "path.hxx"
#include "prompt.hxx"
#include <cassert>

class ShellTests {
public:
  void testAll();
private:
  void testCommandLine();
};
