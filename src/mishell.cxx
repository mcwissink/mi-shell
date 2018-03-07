/**
 * CS-232
 * mishell.cxx
 * @author Mark Wissink and Ian Adams
 * @version 03/03/18
 */

#include "mishell.hxx"
#include "util.hxx"
#include <iostream>
extern "C" {
  #include <unistd.h>
  #include <stdlib.h>
  #include <stdio.h>
  #include <sys/types.h>
  #include <sys/wait.h>
}

/**
 * Runs and contains logic for the shell
 * @param none.
 * @return void.
 */
void MIShell::run() {
  while(true) {
    // Initalize a path and prompt - not efficient, but easy
    Prompt prompt;
    Path path;
    std::cout << prompt.get() << "$ " << std::flush;

    /** wait on any background processes that could have terminated
     *  WNOHANG means that waitpid won't block
     * while loop ensure if multiple process terminated, they all get waited
     */
    while (waitpid(-1, NULL, WNOHANG) > 0);

    // Initialize the command line and get the command
    CommandLine cl(std::cin);
    std::string command = cl.getCommand();

    // Parse the command
    switch (parseCommand(command)) {
      case C_NONE: break; // Do nothing
      case C_EXIT: exit(0); break; // Exit the shell
      case  C_PWD: std::cout << prompt.get() << std::endl; break; // Print cwd
      case   C_CD: changeDirectory(cl, prompt); break; // Change directory
      case C_PROG: { // Run a program
        int i = path.find(command);
        if (i != -1) { // If we found a program
          pid_t pid;
          // Do the forking we learned in class
          util::syserr((pid = fork()) == -1);
          if (pid == 0) { // I am the child
            // Get the arg vector
            std::vector<char*> argv;
            cl.getArgVector(argv);
            // Execute the command
            util::syserr(execve(path.buildPath(path.getDirectory(i), command).c_str(),
                         argv.data(), NULL) == -1);
          } else { // I am the parent
            if (cl.noAmpersand()) {
              util::syserr(waitpid(pid, NULL, 0) == -1);
            }
          }
        } else { // No program found
          std::cout << "Error: "<< command << ": command not found" << std::endl;
        }
        break;
      }
    }
  }
}

/**
 * Changes directory
 * @param commandline and prompt references
 */
void MIShell::changeDirectory(const CommandLine& cl, const Prompt& prompt) {
  std::string dir = cl.getArgVector(1);
  if (dir == ".." || dir == ".") {
    util::syserr(chdir((prompt.get() + "/" + dir).c_str()) == -1);
  } else {
    util::syserr(chdir(dir.c_str()) == -1);
  }
};

/**
 * Allows use of switch on strings
 * @param a command
 * @return Command enum for a switch
 */
MIShell::Command MIShell::parseCommand(const std::string& command) {
  if (command == "exit") return C_EXIT;
  else if (command == "cd") return C_CD;
  else if (command == "pwd") return C_PWD;
  else if (command == "") return C_NONE;
  else return C_PROG;
}
