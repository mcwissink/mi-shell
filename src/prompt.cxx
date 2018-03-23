/**
 * CS-232
 * prompt.cxx
 * @author Mark Wissink
 * @version 03/03/18
 */

#include "prompt.hxx"
#include "util.hxx"
extern "C" {
  #include <stdlib.h>
  #include <unistd.h>
}

/**
 * Get the current working directory
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/getcwd.html
 * TODO: Free the memory
 */
Prompt::Prompt() {
  char *buf;  // Pointer to the buffer for storing path name
  long size;
  util::syserr((size = pathconf(".", _PC_PATH_MAX)) == -1);

  // Set the buffer pointer to memory for storing the path
  if ((buf = (char*)malloc((size_t)size)) != NULL)
    cwd = getcwd(buf, (size_t)size);
}
