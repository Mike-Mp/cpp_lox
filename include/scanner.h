#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include "tokenType.h"
#include <cmath>
#include <vector>

class Scanner {
public:
  std::string source;
  std::vector<Token> tokens;

  Scanner(std::string source);

  std::vector<Token> scanTokens();

private:
  int start;
  int current;
  int line;

  bool isAtEnd();

  void scanToken();

  void string();

  char advance();

  void addToken(TokenType type);

  void addToken(TokenType type, Object);

  bool match(char expected);

  char peek();

  bool isDigit(char c);

  void number();

  char peekNext();
};

#endif
