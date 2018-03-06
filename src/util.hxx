/**
 * CS-232
 * util.hxx
 * @author Mark Wissink
 * @version 03/03/18
 * utility
 * Some useful functions for the shell.
 */

#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <string.h>
#include <errno.h>

namespace util {
   std::vector<std::string> split(const std::string &s, char delim);
   void syserr(bool err);
}
