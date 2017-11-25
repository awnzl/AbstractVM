#ifndef __INT16_HPP
# define __INT16_HPP

# include "Operand.hpp"
# include "eOperandType.hpp"

class Int16 : public Operand<short> {
public:
    Int16(short c) : Operand<short>(eOperandType::INT16, c) {}
    
    virtual ~Int16(void) {}
};

#endif