#ifndef __INT32_HPP
# define __INT32_HPP

# include "Operand.hpp"
# include "eOperandType.hpp"

class Int32 : public Operand<int> {
public:
    Int32(int c) : Operand<int>(eOperandType::INT32, c) {}
    
    virtual ~Int32(void) {}
};

#endif