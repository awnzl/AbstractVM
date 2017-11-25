#ifndef __OPERANDSFACTORY_HPP
# define __OPERANDSFACTORY_HPP

# include <vector>
# include <cstdlib>
# include "IOperand.hpp"
# include "eOperandType.hpp"
# include "Int8.hpp"
# include "Int16.hpp"
# include "Int32.hpp"

class OperandsFactory {
    std::vector<const IOperand *(OperandsFactory::*)(const std::string &) const> creators;

    const IOperand *createInt8(const std::string &value) const;
    const IOperand *createInt16(const std::string &value) const;
    const IOperand *createInt32(const std::string &value) const;
    const IOperand *createFloat(const std::string &value) const;
    const IOperand *createDouble(const std::string &value) const;

public:
    OperandsFactory();
    ~OperandsFactory();
    OperandsFactory(const OperandsFactory &);
    OperandsFactory &operator=(OperandsFactory &);

    const IOperand *createOperand(eOperandType type, std::string const &value) const;
};

#endif