#include "AVMLexer.hpp"

unsigned long AVMLexer::count;

AVMLexer::AVMLexer () {
    _ptrnINSRT = std::regex("push ((int8\\([-]?\\d+\\))|(int16\\([-]?\\d+\\))|(int32\\([-]?\\d+\\))|"\
                            "(float\\([-]?\\d+\\.\\d+\\))|(double\\([-]?\\d+\\.\\d+\\)))([ |\\t]*?;.*)?|"\
                            "pop([ |\\t]*?;.*)?|dump([ |\\t]*?;.*)?|assert ((int8\\([-]?\\d+\\))|"\
                            "(int16\\([-]?\\d+\\))|(int32\\([-]?\\d+\\))|(float\\([-]?\\d+\\.\\d+\\))|"\
                            "(double\\([-]?\\d+\\.\\d+\\)))([ |\\t]*?;.*)?|add([ |\\t]*?;.*)?|"\
                            "sub([ |\\t]*?;.*)?|mul([ |\\t]*?;.*)?|div([ |\\t]*?;.*)?|mod([ |\\t]*?;.*)?|"\
                            "print([ |\\t]*?;.*)?|exit([ |\\t]*?;.*)?|(\n+)|( +)|;;|swap([ |\\t]*?;.*)?|"\
                            "dup([ |\\t]*?;.*)?|clean([ |\\t]*?;.*)?");
    _ptrnCOMM = std::regex("([ |\\t]*?;.*)?");
    _ptrnTP = std::regex("push|pop|dump|assert|add|sub|mul|div|mod|print|exit|;;|swap|dup|clean");
}

AVMLexer &AVMLexer::getLexer() {
    static AVMLexer lexer;
    return (lexer);
}

AVMToken *AVMLexer::lexIt(std::string &s) {
    if (std::regex_match(s, _ptrnINSRT)) {
        count++;
        return (parseIt(s));
    } else if (std::regex_match(s, _ptrnCOMM)) {
        count++;
        return (NULL);
    } else {
        ss.clear();
        ss.str(std::string());
        ss << "avm: Line " << ++count << ": An instruction is unknown";
        throw (AVMException(ss.str()));
    }

    return (NULL);
}

void AVMLexer::resetCount() {
    count = 0;
}

AVMToken *AVMLexer::parseIt(std::string &s) {
    AVMToken *res = new AVMToken();

    std::smatch match;
    std::regex_search(s, match, _ptrnTP);
    res->type = res->m[match.str()];
    if (res->type == AVMToken::TokenType::PUSH || res->type == AVMToken::TokenType::ASSERT) {
        res->operand = s.substr(s.find(" ") + 1, s.find("(") - 1 - s.find(" "));
        res->value = s.substr(s.find("(") + 1, s.find(")") - 1 - s.find("("));
    }

    return (res);
}