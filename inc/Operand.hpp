#ifndef __OPERAND_HPP
# define __OPERAND_HPP

# include <stdexcept>
# include <sstream>
# include <cmath>
# include "IOperand.hpp"
# include "eOperandType.hpp"

template<typename T> class Operand : public IOperand {
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

    Operand &operator=(Operand &op) {
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
        if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.getType(), this->value);
            return (tmp + rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->type, static_cast<Operand<T> const &>(rhs).value);
            return (tmp + rhs);
        } else
            return (new Operand(this->type, this->value + static_cast<Operand<T> const &>(rhs).value));
    }
    
    IOperand const *operator-(IOperand const &rhs) const { // Difference
        if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.getType(), this->value);
            return (tmp - rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->type, static_cast<Operand<T> const &>(rhs).value);
            return (tmp - rhs);
        } else
            return (new Operand(this->type, this->value - static_cast<Operand<T> const &>(rhs).value));
    }


    IOperand const *operator*(IOperand const &rhs) const { // Product
        if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.getType(), this->value);
            return (tmp * rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->type, static_cast<Operand<T> const &>(rhs).value);
            return (tmp * rhs);
        } else
            return (new Operand(this->type, this->value * static_cast<Operand<T> const &>(rhs).value));
    }

    IOperand const *operator/(IOperand const &rhs) const { // Quotient
        if (static_cast<Operand<T> const &>(rhs).value == 0)
            throw (std::runtime_error("division by zero"));
        
        if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.getType(), this->value);
            return (tmp / rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->type, static_cast<Operand<T> const &>(rhs).value);
            return (tmp / rhs);
        } else
            return (new Operand(this->type, this->value / static_cast<Operand<T> const &>(rhs).value));
    }

    IOperand const *operator%(IOperand const &rhs) const { // Modulo
        if (static_cast<Operand<T> const &>(rhs).value == 0)
            throw (std::runtime_error("modulo by zero"));

        if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.getType(), this->value);
            return (tmp % rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->type, static_cast<Operand<T> const &>(rhs).value);
            return (tmp % rhs);
        } else
            return (new Operand(this->type, std::fmod(this->value, static_cast<Operand<T> const &>(rhs).value)));
    }

    std::string const &toString(void) const { // String representation of the instance
        //todo get more relevant string
        std::stringstream ss;
        ss << this->value;
        return (ss.str());
    }

    virtual ~Operand() {}
};

#endif