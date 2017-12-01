#include "AbstractVM.hpp"
#include "AVMException.hpp"

AbstractVM::AbstractVM() {
    _types = {
        {"int8", eOperandType::INT8},
        {"int16", eOperandType::INT16},
        {"int32", eOperandType::INT32},
        {"float", eOperandType::FLOAT},
        {"double", eOperandType::DOUBLE}
    };

    _operations = {
        {AVMToken::TokenType::ADD, &AbstractVM::add},
        {AVMToken::TokenType::SUB, &AbstractVM::sub},
        {AVMToken::TokenType::MUL, &AbstractVM::mul},
        {AVMToken::TokenType::DIV, &AbstractVM::div},
        {AVMToken::TokenType::MOD, &AbstractVM::mod},
        {AVMToken::TokenType::DUMP, &AbstractVM::dump},
        {AVMToken::TokenType::POP, &AbstractVM::pop},
        {AVMToken::TokenType::PRINT, &AbstractVM::print},
        {AVMToken::TokenType::CLEAN, &AbstractVM::clean},
        {AVMToken::TokenType::DUP, &AbstractVM::dup},
        {AVMToken::TokenType::SWAP, &AbstractVM::swap}
    };
}

AbstractVM::~AbstractVM() {
    exit();
}

AbstractVM::AbstractVM(const AbstractVM &avm) {
    this->_work = avm._work;
    this->_avmStack = avm._avmStack;
    this->_types = avm._types;
    this->_operations = avm._operations;
}

AbstractVM &AbstractVM::operator=(AbstractVM &avm) {
    this->_work = avm._work;
    this->_avmStack = avm._avmStack;
    this->_types = avm._types;
    this->_operations = avm._operations;
    return (*this);
}

void AbstractVM::push(std::string &operand, std::string &value) {
    _avmStack.push(OperandsFactory::getFactory().createOperand(_types[operand], value));
}

void AbstractVM::pop() {
    if (_avmStack.size()) {
        const IOperand *tmp = *(_avmStack.begin());
        _avmStack.pop();
        delete (tmp);
    } else
        throw AVMException("avm: Instruction pop on an empty stack");
}

void AbstractVM::dump() {
    AVMStack<const IOperand*>::iterator st = _avmStack.begin();
    AVMStack<const IOperand*>::iterator en = _avmStack.end();

    while (st != en)
        std::cout << (*st++)->toString() << std::endl;
}

bool AbstractVM::assert(std::string &operand, std::string &value) {
    const IOperand *op = OperandsFactory::getFactory().createOperand(_types[operand], value);
    const IOperand *top = *(_avmStack.begin());

    if (op->getType() == top->getType() && op->toString() == top->toString()) {
        delete (op);
        std::cout << "Value at the top of the stack is equal to "
                  << operand << "(" << value << ")" << std::endl;
    } else {
        delete (op);
        throw AVMException("avm: An assert instruction is not true");
    }
    return (false);
}

void AbstractVM::add() {
    if (_avmStack.size() < 2)
        throw AVMException("avm: The stack is composed less that two values ");

    const IOperand *first = *(_avmStack.begin());
    const IOperand *second = *(_avmStack.begin() + 1);
            
    const IOperand *res = (*second) + (*first);
    
    _avmStack.pop();
    _avmStack.pop();
    _avmStack.push(res);

    delete (first);
    delete (second);
}

void AbstractVM::sub() {
    if (_avmStack.size() < 2)
        throw AVMException("avm: The stack is composed less that two values ");

    const IOperand *first = *(_avmStack.begin());
    const IOperand *second = *(_avmStack.begin() + 1);
            
    const IOperand *res = (*second) - (*first);
    
    _avmStack.pop();
    _avmStack.pop();
    _avmStack.push(res);

    delete (first);
    delete (second);
}

void AbstractVM::mul() {
    if (_avmStack.size() < 2)
        throw AVMException("avm: The stack is composed less that two values ");
    
    const IOperand *first = *(_avmStack.begin());
    const IOperand *second = *(_avmStack.begin() + 1);
        
    const IOperand *res = (*second) * (*first);
    
    _avmStack.pop();
    _avmStack.pop();
    _avmStack.push(res);

    delete (first);
    delete (second);
}

