#ifndef __AVMTOKEN_HPP
# define __AVMTOKEN_HPP

# include <string>

struct AVMToken {
    enum TokenType {INSIRT, EXTRACT, OPERATE, COMMENT, EXIT} type; 
    std::string operation;
    std::string operand;
    std::string value;
};

#endif