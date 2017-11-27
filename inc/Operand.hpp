#ifndef __OPERAND_HPP
# define __OPERAND_HPP

# include <stdexcept>
# include <sstream>
# include <cmath>
# include <iostream>//todo debug
# include <typeinfo>//todo debug
# include "IOperand.hpp"
# include "eOperandType.hpp"

template<typename T> class Operand : public IOperand {
    eOperandType _type;
    T _value;
    std::string _instanceString;

public:
    Operand() = delete;

    Operand<T>(eOperandType type, T val) : _type(type), _value(val) {
        std::string arr[] = {"Int8", "Int16", "Int32", "Float", "Double"};
        std::stringstream ss;
        ss << arr[_type] << " " << _value;
        _instanceString = ss.str();
    }

    Operand(const Operand &op) {
        this->_value = op._value;
        this->_type = op._type;
    }

    Operand &operator=(Operand &op) {
        this->_value = op._value;
        this->_type = op._type;
    }

    int getPrecision(void) const { // Precision of the _type of the instance
        return (this->_type);
    }

    eOperandType getType(void) const { // _Type of the instance
        return (this->_type);
    }

    const IOperand *operator+(const IOperand &rhs) const { // Sum
        if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.getType(), this->_value);
            return (tmp + rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->_type, static_cast<Operand<T> const &>(rhs)._value);//откуда оно здесь, какой тип юзать для шаблона?
            return (tmp + rhs);//бесконечная рекурсия для типов от меншего к большему? 
        } else
            return (new Operand(this->_type, this->_value + static_cast<Operand<T> const &>(rhs)._value));
    }
    
    const IOperand *operator-(const IOperand &rhs) const { // Difference
        if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.getType(), this->_value);
            return (tmp - rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->_type, static_cast<Operand<T> const &>(rhs)._value);
            return (tmp - rhs);
        } else
            return (new Operand(this->_type, this->_value - static_cast<Operand<T> const &>(rhs)._value));
    }

    const IOperand *operator*(const IOperand &rhs) const { // Product
        if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.getType(), this->_value);
            return (tmp * rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->_type, static_cast<Operand<T> const &>(rhs)._value);
            return (tmp * rhs);
        } else
            return (new Operand(this->_type, this->_value * static_cast<Operand<T> const &>(rhs)._value));
    }

    const IOperand *operator/(const IOperand &rhs) const { // Quotient
        if (static_cast<Operand<T> const &>(rhs)._value == 0)
            throw (std::runtime_error("division by zero"));
        
        if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.getType(), this->_value);
            return (tmp / rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->_type, static_cast<Operand<T> const &>(rhs)._value);
            return (tmp / rhs);
        } else
            return (new Operand(this->_type, this->_value / static_cast<Operand<T> const &>(rhs)._value));
    }

    const IOperand *operator%(const IOperand &rhs) const { // Modulo
        if (static_cast<Operand<T> const &>(rhs)._value == 0)
            throw (std::runtime_error("modulo by zero"));

        if (this->getPrecision() < rhs.getPrecision()) {
            Operand tmp(rhs.getType(), this->_value);
            return (tmp % rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            Operand tmp(this->_type, static_cast<Operand<T> const &>(rhs)._value);
            return (tmp % rhs);
        } else
            return (new Operand(this->_type, std::fmod(this->_value, static_cast<Operand<T> const &>(rhs)._value)));
    }

    const std::string &toString(void) const { // String representation of the instance
        return (this->_instanceString);
    }

    virtual ~Operand() {}
};

#endif