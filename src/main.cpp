#include "AbstractVM.hpp"
#include "AVMLexer.hpp"

int main(int ac, char **av) {
    AbstractVM avm;

    if (ac > 1 && std::string(av[1]) == "-h")
        std::cout << "usage: ./avm [arg1 [arg2 ... ]]" << std::endl;
    else if (ac > 2)
        while (*(++av)) {
            std::cout << "\033[41;37m Operation log for file: " << *av << " \033[0m\n";
            avm.run(*av);
            std::cout << "\033[41;37m End of " << *av << " \033[0m\n\n";
            AVMLexer::resetCount();
        }
    else
        avm.run(av[1]);

    return (0);
}