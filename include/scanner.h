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

  static std::unordered_map<std::string, TokenType> initializeKeywords();

private:
  int start;
  int current;
  int line;

  static const std::unordered_map<std::string, TokenType> keywords;

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
