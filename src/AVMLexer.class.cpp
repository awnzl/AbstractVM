#include "../inc/AVMLexer.hpp"

AVMLexer::AVMLexer () {
    ptrnINSRT = std::string("push ((int8\\([-]?\\d+\\))|(int16\\([-]?\\d+\\))|(int32\\([-]?\\d+\\))|"\
                            "(float\\([-]?\\d+\\.\\d+\\))|(double\\([-]?\\d+\\.\\d+\\)))|pop|dump|"\
                            "assert ((int8\\([-]?\\d+\\))|(int16\\([-]?\\d+\\))|(int32\\([-]?\\d+\\))|"\
                            "(float\\([-]?\\d+\\.\\d+\\))|(double\\([-]?\\d+\\.\\d+\\)))|add|sub|mul|"\
                            "div|mod|print|exit|(\n+)");
    ptrnENDC = std::string(";.+|;;");
}

AVMLexer &AVMLexer::getLexer() {
    static AVMLexer lexer;
    return (lexer);
}

AVMToken *AVMLexer::lexIt(std::string &s) {
    AVMToken *res = NULL;

    //todo допилить обработку комментариев и конца ввода из консоли
    //в частности, нужен ввод комментов после каждой из строк, также в начале строки
    //
    if (std::regex_match(s, ptrnINSRT))
        res = parseIt(s);
    else if (std::regex_match(s, ptrnENDC))
        return (res);
    else
        throw (std::runtime_error("avm: invalid instruction"));

    return (res);
}

AVMToken *AVMLexer::parseIt(std::string &s) {
    AVMToken *res = new AVMToken();

    res->type = res->m[s.substr(0, (s.find(" ") == std::string::npos) ? s.length() : s.find(" "))];
    if (res->type == AVMToken::TokenType::PUSH || res->type == AVMToken::TokenType::ASSERT) {
        res->operand = s.substr(s.find(" ") + 1, s.find("(") - 1 - s.find(" "));
        res->value = s.substr(s.find("(") + 1, s.find(")") - 1 - s.find("("));
    }

    return (res);
}


/*
    "push int8(42)",
    "push int8(-42)",
    "push int16(42)",
    "push int32(42)",
    "push float(44.55)",
    "push double(42.42)",
    "assert float(42.42)",
    "assert double(-42.42)",
    "assert int8(42)",
    "assert int16(42)",
    "assert int32(42)",
    "add",
    "sub",
    "mul",
    "dump",
    "pop",
    "print",
    "mod",
    "div",
    "exit",
*/