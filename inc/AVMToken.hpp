#ifndef __AVMTOKEN_HPP
# define __AVMTOKEN_HPP

# include <string>
# include <map>

struct AVMToken {
    enum TokenType {PUSH, ASSERT, ADD, SUB, MUL, MOD, DIV, DUMP, POP, PRINT, EXIT} type;
    std::map<std::string, TokenType> m = {
        {"push", TokenType::PUSH},
        {"assert", TokenType::ASSERT},
        {"add", TokenType::ADD},
        {"sub", TokenType::SUB},
        {"mul", TokenType::MUL},
        {"mod", TokenType::MOD},
        {"div", TokenType::DIV},
        {"dump", TokenType::DUMP},
        {"pop", TokenType::POP},
        {"print", TokenType::PRINT},
        {"exit", TokenType::EXIT}
    };
    std::string operand;
    std::string value;
};

#endif