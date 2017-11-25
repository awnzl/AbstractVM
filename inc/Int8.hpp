#ifndef __INT8_HPP
# define __INT8_HPP

# include "Operand.hpp"
# include "eOperandType.hpp"

class Int8 : public Operand<char> {
public:
    Int8(char v) : Operand<char>(eOperandType::INT8, v) {}
    
    virtual ~Int8(void) {}
};

#endif