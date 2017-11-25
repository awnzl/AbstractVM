#ifndef __FLOAT_HPP
# define __FLOAT_HPP

# include "Operand.hpp"
# include "eOperandType.hpp"

class Float : public Operand<float> {
public:
    Float(float c) : Operand<float>(eOperandType::FLOAT, c) {}
    
    virtual ~Float(void) {}
};

#endif