#ifndef __FLOAT_HPP
# define __FLOAT_HPP

# include "Operand.hpp"
# include "eOperandType.hpp"

class Float : public Operand<float> {
public:
    Float() = delete;
    Float(float v) : Operand<float>(eOperandType::FLOAT, v) {}
    
    virtual ~Float(void) {}
};

#endif