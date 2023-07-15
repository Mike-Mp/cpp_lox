#include <vector>
#include <string>

#include "token.h"

class Scanner {
   private: 
    std::string source;
    std::vector<Token> tokens = std::vector<Token>();
};
