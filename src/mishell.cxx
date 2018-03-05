/**
 * CS-232
 * mishell.cxx
 * @author Mark Wissink
 * @version 03/03/18
 */

#include "mishell.hxx"
#include "commandline.hxx"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
    std::cout << Prompt().get() << "$ " << std::flush;
    CommandLine cl(std::cin);
    std::string directoryStr = path.getDirectory(path.find(cl.getCommand()));
    char dir[directoryStr.size()];
    strcpy(dir, directoryStr.c_str());
    int pid = fork();
    execv(dir, cl.getArgVector());
    if(!cl.noAmpersand()) {
      int* filler = NULL;
      waitpid(pid, filler, 5);
    }
  }
}
