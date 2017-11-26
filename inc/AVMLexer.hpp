#ifndef __AVMLEXER_HPP
# define __AVMLEXER_HPP

# include <string>
# include <regex>
# include <stdexcept>

class AVMLexer {
    std::regex ptrnINSRT;

    AVMLexer ();
    AVMLexer &operator=(AVMLexer &);

public:
    static AVMLexer &getLexer();
    std::string *lexIt(std::string &s);
};

static AVMLexer &getLexer();

#endif