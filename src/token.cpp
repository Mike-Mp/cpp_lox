#include <iostream>
#include <sstream>
#include <string>
#include <variant>

#include "../include/tokenType.h"

using std::string;

using Object = std::variant<std::nullptr_t, bool, double, std::string>;

class Token {
public:
  const TokenType type;
  const std::string lexeme;
  const Object literal;
  const int line;

  Token(TokenType type, std::string lexeme, Object literal, int line)
      : type(type), lexeme(lexeme), literal(literal), line(line) {}

  string toString() {
    std::stringstream ss;
    ss << type << " " << lexeme << " " << objectToString(literal);
    return ss.str();
  };

private:
  std::string objectToString(const Object &literal) {
    std::ostringstream oss;

    std::visit([&oss](const auto &value) { oss << value; }, literal);
    return oss.str();
  }
};