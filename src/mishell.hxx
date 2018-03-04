/**
 * CS-232
 * mishell.hxx
 * @author Mark Wissink
 * @version 03/03/18
 * MIShell
 * Integrates CommandLine, Path, and Prompt to create a shell environment.
 */

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
