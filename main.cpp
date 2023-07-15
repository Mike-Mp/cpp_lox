#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Lox {
public:
  static bool hadError;

  static void error(int line, std::string message) { report(line, "", message); }

  static void runFile(const std::string &path) {
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
    std::cout << "Hello";
    std::cout << fileContent;
    hadError = true;
    run(fileContent);

    if (hadError) exit(65);
  }

  static void runPrompt() {
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

private:
  static void run(std::string source) {
    // Scanner scanner = Scanner{};
    // List<Token> tokens = scanner.scanTokens();
    // for (Token token : tokens) {
    //   std::cout >> token;
    // }
  }

  static void report(int line, std::string where, std::string message) {
    std::cout << "[line " << line << "] Error" << where << ": " << message;
    // hadError = true;
  }
};

int main(int argc, char *argv[]) {
  // std::cout << argc;
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
