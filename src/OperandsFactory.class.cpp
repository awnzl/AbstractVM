#include "OperandsFactory.hpp"
#include "eOperandType.hpp"
#include "Int8.hpp"
#include "Int16.hpp"
#include "Int32.hpp"
#include "Float.hpp"
#include "Double.hpp"

OperandsFactory::OperandsFactory() {
    _creators.push_back(&OperandsFactory::createInt8);
    _creators.push_back(&OperandsFactory::createInt16);
    _creators.push_back(&OperandsFactory::createInt32);
    _creators.push_back(&OperandsFactory::createFloat);
    _creators.push_back(&OperandsFactory::createDouble);
}

OperandsFactory::~OperandsFactory() {
}

OperandsFactory &OperandsFactory::getFactory() {
    static OperandsFactory factory;
    return (factory);
}

const IOperand *OperandsFactory::createInt8(std::string const &value) const {
    long res = std::strtol(value.c_str(), NULL, 10);
    if (res > std::numeric_limits<int8_t>::max())
        throw std::runtime_error("Overflow on a value or the result of an operation");
    else if (res < std::numeric_limits<int8_t>::min()) 
        throw std::runtime_error("Underflow on a value or the result of an operation");
    return (new Int8(res));
}

const IOperand *OperandsFactory::createInt16(std::string const &value) const {
    long res = std::strtol(value.c_str(), NULL, 10);
    if (res > std::numeric_limits<int16_t>::max())
        throw std::runtime_error("Overflow on a value or the result of an operation");
    else if (res < std::numeric_limits<int16_t>::min()) 
        throw std::runtime_error("Underflow on a value or the result of an operation");
    return (new Int16(res));
}

const IOperand *OperandsFactory::createInt32(std::string const &value) const {
    long res = std::strtol(value.c_str(), NULL, 10);
    if (res > std::numeric_limits<int32_t>::max())
        throw std::runtime_error("Overflow on a value or the result of an operation");
    else if (res < std::numeric_limits<int32_t>::min()) 
        throw std::runtime_error("Underflow on a value or the result of an operation");
    return (new Int32(res));
}

const IOperand *OperandsFactory::createFloat(std::string const &value) const {
    long double res = std::strtof(value.c_str(), NULL);
    if (res == HUGE_VALF)
        throw std::runtime_error("Overflow on a value or the result of an operation");
    else if (res == -HUGE_VALF) 
        throw std::runtime_error("Underflow on a value or the result of an operation");
    return (new Float(res));
}

const IOperand *OperandsFactory::createDouble(std::string const &value) const {
    double res = std::strtod(value.c_str(), NULL);
    if (res == HUGE_VAL)
        throw std::runtime_error("Overflow on a value or the result of an operation");
    else if (res == -HUGE_VAL) 
        throw std::runtime_error("Underflow on a value or the result of an operation");
    return (new Double(res));
}

const IOperand *OperandsFactory::createOperand(eOperandType type, std::string const &value) const {
    return (this->*(_creators.at(type)))(value);
}