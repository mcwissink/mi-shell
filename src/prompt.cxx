/**
 * CS-232
 * prompt.cxx
 * @author Mark Wissink
 * @version 03/03/18
 */

#include "prompt.hxx"
extern "C" {
  #include <stdlib.h>
  #include <unistd.h>
}

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
