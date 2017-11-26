#include "AVMLexer.hpp"

AVMLexer::AVMLexer () {
    ptrnINSRT = std::string("push ((int8\\([-]?\\d+\\))|(int16\\([-]?\\d+\\))|(int32\\([-]?\\d+\\))|"\
                            "(float\\([-]?\\d+\\.\\d+\\))|(double\\([-]?\\d+\\.\\d+\\)))|pop|dump|"\
                            "assert ((int8\\([-]?\\d+\\))|(int16\\([-]?\\d+\\))|(int32\\([-]?\\d+\\))|"\
                            "(float\\([-]?\\d+\\.\\d+\\))|(double\\([-]?\\d+\\.\\d+\\)))|add|sub|mul|"\
                            "div|mod|print|exit|(\n+)");
}

AVMLexer &AVMLexer::getLexer() {
    static AVMLexer lexer;
    return (lexer);
}

std::string *AVMLexer::lexIt(std::string &s) {
    std::string *res = NULL;

    if (std::regex_match(s, ptrnINSRT))
        res = new std::string(s);
    else
        throw (std::runtime_error("avm: invalid instruction"));

    return (res);
}