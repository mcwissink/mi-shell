#pragma once
#include "path.hxx"
#include "prompt.hxx"

class MIShell {
  public:
    MIShell();
    void run();
  private:
    Path path;
};

