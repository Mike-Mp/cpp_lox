#include <iostream>
#include <sstream>
#include <string>
#include <variant>

#include "../include/tokenType.h"
#include "../include/token.h"

using std::string;

Token::Token(TokenType type, std::string lexeme, Object literal, int line)
    : type(type), lexeme(lexeme), literal(literal), line(line) {}

string Token::toString() {
  std::stringstream ss;
  ss << type << " " << lexeme << " " << objectToString(literal);
  return ss.str();
};

string Token::objectToString(const Object &literal) {
  std::ostringstream oss;

  std::visit([&oss](const auto &value) { oss << value; }, literal);
  return oss.str();
};