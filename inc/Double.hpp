#ifndef __DOUBLE_HPP
# define __DOUBLE_HPP

# include "Operand.hpp"
# include "eOperandType.hpp"

class Double : public Operand<double> {
public:
    Double(double c) : Operand<double>(eOperandType::DOUBLE, c) {}
    
    virtual ~Double(void) {}
};

#endif