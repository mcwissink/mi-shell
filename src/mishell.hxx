/**
 * CS-232
 * mishell.hxx
 * @author Mark Wissink
 * @version 03/03/18
 * MIShell
 * Integrates CommandLine, Path, and Prompt to create a shell environment.
 */

#pragma once

#include "commandline.hxx"
#include "path.hxx"
#include "prompt.hxx"

class MIShell {
  public:
    void run();
    void changeDirectory(const Prompt& prompt, const std::string& dir);
    enum Command { C_PWD, C_CD, C_EXIT, C_NONE, C_PROG };
    Command parseCommand(const std::string& command);
    void runProgram(const CommandLine& cl, const std::string& command);
  private:
    Path path;
};
