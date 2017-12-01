#ifndef __AVMEXCEPTION_HPP
# define __AVMEXCEPTION_HPP

# include <stdexcept>
# include <string>

class AVMException : public std::exception {
    std::string _message;

public:
    AVMException() = delete;
    AVMException(std::string s);
    ~AVMException() throw();
    AVMException(const AVMException &);
    AVMException &operator=(AVMException &);
    virtual const char* what() const throw();
};

#endif