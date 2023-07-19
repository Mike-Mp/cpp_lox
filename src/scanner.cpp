#include <concepts>
#include <string>
#include <unordered_map>
#include <vector>

#include "../include/lox.h"
#include "../include/scanner.h"
#include "../include/token.h"
#include "../include/tokenType.h"

Scanner::Scanner(std::string source)
    : source(source), start(0), current(0), line(1) {}

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.push_back(Token{END_OF_FILE, "", nullptr, line});
  return tokens;
}

std::unordered_map<std::string, TokenType> Scanner::keywords = {
   {"and", AND},
    {"class", CLASS},
    {"else", ELSE},
    {"false", FALSE},
    {"for", FOR},
    {"fun", FUN},
    {"if", IF},
    {"nil", NIL},
    {"or", OR},
    {"print", PRINT},
    {"return", RETURN},
    {"super", SUPER},
    {"this", THIS},
    {"true", TRUE},
    {"var", VAR},
    {"while", WHILE}
};

bool Scanner::isAtEnd() { return current >= source.length(); }

void Scanner::scanToken() {
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
    } else if (isAlpha(c)) {
      identifier();
    } else {
      Lox::error(line, "Unexpected character.");
    }
    break;
  }
}

void Scanner::identifier() {
  while (isAlphaNumeric(peek()))
    advance();

  addToken(IDENTIFIER);
  std::string text = source.substr(start, current);
  auto it = Scanner::keywords.find(text);

  TokenType type = (it != Scanner::keywords.end()) ? it->second : IDENTIFIER;
  addToken(type);
}

void Scanner::string() {
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
  std::string value = source.substr(start + 1, current - start - 2);
  addToken(STRING, value);
}

char Scanner::advance() { return source[current++]; }

void Scanner::addToken(TokenType type) { addToken(type, nullptr); }

void Scanner::addToken(TokenType type, Object literal) {
  std::string text = source.substr(start, current - start);
  tokens.push_back(Token{type, text, literal, line});
}

bool Scanner::match(char expected) {
  if (isAtEnd())
    return false;
  if (source[current] != expected)
    return false;

  current++;
  return true;
}

char Scanner::peek() {
  if (isAtEnd())
    return '\0';
  return source[current];
}

bool Scanner::isDigit(char c) { return c >= '0' && c <= '9'; }

void Scanner::number() {
  while (isDigit(peek()))
    advance();

  if (peek() == '.' && isDigit(peekNext())) {
    advance();

    while (isDigit(peek()))
      advance();
  }

  double numberValue = std::stod(source.substr(start, current - start));
  addToken(NUMBER, numberValue);
}

char Scanner::peekNext() {
  if (current + 1 >= source.length())
    return '\0';
  return source[current + 1];
}

bool Scanner::isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); }
