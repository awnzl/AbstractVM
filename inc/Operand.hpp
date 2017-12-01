#ifndef __OPERAND_HPP
# define __OPERAND_HPP

# include <sstream>
# include <limits>
# include <cmath>
# include "OperandsFactory.hpp"
# include "IOperand.hpp"
# include "AVMException.hpp"

template<typename T> class Operand : public IOperand {
    eOperandType _type;
    T _value;
    std::string _instanceString;

    bool checkRange(int tp, double res, int *flg) const {
        switch (tp) {
            case (eOperandType::FLOAT) :
            if (res > std::numeric_limits<float>::max())
                return (true);
            else if (res < -std::numeric_limits<float>::max()) {
                *flg = -1;
                return (true);
            }
            break;
        case (eOperandType::DOUBLE) :
            if (res == NAN)
                return (true);
            else if (res == -NAN) {
                *flg = -1;
                return (true);
            }
            break;
        }
        return (false);
    }

    bool checkRange(int tp, long res, int *flg) const {
        switch (tp) {
            case (eOperandType::INT8) :
                if (res > std::numeric_limits<int8_t>::max())
                    return (true);
                else if (res < std::numeric_limits<int8_t>::min()) {
                    *flg = -1;
                    return (true);
                }
                break;
            case (eOperandType::INT16) :
                if (res > std::numeric_limits<int16_t>::max())
                    return (true);
                else if (res < std::numeric_limits<int16_t>::min()) {
                    *flg = -1;
                    return (true);
                }
                break;
            case (eOperandType::INT32) :
                if (res > std::numeric_limits<int32_t>::max())
                    return (true);
                else if (res < std::numeric_limits<int32_t>::min()) {
                    *flg = -1;
                    return (true);
                }
                break;
        }
        return (false);
    }

    const IOperand *mathIt(eOperandType tp, std::string left, std::string right, char c) const {
        int flg = 1;
        std::stringstream ss;
        
        auto l = (tp < 3) ? std::atol(left.c_str()) : std::atof(left.c_str());
        auto r = (tp < 3) ? std::atol(right.c_str()) : std::atof(right.c_str());
        
        const IOperand *resop = NULL;

        switch (c) {
            case '+' : 
                {
                    auto add = l + r;
                    if (checkRange(tp, add, &flg))
                        throw AVMException((flg > 0) ? "Overflow on a value or the result of an operation"
                                                           : "Underflow on a value or the result of an operation");
                    ss << add;
                    resop = OperandsFactory::getFactory().createOperand(tp, ss.str());
                }
                break;
            case '-' : 
                {
                    auto sub = l - r;
                    if (checkRange(tp, sub, &flg))
                        throw AVMException((flg > 0) ? "Overflow on a value or the result of an operation"
                                                           : "Underflow on a value or the result of an operation");
                    ss << sub;
                    resop = OperandsFactory::getFactory().createOperand(tp, ss.str());
                }
                break;
            case '*' : 
                {
                    auto mul = l * r;
                    if (checkRange(tp, mul, &flg))
                        throw AVMException((flg > 0) ? "Overflow on a value or the result of an operation"
                                                           : "Underflow on a value or the result of an operation");
                    ss << mul;
                    resop = OperandsFactory::getFactory().createOperand(tp, ss.str());
                }
                break;
            case '/' : 
                {
                    auto div = l / r;
                    if (checkRange(tp, div, &flg))
                        throw AVMException((flg > 0) ? "Overflow on a value or the result of an operation"
                                                           : "Underflow on a value or the result of an operation");
                    ss << div;
                    resop = OperandsFactory::getFactory().createOperand(tp, ss.str());
                }
                break;
            case '%' : 
                {
                    bool range;
                    if (tp < 3) {
                        long mod = static_cast<long>(l) % static_cast<long>(r);
                        ss << mod;
                        range = checkRange(tp, mod, &flg);
                    } else {
                        int cha = l / r;
                        double mod = l - cha * r;
                        ss << mod;
                        range = checkRange(tp, mod, &flg);
                    }
                    if (range)
                        throw AVMException((flg > 0) ? "Overflow on a value or the result of an operation"
                                                           : "Underflow on a value or the result of an operation");

                    resop = OperandsFactory::getFactory().createOperand(tp, ss.str());
                }
                break;
        }

        return (resop);
    }

public:
    Operand() = delete;

    Operand(eOperandType type, T val) : _type(type), _value(val) {
        std::stringstream ss;
        ss << ((type == eOperandType::INT8) ? static_cast<int16_t>(val) : val);
        _instanceString = ss.str();
    }

    Operand(const Operand &op) {
        this->_value = op._value;
        this->_type = op._type;
    }

    const Operand &operator=(const Operand &op) {
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
            const IOperand *res = NULL;
        if (this->getPrecision() < rhs.getPrecision()) {
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(rhs.getType(), this->_instanceString);
            res = mathIt(rhs.getType(), tmp->toString(), rhs.toString(), '+');
            delete (tmp);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(this->_type, rhs.toString());
            res = mathIt(this->_type, this->_instanceString, tmp->toString(), '+');
            delete (tmp);
        } else
            res = mathIt(this->_type, this->_instanceString, rhs.toString(), '+');
        
        return (res);
    }

    const IOperand *operator-(const IOperand &rhs) const { // Difference
        const IOperand *res = NULL;
        if (this->getPrecision() < rhs.getPrecision()) {
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(rhs.getType(), this->_instanceString);
            res = mathIt(rhs.getType(), tmp->toString(), rhs.toString(), '-');
            delete (tmp);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(this->_type, rhs.toString());
            res = mathIt(this->_type, this->_instanceString, tmp->toString(), '-');
            delete (tmp);
        } else
            res = mathIt(this->_type, this->_instanceString, rhs.toString(), '-');
        
        return (res);
    }

    const IOperand *operator*(const IOperand &rhs) const { // Product
        const IOperand *res = NULL;
        if (this->getPrecision() < rhs.getPrecision()) {
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(rhs.getType(), this->_instanceString);
            res = mathIt(rhs.getType(), tmp->toString(), rhs.toString(), '*');
            delete (tmp);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(this->_type, rhs.toString());
            res = mathIt(this->_type, this->_instanceString, tmp->toString(), '*');
            delete (tmp);
        } else
            res = mathIt(this->_type, this->_instanceString, rhs.toString(), '*');
        
        return (res);
    }

    const IOperand *operator/(const IOperand &rhs) const { // Quotient
        if (rhs.toString() == "0" || rhs.toString() == "0.0")
            throw (AVMException("avm: division by zero"));
        
        const IOperand *res = NULL;
        if (this->getPrecision() < rhs.getPrecision()) {
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(rhs.getType(), this->_instanceString);
            res = mathIt(rhs.getType(), tmp->toString(), rhs.toString(), '/');
            delete (tmp);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(this->_type, rhs.toString());
            res = mathIt(this->_type, this->_instanceString, tmp->toString(), '/');
            delete (tmp);
        } else
            res = mathIt(this->_type, this->_instanceString, rhs.toString(), '/');
        
        return (res);
    }
    
    const IOperand *operator%(const IOperand &rhs) const { // Modulo
        if (rhs.toString() == "0" || rhs.toString() == "0.0")
            throw (AVMException("avm: modulo by zero"));
        
        const IOperand *res = NULL;
        if (this->getPrecision() < rhs.getPrecision()) {
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(rhs.getType(), this->_instanceString);
            res = mathIt(rhs.getType(), tmp->toString(), rhs.toString(), '-');
            delete (tmp);
        } else if (this->getPrecision() > rhs.getPrecision()) {
            const IOperand *tmp = OperandsFactory::getFactory().createOperand(this->_type, rhs.toString());
            res = mathIt(this->_type, this->_instanceString, tmp->toString(), '-');
            delete (tmp);
        } else
            res = mathIt(this->_type, this->_instanceString, rhs.toString(), '-');

        return (res);
    }

    const std::string &toString(void) const { // String representation of the instance
        return (_instanceString);
    }

    virtual ~Operand() {
    }
};

#endif