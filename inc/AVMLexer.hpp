#ifndef __AVMLEXER_HPP
# define __AVMLEXER_HPP

# include <string>
# include <regex>
# include <iostream>//todo no need for this include here /debug
# include <sstream>
# include "AVMToken.hpp"

//todo запилить .cpp файл



class AVMLexer {
    AVMLexer () {}
    // AVMLexer (const AVMLexer &);// {}
    AVMLexer &operator=(AVMLexer &);// { return (*this); }

public:
    static AVMLexer &getLexer();
    AVMToken *lexIt(std::string &s) {
//        std::regex ptrnSEP("[\n]+");
//        std::regex ptrnZ("[-]?[0..9]+.[0..9]+");
//        std::regex ptrnN("[-]?[0..9]+");
//        std::regex ptrnVALUE("int8(N)|int16(N)|int32(N)|float(Z)|double(Z)");
        
        
        //todo засунуть эту срань в конструктор по умолчанию, чтобы оно не создавало при
        //каждом вызове функции
        std::stringstream ss;

        ss << "push ((int8\\([-]?\\d+\\))|(int16\\([-]?\\d+\\))|(int32\\([-]?\\d+\\))"
           << "|(float\\([-]?\\d+\\.\\d+\\))|(double\\([-]?\\d+\\.\\d+\\)))|pop|dump|"
           << "assert ((int8\\([-]?\\d+\\))|(int16\\([-]?\\d+\\))|(int32\\([-]?\\d+\\))"
           << "|(float\\([-]?\\d+\\.\\d+\\))|(double\\([-]?\\d+\\.\\d+\\)))|add|sub|mul"
           << "|div|mod|print|exit|(\n+)";
        
        std::regex ptrnINSRT(ss.str());

        std::cout << s << " ---> " << std::regex_match(s, ptrnINSRT) << std::endl;
        return (NULL);
    }
};

AVMLexer &AVMLexer::getLexer() {
    static AVMLexer lexer;
    return (lexer);
}

#endif