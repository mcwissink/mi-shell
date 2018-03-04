/**
 * CS-232
 * mishell.cxx
 * @author Mark Wissink
 * @version 03/03/18
 */

#include "mishell.hxx"
#include "commandline.hxx"
#include <iostream>

MIShell::MIShell() {
  path = Path();
}

/**
 * Runs and contains logic for the shell
 * @param none.
 * @return void.
 */
void MIShell::run() {
  std::string command;
  while(1) {
    std::cout << Prompt().get() << '$' << std::flush;
    CommandLine cl(std::cin);
  }
}
