#ifndef TOKEN_H
#define TOKEN_H

#include "tokenType.h"
#include <variant>

using Object = std::variant<std::nullptr_t, bool, double, std::string>;

class Token {
public:
  const TokenType type;
  const std::string lexeme;
  const Object literal;
  const int line;

  Token(TokenType type, std::string lexeme, Object literal, int line);

  std::string toString();
};

#endif