#ifndef __AVMLEXER_HPP
# define __AVMLEXER_HPP

# include <string>
# include <regex>
# include <stdexcept>

//todo запилить .cpp файл



class AVMLexer {
    std::regex ptrnINSRT;

    AVMLexer () {
        ptrnINSRT = std::string("push ((int8\\([-]?\\d+\\))|(int16\\([-]?\\d+\\))|(int32\\([-]?\\d+\\))|"\
                                "(float\\([-]?\\d+\\.\\d+\\))|(double\\([-]?\\d+\\.\\d+\\)))|pop|dump|"\
                                "assert ((int8\\([-]?\\d+\\))|(int16\\([-]?\\d+\\))|(int32\\([-]?\\d+\\))|"\
                                "(float\\([-]?\\d+\\.\\d+\\))|(double\\([-]?\\d+\\.\\d+\\)))|add|sub|mul|"\
                                "div|mod|print|exit|(\n+)");
    }
    // AVMLexer (const AVMLexer &);// {}
    AVMLexer &operator=(AVMLexer &);// { return (*this); }

public:
    static AVMLexer &getLexer();

    std::string *lexIt(std::string &s) {
        std::string *res = NULL;

        if (std::regex_match(s, ptrnINSRT))
            res = new std::string(s);
        else
            throw (std::runtime_error("avm: invalid instruction"));

        return (res);
    }
};

AVMLexer &AVMLexer::getLexer() {
    static AVMLexer lexer;
    return (lexer);
}

#endif