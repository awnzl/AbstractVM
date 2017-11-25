#ifndef __OPERAND_HPP
# define __OPERAND_HPP

# include <stdexcept>
# include "IOperand.hpp"
# include "eOperandType.hpp"

template<typename T>
class Operand : public IOperand {
    T value;
    eOperandType type;
    Operand() {}

public:
    Operand(eOperandType type, T val) : value(val), type(type) {
    }

    Operand(const Operand &op) {
        this->value = op.value;
        this->type = op.type;
    }

    Operand &operator=(Operand &) {
        this->value = op.value;
        this->type = op.type;
    }

    int getPrecision(void) const { // Precision of the type of the instance
        return (this->type);
    }

    eOperandType getType(void) const { // Type of the instance
        return (this->type);
    }

    IOperand const *operator+(IOperand const &rhs) const { // Sum
        if (this->getPrecision() == rhs.getPrecision())
            return (new Operand(this->type, this->value + rhs.value);
        else if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.type, this->value);
            return (tmp + rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->type, rhs.value);
            return (tmp + rhs);
        }
    }
    
    IOperand const *operator-(IOperand const &rhs) const { // Difference
        if (this->getPrecision() == rhs.getPrecision())
            return (new Operand(this->type, this->value - rhs.value);
        else if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.type, this->value);
            return (tmp - rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->type, rhs.value);
            return (tmp - rhs);
        }
    }


    IOperand const *operator*(IOperand const &rhs) const { // Product
        if (this->getPrecision() == rhs.getPrecision())
            return (new Operand(this->type, this->value * rhs.value);
        else if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.type, this->value);
            return (tmp * rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->type, rhs.value);
            return (tmp * rhs);
        }
    }

    IOperand const *operator/(IOperand const &rhs) const { // Quotient
        if (rhs.value == 0)
            throw (runtime_error("division by zero"));
        
        if (this->getPrecision() == rhs.getPrecision())
            return (new Operand(this->type, this->value / rhs.value);
        else if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.type, this->value);
            return (tmp / rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->type, rhs.value);
            return (tmp / rhs);
        }
    }

    IOperand const *operator%(IOperand const &rhs) const { // Modulo
        if (rhs.value == 0)
            throw (runtime_error("modulo by zero"));

        if (this->getPrecision() == rhs.getPrecision())
            return (new Operand(this->type, this->value % rhs.value);
        else if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.type, this->value);
            return (tmp % rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->type, rhs.value);
            return (tmp % rhs);
        }
    }

    std::string const &toString(void) const; // String representation of the instance
    //todo implement toString function

    virtual ~Operand() {}
};

#endif