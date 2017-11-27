#ifndef __INT8_HPP
# define __INT8_HPP

# include "Operand.hpp"
# include "eOperandType.hpp"

class Int8 : public Operand<int8_t> {
public:
    Int8() = delete;
    Int8(int8_t v) : Operand<int8_t>(eOperandType::INT8, v) {}
    
    virtual ~Int8(void) {}
};

#endif