#ifndef __INT32_HPP
# define __INT32_HPP

# include "Operand.hpp"
# include "eOperandType.hpp"

class Int32 : public Operand<int32_t> {
public:
    Int32() = delete;
    Int32(int32_t v) : Operand<int32_t>(eOperandType::INT32, v) {}
    
    virtual ~Int32(void) {}
};

#endif