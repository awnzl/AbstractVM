#ifndef __ABSTRACTVM_HPP
# define __ABSTRACTVM_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <map>
# include "OperandsFactory.hpp"
# include "AVMLexer.hpp"
# include "AVMToken.hpp"
# include "AVMStack.hpp"

class AbstractVM {
    enum Work {RUN, STOP} _work;
    std::map<std::string, eOperandType> _types;
    std::map<AVMToken::TokenType, void (AbstractVM::*)()> _operations;
    AVMStack<const IOperand*> _avmStack;

    void push(std::string &operand, std::string &value);
    void pop();
    void dump();
    void assert(std::string &operand, std::string &value);
    void add();
    void sub();
    void mul();
    void div();
    void mod();
    void print();
    void exit();

    void dup();
    void clean();
    void swap();

    void fileRead(char *in);
    void consoleRead();

public:

    AbstractVM();
    ~AbstractVM();
    AbstractVM(const AbstractVM &avm);
    AbstractVM &operator=(AbstractVM &avm);

    void run(char *);

};


#endif