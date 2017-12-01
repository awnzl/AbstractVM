#ifndef __AVMLEXER_HPP
# define __AVMLEXER_HPP

# include <string>
# include <sstream>
# include <regex>
# include <stdexcept>
# include "AVMToken.hpp"
# include "AVMException.hpp"

class AVMLexer {
    std::regex _ptrnINSRT;
    std::regex _ptrnCOMM;
    std::regex _ptrnTP;
    static unsigned long count;
    std::stringstream ss;
    
    AVMLexer ();
    AVMToken *parseIt(std::string &s);

public:
    AVMLexer(const AVMLexer &) = delete;
    AVMLexer &operator=(AVMLexer &) = delete;
    static AVMLexer &getLexer();
    static void resetCount();
    AVMToken *lexIt(std::string &s);
};

static unsigned long count;

static AVMLexer &getLexer();

#endif