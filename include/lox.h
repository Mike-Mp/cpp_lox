#ifndef MAIN_H
#define MAIN_H

#include <string>
class Lox {
public:
  static bool hadError;

  static void error(int line, std::string message);

  static void runFile(const std::string &path);

  static void runPrompt();

private:
  static void run(std::string source);

  static void report(int line, std::string where, std::string message);
};

#endif
