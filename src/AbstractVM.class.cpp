#include "AbstractVM.hpp"

AbstractVM::AbstractVM() : work(RUN) {}

AbstractVM::~AbstractVM() {}

AbstractVM::AbstractVM(const AbstractVM &avm) {
    this->work = avm.work;
    //...
}

AbstractVM &AbstractVM::operator=(AbstractVM &avm) {
    this->work = avm.work;
    //...
    return (*this);
}

//запиливаем здесь считываетль из консоли и файла, а там будет видно
void AbstractVM::run() {
    //получает отвалидированные данные и начинает свое дело...
    //нужно обрабатывать эксепшены, чтобы выполнение программы не прерывалось на этом,
    //как в калькуляторе dc
    /*
    AbstractVM is a stack based virtual machine. Whereas the stack is an actual stack or
    another container that behaves like a stack is up to you. Whatever the container, it MUST
    only contain pointers to the abstract type IOperand.
    */
    while (work == RUN) {
        
        if (true)
            std::cout << "All works\n";
            work = STOP;
    }
}