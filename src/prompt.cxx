#include "prompt.hxx"

#include <stdlib.h>
#include <unistd.h>
#include <iostream>

Prompt::Prompt() {
  char *buf;  // Pointer to the buffer for storing path name
  long size = pathconf(".", _PC_PATH_MAX); // Make sure we can handle any path size
  
  // Set the buffer pointer to memory for storing the path
  if ((buf = (char*)malloc((size_t)size)) != NULL)
    fullPath = getcwd(buf, (size_t)size);
}

std::string Prompt::get() const {
  return fullPath;
}; 

