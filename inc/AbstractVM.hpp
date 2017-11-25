#ifndef __ABSTRACTVM_HPP
# define __ABSTRACTVM_HPP

# include <iostream>

//AbstractVM is a stack based virtual machine. Whereas the stack is an actual stack or
//another container that behaves like a stack is up to you. Whatever the container, it MUST
//only contain pointers to the abstract type IOperand.

//todo унаследоваться от стека, прикрутить итератор

class AbstractVM {
    enum Work {RUN, STOP} work;
public:
    AbstractVM();
    ~AbstractVM();
    AbstractVM(const AbstractVM &avm);
    AbstractVM &operator=(AbstractVM &avm);

    //запиливаем здесь считываетль из консоли и файла, а там будет видно
    void run();
};


#endif