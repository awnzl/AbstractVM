// #include "AVMLexer.hpp"
#include "../inc/AVMLexer.hpp" //todo delete

unsigned long AVMLexer::count;

AVMLexer::AVMLexer () {
    _ptrnINSRT = std::string("push ((int8\\([-]?\\d+\\))|(int16\\([-]?\\d+\\))|(int32\\([-]?\\d+\\))|"\
                            "(float\\([-]?\\d+\\.\\d+\\))|(double\\([-]?\\d+\\.\\d+\\)))([ |\\t]*?;.*)?|"\
                            "pop([ |\\t]*?;.*)?|dump([ |\\t]*?;.*)?|assert ((int8\\([-]?\\d+\\))|"\
                            "(int16\\([-]?\\d+\\))|(int32\\([-]?\\d+\\))|(float\\([-]?\\d+\\.\\d+\\))|"\
                            "(double\\([-]?\\d+\\.\\d+\\)))([ |\\t]*?;.*)?|add([ |\\t]*?;.*)?|"\
                            "sub([ |\\t]*?;.*)?|mul([ |\\t]*?;.*)?|div([ |\\t]*?;.*)?|mod([ |\\t]*?;.*)?|"\
                            "print([ |\\t]*?;.*)?|exit([ |\\t]*?;.*)?|(\n+)|( +)|;;");
    _ptrnCOMM = std::string("([ |\\t]*?;.*)?");
}

AVMLexer &AVMLexer::getLexer() {
    static AVMLexer lexer;
    return (lexer);
}

AVMToken *AVMLexer::lexIt(std::string &s) {
    AVMToken *res = NULL;
    
    if (std::regex_match(s, _ptrnINSRT)) {
        count++;
        res = parseIt(s);
    } else if (std::regex_match(s, _ptrnCOMM)) {
        count++;
        return (res);
    } else {
        std::stringstream sss;
        sss << "avm: Line " << ++count << ": An instruction is unknown";
        throw (std::runtime_error(sss.str()));
        sss.clear();
        sss.str(std::string());
    }

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
    ";;",
*/