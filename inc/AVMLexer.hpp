#ifndef __AVMLEXER_HPP
# define __AVMLEXER_HPP

# include <string>
# include <regex>
# include <stdexcept>
# include "AVMToken.hpp"

class AVMLexer {
    std::regex ptrnINSRT;
    std::regex ptrnENDC;

    AVMLexer ();
    AVMLexer &operator=(AVMLexer &);
    AVMToken *parseIt(std::string &s);
public:
    static AVMLexer &getLexer();
    AVMToken *lexIt(std::string &s);
};

static AVMLexer &getLexer();

#endif