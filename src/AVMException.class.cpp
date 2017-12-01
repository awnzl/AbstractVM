#include "AVMException.hpp"

AVMException::AVMException(std::string s) : _message(s) {
}

AVMException::~AVMException() throw() {
}

AVMException::AVMException(const AVMException &e) {
    this->_message = e._message;
}

AVMException &AVMException::operator=(AVMException &e) {
    this->_message = e._message;
    return (*this);
}

const char* AVMException::what() const throw() {
    return (this->_message.c_str());
}
