#ifndef __DOUBLE_HPP
# define __DOUBLE_HPP

# include "Operand.hpp"
# include "eOperandType.hpp"

class Double : public Operand<double> {
public:
    Double(double v) : Operand<double>(eOperandType::DOUBLE, v) {}
    
    virtual ~Double(void) {}
};

#endif