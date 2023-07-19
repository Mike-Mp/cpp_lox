#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include "tokenType.h"
#include <cmath>
#include <unordered_map>
#include <vector>

class Scanner {
public:
  std::string source;
  std::vector<Token> tokens;

  Scanner(std::string source);

  std::vector<Token> scanTokens();

private:
  unsigned int start;
  unsigned int current;
  int line;

  static std::unordered_map<std::string, TokenType> keywords;

  bool isAtEnd();

  void scanToken();

  void identifier();

  void string();

  char advance();

  void addToken(TokenType type);

  void addToken(TokenType type, Object);

  bool match(char expected);

  char peek();

  bool isDigit(char c);

  void number();

  char peekNext();

  bool isAlpha(char c);

  bool isAlphaNumeric(char c);
};

#endif
