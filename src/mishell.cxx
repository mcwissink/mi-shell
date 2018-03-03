#include "mishell.hxx"
#include <iostream>

MIShell::MIShell() {
  myPath = new Path();
  myPrompt = new Prompt(); 
}

void MIShell::run() {
	std::cout << "Press Enter to exit...";
	std::cin.get();
}