void AbstractVM::div() {
    if (_avmStack.size() < 2)
        throw AVMException("avm: The stack is composed less that two values ");
    
    const IOperand *first = *(_avmStack.begin());
    const IOperand *second = *(_avmStack.begin() + 1);
        
    const IOperand *res = (*second) / (*first);
    
    _avmStack.pop();
    _avmStack.pop();
    _avmStack.push(res);

    delete (first);
    delete (second);
}

void AbstractVM::mod() {
    if (_avmStack.size() < 2)
        throw AVMException("avm: The stack is composed less that two values ");
    
    const IOperand *first = *(_avmStack.begin());
    const IOperand *second = *(_avmStack.begin() + 1);
            
    const IOperand *res = (*second) % (*first);
    
    _avmStack.pop();
    _avmStack.pop();
    _avmStack.push(res);

    delete (first);
    delete (second);
}

void AbstractVM::exit() {
    while (_avmStack.size())
        this->pop();
    _work = AbstractVM::Work::STOP;
}

void AbstractVM::print() {
    const IOperand *top = *(_avmStack.begin());

    if (top->getType() == eOperandType::INT8) {
        char c = std::atoi(top->toString().c_str());
        std::cout << "'" << c;
        std::cout << "'" << std::endl;
    } else
        throw AVMException("avm: An print instruction is not true");
}

void AbstractVM::clean() {
    while (_avmStack.size())
        this->pop();
}

void AbstractVM::dup() {
    const IOperand *top = *(_avmStack.begin());
    const IOperand *dup = OperandsFactory::getFactory().createOperand(top->getType(), top->toString());
    _avmStack.push(dup);
}

void AbstractVM::swap() {
    const IOperand *first = *(_avmStack.begin());
    const IOperand *second = *(_avmStack.begin() + 1);
    _avmStack.pop();
    _avmStack.pop();
    _avmStack.push(first);
    _avmStack.push(second);
}

void AbstractVM::fileRead(char *in) {
    AVMToken *tok;
    std::ifstream ifs(in);
    std::string buff;
    if (ifs) {
        while(std::getline(ifs, buff)) { 
            tok = NULL;
            try {
                if ((tok = AVMLexer::getLexer().lexIt(buff))) {
                    if (tok->type == AVMToken::TokenType::PUSH) {
                        push(tok->operand, tok->value);
                    } else if (tok->type == AVMToken::TokenType::ASSERT) {
                        assert(tok->operand, tok->value);
                    } else if (tok->type == AVMToken::TokenType::EXIT) {
                        exit();
                        return;
                    } else {
                        (this->*(_operations[tok->type]))();
                    }
                }
            } catch (AVMException &ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        ifs.close();
        _work = AbstractVM::Work::STOP;
        throw AVMException("avm: The program doesn’t have an exit instruction");
    }
}

void AbstractVM::consoleRead() {
    AVMToken *tok;
    std::string buff;
    while(std::getline(std::cin, buff)) { 
        tok = NULL;
        try {
            if ((tok = AVMLexer::getLexer().lexIt(buff))) {
                if (tok->type == AVMToken::TokenType::PUSH) {
                    push(tok->operand, tok->value);
                } else if (tok->type == AVMToken::TokenType::ASSERT) {
                    assert(tok->operand, tok->value);
                } else if (tok->type == AVMToken::TokenType::EXIT) {
                    exit();
                    return;
                } else {
                    (this->*(_operations[tok->type]))();
                }
            }
        } catch (AVMException &ex) {
            std::cout << ex.what() << std::endl;
        }
    }
}

void AbstractVM::run(char *in = NULL) {
    try {
        _work = AbstractVM::Work::RUN;
        while (_work == AbstractVM::Work::RUN) {
            if (in)
                fileRead(in);
            else
                consoleRead();
        }
    } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
}