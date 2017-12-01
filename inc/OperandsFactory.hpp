#ifndef __OPERANDSFACTORY_HPP
# define __OPERANDSFACTORY_HPP

# include <vector>
# include <cstdlib>
# include <cmath>
# include "IOperand.hpp"
# include "eOperandType.hpp"

class OperandsFactory {
    std::vector<const IOperand *(OperandsFactory::*)(const std::string &) const> _creators;

    const IOperand *createInt8(const std::string &value) const;
    const IOperand *createInt16(const std::string &value) const;
    const IOperand *createInt32(const std::string &value) const;
    const IOperand *createFloat(const std::string &value) const;
    const IOperand *createDouble(const std::string &value) const;

    OperandsFactory();

public:
    ~OperandsFactory();
    OperandsFactory(const OperandsFactory &) = delete;
    OperandsFactory &operator=(OperandsFactory &) = delete;
    const OperandsFactory &operator=(const OperandsFactory &) = delete;
    const IOperand *createOperand(eOperandType type, std::string const &value) const;
    static OperandsFactory &getFactory();

};

static OperandsFactory &getFactory();

#endif