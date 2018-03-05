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

void handler(int sig) {
  int status;
  pid_t pid = waitpid(-1, &status, WNOHANG);
  if (pid > 0){
    std::cout << "-- My background child: " << pid << " returned to me with status: " << status << std::endl;
  }
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
    std::string program("ls");
    int index = path.find(program);
    std::string directoryStr = path.getDirectory(index);
    std::cout << "program: " << program << ", index: " << index <<  directoryStr << std::endl;
    char *dir = strdup(directoryStr.c_str());
    char *argv[] = {"ls", NULL};
    char *env[] = { "HOME=/usr/home", "LOGNAME=home", NULL };
    std::cout<< "This is the directory: " << dir << std::endl;
    //signal(SIGCHLD, handler);

    pid_t pid = fork();
    std::cout<< "We forked the children" << std::endl;
    int status;

    if (pid < 0) {
      std::cout << "-- Fork failed" << std::endl;
    } else if (pid == 0) {
      std::cout << "I am the child!" << std::endl;
      if (execve("/bin/ls", argv, NULL) == -1) {
 	perror("htaouht");
      }
      std::cout << "This should not happen" << std::endl;
    } else {
      if (cl.noAmpersand()) {
        std::cout << " -- waiting" << std::endl;
        pid_t child = waitpid(pid, &status, 0);
        std::cout << "-- My child: " << child << " returned to me with status: " << status << std::endl;
      }
    }
  }
}
