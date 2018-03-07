/**
 * CS-232
 * mishell.cxx
 * @author Mark Wissink and Ian Adams
 * @version 03/03/18
 */

#include "util.hxx"
#include <sstream>
#include <iostream>
#include <cstring>
extern "C" {
  #include <errno.h>
}

namespace util {

  /**
   * Parse string into seperate tokens based on delimiter
   * https://stackoverflow.com/questions/236129/the-most-elegant-way-to-iterate-the-words-of-a-string?page=1&tab=votes#tab-top
   * @param a string and delimiter
   * @return an array of the string seperate by the delimiter
   */
  std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    
    while (std::getline(ss, item, delim))
      elems.push_back(item);

    return elems;
  }

  /**
   * Print errors messages
   * @param a boolean, whether the funciton
   * @return an array of the string seperate by the delimiter
   */
  void syserr(bool err) {
    if (err) std::cerr << "Error:" << strerror(errno) << std::endl;
  }
}
