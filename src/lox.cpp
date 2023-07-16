#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/lox.h"
#include "../include/scanner.h"
#include "../include/token.h"

bool Lox::hadError = false;

void Lox::error(int line, std::string message) { report(line, "", message); }

void Lox::runFile(const std::string &path) {
  std::ifstream file{path};

  if (!file) {
    std::cerr << "Failed to open file: " << path << std::endl;
    return;
  }

  std::string myline;
  std::getline(file, myline);

  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string fileContent = buffer.str();
  hadError = false;
  run(fileContent);

  if (hadError)
    exit(65);
}

void Lox::runPrompt() {
  std::string line;

  for (;;) {
    std::cout << "> ";
    std::getline(std::cin, line);

    if (std::cin.eof()) {
      break;
    }

    run(line);
    hadError = false;
  }
}

void Lox::run(std::string source) {
  Scanner scanner = Scanner{source};
  std::vector<Token> tokens = scanner.scanTokens();

  for (Token token : tokens) {
    std::cout << token.toString();
  }
}

void Lox::report(int line, std::string where, std::string message) {
  std::cout << "[line " << line << "] Error" << where << ": " << message;
  hadError = true;
}
