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
    while (work == RUN) {
        
        if (true)
            std::cout << "All works\n";
            work = STOP;
    }
}