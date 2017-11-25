// #include "OperandsFactory.hpp"
// #include "eOperandType.hpp"
#include "../inc/OperandsFactory.hpp"
#include "../inc/eOperandType.hpp"

//TODO поменять инклюды


//todo проверить, чтобы Инт8 был на нулевой позиции
OperandsFactory::OperandsFactory() {
    creators.push_back(createInt8);
    creators.push_back(createInt16);
    creators.push_back(createInt32);
    creators.push_back(createFloat);
    creators.push_back(createDouble);
}

OperandsFactory::~OperandsFactory() {
}

OperandsFactory::OperandsFactory(const OperandsFactory &oc) {
    this->creators = oc.creators;
}

OperandsFactory &OperandsFactory::operator=(OperandsFactory &oc) {
    this->creators = oc.creators;
    return (*this);
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
    //return (new Int32(std::atoi(value.c_str())));
}

const IOperand *OperandsFactory::createDouble(std::string const &value) const {
    //return (new Int32(std::atoi(value.c_str())));
}

const IOperand *OperandsFactory::createOperand(eOperandType type, std::string const &value) const {
    return (this->*(creators.at(type)))(value);
}