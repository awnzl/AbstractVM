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

//AbstractVM is a stack based virtual machine. Whereas the stack is an actual stack or
//another container that behaves like a stack is up to you. Whatever the container, it MUST
//only contain pointers to the abstract type IOperand.

//todo унаследоваться от стека, прикрутить итератор?

class AbstractVM {
    enum Work {RUN, STOP} _work;
    std::map<std::string, eOperandType> _types;
    std::map<AVMToken::TokenType, void (AbstractVM::*)()> _operations;
    AVMStack<const IOperand*> _avmStack;

    void push(std::string &operand, std::string &value);
    void pop();
    void dump();
    bool assert(std::string &operand, std::string &value);
    void add();
    void sub();
    void mul();
    void div();
    void mod();
    void print();
public:

    AbstractVM();
    ~AbstractVM();
    AbstractVM(const AbstractVM &avm);
    AbstractVM &operator=(AbstractVM &avm);

    //запиливаем здесь считываетль из консоли и файла, а там будет видно
    void run(char *);

};


#endif