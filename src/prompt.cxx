/**
 * CS-232
 * prompt.cxx
 * @author Mark Wissink
 * @version 03/03/18
 */

#include "prompt.hxx"
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

/**
 * Get the current working directory
 */
Prompt::Prompt() {
  char *buf;  // Pointer to the buffer for storing path name
  long size = pathconf(".", _PC_PATH_MAX); // Make sure we can handle any path size

  // Set the buffer pointer to memory for storing the path
  if ((buf = (char*)malloc((size_t)size)) != NULL)
    cwd = getcwd(buf, (size_t)size);
}

std::string Prompt::getCwd() const {
  return cwd;
}

std::string Prompt::get() const {
  return cwd + "$ ";
};
