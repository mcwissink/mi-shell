/**
 * CS-232
 * prompt.hxx
 * @author Mark Wissink
 * @version 03/03/18
 * Prompt
 * Get's the current working directory
 */

#pragma once

#include <string>

class Prompt {
  public:
    Prompt();
    const std::string& get() const { return cwd; };
  private:
    std::string cwd;
};
