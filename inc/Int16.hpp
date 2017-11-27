#ifndef __INT16_HPP
# define __INT16_HPP

# include "Operand.hpp"
# include "eOperandType.hpp"

class Int16 : public Operand<int16_t> {
public:
    Int16() = delete;
    Int16(int16_t v) : Operand<int16_t>(eOperandType::INT16, v) {}
    
    virtual ~Int16(void) {}
};

#endif