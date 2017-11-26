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
    std::string instanceString;

    Operand() {}

public:
    Operand(eOperandType type, T val) : value(val), type(type) {
        std::stringstream ss;
        ss << type << " " << value << std::endl;
        instanceString = ss.str();
        //todo change this to more relevant string?
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

    const IOperand *operator+(const IOperand &rhs) const { // Sum
        if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.getType(), this->value);
            return (tmp + rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->type, static_cast<Operand<T> const &>(rhs).value);
            return (tmp + rhs);
        } else
            return (new Operand(this->type, this->value + static_cast<Operand<T> const &>(rhs).value));
    }
    
    const IOperand *operator-(const IOperand &rhs) const { // Difference
        if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.getType(), this->value);
            return (tmp - rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->type, static_cast<Operand<T> const &>(rhs).value);
            return (tmp - rhs);
        } else
            return (new Operand(this->type, this->value - static_cast<Operand<T> const &>(rhs).value));
    }

    const IOperand *operator*(const IOperand &rhs) const { // Product
        if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.getType(), this->value);
            return (tmp * rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->type, static_cast<Operand<T> const &>(rhs).value);
            return (tmp * rhs);
        } else
            return (new Operand(this->type, this->value * static_cast<Operand<T> const &>(rhs).value));
    }

    const IOperand *operator/(const IOperand &rhs) const { // Quotient
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

    const IOperand *operator%(const IOperand &rhs) const { // Modulo
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

    const std::string &toString(void) const { // String representation of the instance
        return (this->instanceString);
    }

    virtual ~Operand() {}
};

#endif