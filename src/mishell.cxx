#include "mishell.hxx"
#include <iostream>

MIShell::MIShell() {
  path = Path();
  std::cout << Prompt().get() << std::endl; 
}

void MIShell::run() {
  //std::cout << "Press Enter to exit...";
  //std::cin.get();
  while(1) {
  }
}

