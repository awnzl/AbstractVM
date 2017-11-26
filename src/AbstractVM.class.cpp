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
void AbstractVM::run(char *in = NULL) {
    //получает отвалидированные данные и начинает свое дело...
    //нужно обрабатывать эксепшены, чтобы выполнение программы не прерывалось на этом,
    //как в калькуляторе dc
    /*
    AbstractVM is a stack based virtual machine. Whereas the stack is an actual stack or
    another container that behaves like a stack is up to you. Whatever the container, it MUST
    only contain pointers to the abstract type IOperand.
    */

    //лексер разбирает на токены, а токены парсятся парсером
    //т.е. по регекспу разобрать на токены? А токены уже парсонуть? 

    while (work == RUN) {
        
        if (in) {//name of the arg file, c-string
            //read from file
            //lexer from here
            /*
                лексер будет работать построчно, принял объект, чекнул, вернул
                токен.
                Токен - что в нем будет? 
                тип токена, где в соответствии с типом будет или не будет:
                    операция,
                    тип операнда
                    значение операнда
            */
        } else {
            //read from std input by lexer?
        }


        if (true)
            std::cout << "All works\n";
            work = STOP;
    }
}