#ifndef __OPERAND_HPP
# define __OPERAND_HPP

# include <stdexcept>
# include <sstream>
# include <cmath>
# include <iostream>//todo delete
# include <typeinfo>//todo delete
# include "OperandsFactory.hpp"
# include "IOperand.hpp"

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
//todo test all this
    const IOperand *operator+(const IOperand &rhs) const { // Sum
        std::stringstream ss;
        if (this->getPrecision() < rhs.getPrecision()) {
            ss << this->_value;
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(rhs.getType(), ss.str());
            return ((*tmp) + rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            ss << static_cast<Operand<T> const &>(rhs)._value;
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(this->_type, ss.str());
            return ((*tmp) + rhs);
        } else {
            ss << (this->_value + static_cast<Operand<T> const &>(rhs)._value);
            const IOperand *res = OperandsFactory::getFactory().createOperand(this->_type, ss.str());
            delete (this);
            return (res);
        }
    }
  
    const IOperand *operator-(const IOperand &rhs) const { // Difference
        std::stringstream ss;
        if (this->getPrecision() < rhs.getPrecision()) {
            ss << this->_value;
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(rhs.getType(), ss.str());
            return ((*tmp) - rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            ss << static_cast<Operand<T> const &>(rhs)._value;
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(this->_type, ss.str());
            return ((*tmp) - rhs);
        } else {
            ss << (this->_value - static_cast<Operand<T> const &>(rhs)._value);
            const IOperand *res = OperandsFactory::getFactory().createOperand(this->_type, ss.str());
            delete (this);
            return (res);
        }
    }

    const IOperand *operator*(const IOperand &rhs) const { // Product
        std::stringstream ss;
        if (this->getPrecision() < rhs.getPrecision()) {
            ss << this->_value;
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(rhs.getType(), ss.str());
            return ((*tmp) * rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            ss << static_cast<Operand<T> const &>(rhs)._value;
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(this->_type, ss.str());
            return ((*tmp) * rhs);
        } else {
            ss << (this->_value * static_cast<Operand<T> const &>(rhs)._value);
            const IOperand *res = OperandsFactory::getFactory().createOperand(this->_type, ss.str());
            delete (this);
            return (res);
        }
    }

    const IOperand *operator/(const IOperand &rhs) const { // Quotient
        if (static_cast<Operand<T> const &>(rhs)._value == 0)
            throw (std::runtime_error("avm: division by zero"));
        
        std::stringstream ss;
        if (this->getPrecision() < rhs.getPrecision()) {
            ss << this->_value;
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(rhs.getType(), ss.str());
            return ((*tmp) / rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            ss << static_cast<Operand<T> const &>(rhs)._value;
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(this->_type, ss.str());
            return ((*tmp) / rhs);
        } else {
            ss << (this->_value / static_cast<Operand<T> const &>(rhs)._value);
            const IOperand *res = OperandsFactory::getFactory().createOperand(this->_type, ss.str());
            delete (this);
            return (res);
        }
    }

    const IOperand *operator%(const IOperand &rhs) const { // Modulo
        if (static_cast<Operand<T> const &>(rhs)._value == 0)
            throw (std::runtime_error("avm: modulo by zero"));
        
        std::stringstream ss;
        if (this->getPrecision() < rhs.getPrecision()) {
            ss << this->_value;
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(rhs.getType(), ss.str());
            return ((*tmp) + rhs);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            ss << static_cast<Operand<T> const &>(rhs)._value;
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(this->_type, ss.str());
            return ((*tmp) + rhs);
        } else {
            ss << std::fmod(this->_value, static_cast<Operand<T> const &>(rhs)._value);
            const IOperand *res = OperandsFactory::getFactory().createOperand(this->_type, ss.str());
            delete (this);
            return (res);
        }
    }

    const std::string &toString(void) const { // String representation of the instance
        return (this->_instanceString);
    }

    virtual ~Operand() {}
};

#endif