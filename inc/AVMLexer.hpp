#ifndef __AVMLEXER_HPP
# define __AVMLEXER_HPP

# include <string>
# include <regex>
# include <stdexcept>
# include "AVMToken.hpp"

class AVMLexer {
    std::regex _ptrnINSRT;
    std::regex _ptrnENDC;
    
    AVMLexer ();
    AVMToken *parseIt(std::string &s);

public:
    AVMLexer(const AVMLexer &) = delete;
    AVMLexer &operator=(AVMLexer &) = delete;
    static AVMLexer &getLexer();
    AVMToken *lexIt(std::string &s);
};

static AVMLexer &getLexer();

#endif