/**
 * CS-232
 * mishell.cxx
 * @author Mark Wissink and Ian Adams
 * @version 03/03/18
 */

#include "mishell.hxx"
#include "commandline.hxx"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

static void child_handler(int sig){
  int status;
  pid_t pid = waitpid(-1, &status, WNOHANG);
  std::cout << "background child: " <<pid << std::endl;
}

/**
 * Runs and contains logic for the shell
 * @param none.
 * @return void.
 */
void MIShell::run() {
  // Setup signal handler
  struct sigaction handler;
  handler.sa_handler = child_handler;
  sigaction(SIGCHLD, &handler, NULL);

  {
    std::cout << Prompt().get() << "$ " << std::flush;
    CommandLine cl(std::cin);
    std::string program = cl.getCommand();
    int index = path.find(program);
    std::string directoryStr = path.getDirectory(index);
    std::cout << "program: " << program << ", index: " << index <<  directoryStr << std::endl;
    char *dir = strdup(std::string(directoryStr + '/' + program).c_str());
    std::cout << dir << std::endl;
    char *argv[] = {"ls", NULL};

    std::cout<< "This is the directory: " << dir << std::endl;



    pid_t pid = fork();
    std::cout<< "We forked the children" << std::endl;
    int status;

    if (pid < 0) {
      std::cout << "Fork failed" << std::endl;
    } else if (pid == 0) {
      std::cout << "I am the child!" << std::endl;
      execve(dir, argv, NULL);
    } else {
      if (cl.noAmpersand()) {
        std::cout << " -- waiting" << std::endl;
        pid_t child = waitpid(pid, &status, 0);
        std::cout << "-- My child: " << child << " returned to me with status: " << status << std::endl;
      }
    }
  }
}
