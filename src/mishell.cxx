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
  prevDir = "\0"; //initialize previous directory to null
  while(true) {
    // Initalize a path and prompt - not efficient, but easy
    Prompt prompt;
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
    if (command == "exit"){
      exit(0); // Exit the shell
    } else if (command == "pwd"){
      std::cout << prompt.get() << std::endl; // Print cwd
    } else if (command == "cd") {
      changeDirectory(cl.getArgVector(1), prompt); // Change directory
    } else {
      runProgram(cl, command); // Run a program
    }
  }
}

/* Executes all non-shell commands
 * @param CommandLine, command
 * @return void
 */
void MIShell::runProgram(const CommandLine& cl, const std::string& command) {
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
      util::syserr(execve(path.buildPath(path.getDirectory(i), command).c_str(), argv.data(), NULL) == -1);
    } else { // I am the parent
      if (cl.noAmpersand()) {
        util::syserr(waitpid(pid, NULL, 0) == -1);
      }
    }
  } else { // No program found
    std::cout << "Error: "<< command << ": command not found" << std::endl;
  }
}


/**
 * Changes directory
 * @param commandline and prompt references
 */
void MIShell::changeDirectory(const std::string& dir, const Prompt prompt) {
  if (dir == "" || dir == "~") { //go to home directory
    prevDir = prompt.get();
    util::syserr(chdir(getenv("HOME")) == -1);
  } else if (dir == "-") { //go to previous directory
    if(prevDir != "\0") {
      util::syserr(chdir(prevDir.c_str()) == -1);
    } else {
      std::cerr << "-bash: cd: OLDPWD not set" << std::endl;
    }
  } else { //go to whatever directory is specified
    prevDir = prompt.get();
    util::syserr(chdir(dir.c_str()) == -1);
  }
};
