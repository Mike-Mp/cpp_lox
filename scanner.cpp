#include <string>
#include <vector>

#include "lox.h"
#include "token.h"
#include "tokenType.h"

class Scanner {
private:
  std::string source;
  std::vector<Token> tokens = std::vector<Token>();
  int start = 0;
  int current = 0;
  int line = 1;

  Scanner(std::string source) { this->source = source; }

  std::vector<Token> scanTokens() {
    while (!isAtEnd()) {
      start = current;
      scanToken();
    }

    tokens.push_back(Token{END_OF_FILE, "", nullptr, line});
    return tokens;
  }

  bool isAtEnd() { return current >= source.length(); }

  void scanToken() {
    char c = advance();
    switch (c) {
    case '(':
      addToken(LEFT_PAREN);
      break;
    case ')':
      addToken(RIGHT_PAREN);
      break;
    case '{':
      addToken(LEFT_BRACE);
      break;
    case '}':
      addToken(RIGHT_BRACE);
      break;
    case ',':
      addToken(COMMA);
      break;
    case '.':
      addToken(DOT);
      break;
    case '-':
      addToken(MINUS);
      break;
    case '+':
      addToken(PLUS);
      break;
    case ';':
      addToken(SEMICOLON);
      break;
    case '*':
      addToken(STAR);
      break;

    case '!':
      addToken(match('=') ? BANG_EQUAL : BANG);
      break;
    case '=':
      addToken(match('=') ? EQUAL_EQUAL : EQUAL);
      break;
    case '<':
      addToken(match('=') ? LESS_EQUAL : LESS);
      break;
    case '>':
      addToken(match('=') ? GREATER_EQUAL : GREATER);
      break;
    case '/':
      if (match('/')) {
        while (peek() != '\n' && !isAtEnd())
          advance();
      } else {
        addToken(SLASH);
      }
      break;

    case ' ':
    case '\r':
    case '\t':
      // Ignore whitespace.
      break;

    case '\n':
      line++;
      break;

    case '"':
      string();
      break;
    default:

      if (isDigit(c)) {
        number();
      } else {
        Lox::error(line, "Unexpected character.");
      }
      break;
    }
  }

  void string() {
    while (peek() != '"' && !isAtEnd()) {
      if (peek() == '\n')
        line++;
      advance();
    }

    if (isAtEnd()) {
      Lox::error(line, "Unterminated string");
      return;
    }

    advance();
    std::string value = source.substr(start + 1, current - 1);
    addToken(STRING, value);
  }

  char advance() { return source[current++]; }

  void addToken(TokenType type) { addToken(type, nullptr); }

  void addToken(TokenType type, Object literal) {
    std::string text = source.substr(start, current);
    tokens.push_back(Token{type, text, literal, line});
  }

  bool match(char expected) {
    if (isAtEnd())
      return false;
    if (source[current] != expected)
      return false;

    current++;
    return true;
  }

  char peek() {
    if (isAtEnd())
      return '\0';
    return source[current];
  }

  bool isDigit(char c) { return c >= '0' && c <= '9'; }

  void number() {
    while (isDigit(peek()))
      advance();

    if (peek() == '.' && isDigit(peekNext())) {
      advance();

      while (isDigit(peek()))
        advance();
    }

    addToken(NUMBER, source.substr(start, current));
  }

  char peekNext() {
    if (current + 1 >= source.length())
      return '\0';
    return source[current + 1];
  }
};
