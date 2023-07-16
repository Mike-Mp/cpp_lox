#include <iostream>

#include "../include/lox.h"
#include "../include/scanner.h"


int main(int argc, char *argv[]) {
  std::cout << argc;
  if (argc > 2) {
    std::cout << "Usage: clox [script]";
    exit(64);
  } else if (argc == 2) {
    Lox::runFile(argv[1]);
  } else {
    Lox::runPrompt();
  }

  return 0;
}
