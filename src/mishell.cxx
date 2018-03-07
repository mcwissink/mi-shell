/**
 * CS-232
 * mishell.cxx
 * @author Mark Wissink and Ian Adams
 * @version 03/03/18
 */

#include "mishell.hxx"
#include "util.hxx"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Runs and contains logic for the shell
 * @param none.
 * @return void.
 */
void MIShell::run() {
  /** Register signal handler so no zombies are created
   * https://linux.die.net/man/2/sigaction
   * http://www.microhowto.info/howto/reap_zombie_processes_using_a_sigchld_handler.html
   */
  signal(SIGCHLD, SIG_IGN);

  while(true) {
    // Initalize a path and prompt - this is probably not very efficient
    Prompt prompt;
    Path path;
    std::cout << prompt.get() << "$ " << std::flush;

    // Initialize the command line
    CommandLine cl(std::cin);
    std::string command = cl.getCommand();
    // Parse the command
    switch (parseCommand(command)) {
      case C_NONE: break; // Do nothing
      case C_EXIT: exit(0); break; // Exit the shell
      case   C_CD: changeDirectory(cl, prompt); break; // Change directory
      case  C_PWD: std::cout << prompt.get() << std::endl; break; // Print cwd
      case C_PROG: { // Run a program
        int programPath = path.find(command);
        if (programPath != -1) { // If we found a program
          // Do the forking we learned in class
          pid_t pid = fork();
          if (pid < 0) {
            std::cerr << "Fork failed" << std::endl;
          } else if (pid == 0) {
            // Execute the command
            execve((path.getDirectory(programPath) + '/' + command).c_str(), cl.getArgVector().data(), NULL);
          } else {
            // If there is an ampersand, the signal handler should clean it up
            if (cl.noAmpersand()) {
              // Reap the child
              waitpid(pid, NULL, 0);
            }
          }
        } else { // No program found
          std::cout << command << ": command not found" << std::endl;
        }
        break;
      }
    }
  }
}

void MIShell::changeDirectory(const CommandLine& cl, const Prompt& prompt) {
  std::string dir = cl.getArgVector(1);
  if (dir == ".." || dir == ".") {
    chdir((prompt.get() + "/" + dir).c_str());
  } else {
    chdir(dir.c_str());
  }
};

MIShell::Command MIShell::parseCommand(const std::string& command) {
  if (command == "exit") return C_EXIT;
  else if (command == "cd") return C_CD;
  else if (command == "pwd") return C_PWD;
  else if (command == "") return C_NONE;
  else return C_PROG;
}
