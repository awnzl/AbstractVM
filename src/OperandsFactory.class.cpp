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
    return (new Int8(std::atoi(value.c_str())));
}

const IOperand *OperandsFactory::createInt16(std::string const &value) const {
    return (new Int16(std::atoi(value.c_str())));
}

const IOperand *OperandsFactory::createInt32(std::string const &value) const {
    return (new Int32(std::atoi(value.c_str())));
}

const IOperand *OperandsFactory::createFloat(std::string const &value) const {
    return (new Float(std::atof(value.c_str())));
}

const IOperand *OperandsFactory::createDouble(std::string const &value) const {
    return (new Double(std::atof(value.c_str())));
}

const IOperand *OperandsFactory::createOperand(eOperandType type, std::string const &value) const {
    return (this->*(_creators.at(type)))(value);
}