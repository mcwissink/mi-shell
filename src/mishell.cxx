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

/**
 * Runs and contains logic for the shell
 * @param none.
 * @return void.
 */
void MIShell::run() {
  /** Register signal handler
   * https://linux.die.net/man/2/sigaction
   * http://www.microhowto.info/howto/reap_zombie_processes_using_a_sigchld_handler.html
   */
   /*
  struct sigaction sa;
  sa.sa_handler = SIG_IGN;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
  sigaction(SIGCHLD, &sa, 0);
  */
  signal(SIGCHLD, SIG_IGN);

  // Run the shell
  while(true){
    std::cout << Prompt().get() << std::flush;
    CommandLine cl(std::cin);

    if((std::string)cl.getCommand() == "cd") {
      chdir((Prompt().getCwd() + "/" + (std::string)cl.getArgVector(1)).c_str());
    } else if((std::string)cl.getCommand() == "exit") {
      break;
    } else if((std::string)cl.getCommand() == "pwd") {
      std::cout << Prompt().getCwd() << "\n" << std::flush;
    } else {
      pid_t pid = fork();
      int status;

      if (pid < 0) {
        //std::cout << "Fork failed" << std::endl;
      } else if (pid == 0) {
        //std::cout << "I am the child!" << std::endl;
        execve(path.getPath(cl.getCommand()).c_str(), cl.getArgVector().data(), NULL);
      } else {
        if (cl.noAmpersand()) {
          //std::cout << " -- waiting" << std::endl;
          //pid_t child =
          waitpid(pid, &status, 0);
          //std::cout << "-- My child: " << child << " returned to me with status: " << status << std::endl;
        }
      }
    }
  }
}
