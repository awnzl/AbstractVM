#include "AbstractVM.hpp"

int main(int ac, char **av) {
    AbstractVM avm;

    if (ac < 2)
        avm.run(av[1]);
    else
        std::cout << "usage: ./avm [arg]" << std::endl;

    return (0);
}