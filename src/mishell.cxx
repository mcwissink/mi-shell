/**
 * CS-232
 * mishell.cxx
 * @author Mark Wissink and Ian Adams
 * @version 03/03/18
 */

#include "mishell.hxx"
#include "commandline.hxx"
#include "path.hxx"
#include "prompt.hxx"
#include "util.hxx"
#include <iostream>
#include <unistd.h>
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

    if (command == "") {
      // Do nothing
    } else if (command == "exit") { // Exit the shell
      break;
    } else if (command == "cd") { // Change directory
      std::string dir = cl.getArgVector(1);
      if (dir == ".." || dir == ".") {
        chdir((prompt.get() + "/" + dir).c_str());
      } else {
        chdir(dir.c_str());
      }
    } else if (command == "pwd") { // Print the working directory
      std::cout << prompt.get() << "\n" << std::flush;
    } else { // Run a command
      int prog_i = path.find(command);
      if (prog_i != -1) { // If we found a program
        // Do the forking we learned in class
        pid_t pid = fork();
        if (pid < 0) {
          std::cerr << "Fork failed" << std::endl;
        } else if (pid == 0) {
          // Execute the command
          execve((path.getDirectory(prog_i) + '/' + command).c_str(), cl.getArgVector().data(), NULL);
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
    }
  }
}
