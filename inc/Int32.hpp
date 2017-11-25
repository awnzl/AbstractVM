#ifndef __INT32_HPP
# define __INT32_HPP

# include "Operand.hpp"
# include "eOperandType.hpp"

class Int32 : public Operand<int> {
public:
    Int32(int v) : Operand<int>(eOperandType::INT32, v) {}
    
    virtual ~Int32(void) {}
};

#endif