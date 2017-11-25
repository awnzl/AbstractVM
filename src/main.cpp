#include "AbstractVM.hpp"

int main(int ac, char **av) {
    AbstractVM avm;

    //читает либо из 1 файла либо из консоли.
    //нужна валидция для содержимого файла (по регексу?)
    avm.run();

    return (0);
}