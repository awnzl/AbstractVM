#include "AbstractVM.hpp"

AbstractVM::AbstractVM() : _work(RUN) {
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
        {AVMToken::TokenType::PRINT, &AbstractVM::print}
    };
}

AbstractVM::~AbstractVM() {
    while (_avmStack.size())
        this->pop();
}

AbstractVM::AbstractVM(const AbstractVM &avm) {
    this->_work = avm._work;
    this->_avmStack = avm._avmStack;
    this->_types = avm._types;
    this->_operations = avm._operations;
    //...
}

AbstractVM &AbstractVM::operator=(AbstractVM &avm) {
    this->_work = avm._work;
    this->_avmStack = avm._avmStack;
    this->_types = avm._types;
    this->_operations = avm._operations;
    //...
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
        throw std::runtime_error("avm: Instruction pop on an empty stack");
}

void AbstractVM::dump() {
    AVMStack<const IOperand*>::iterator st = _avmStack.begin();
    AVMStack<const IOperand*>::iterator en = _avmStack.end();

    while (st != en)
        std::cout << (*st++)->toString() << std::endl;
}

bool AbstractVM::assert(std::string &operand, std::string &value) {
    //todo сделать, чтобы оно печатало true в выводе? 
    const IOperand *op = OperandsFactory::getFactory().createOperand(_types[operand], value);
    const IOperand *top = *(_avmStack.begin());

    if (op->getType() == top->getType() && op->toString() == top->toString()) {
        delete (op);
        return (true);
    } else {
        delete (op);
        throw std::runtime_error("avm: An assert instruction is not true");
    }
    return (false);
}

void AbstractVM::add() {
    if (_avmStack.size() < 2)
        throw std::runtime_error("The stack is composed of strictly less that two values "\
                            "when an arithmetic instruction is executed");

    const IOperand *first = *(_avmStack.begin());
    const IOperand *second = *(_avmStack.begin() + 1);
    _avmStack.pop();
    _avmStack.pop();
    
    const IOperand *res = (*second) + (*first);// v2 op v1 !!!!!!!!!!
    delete (first);
    delete (second);
    
    _avmStack.push(res);

}

void AbstractVM::sub() {
    if (_avmStack.size() < 2)
        throw std::runtime_error("The stack is composed of strictly less that two values "\
                            "when an arithmetic instruction is executed");

    const IOperand *first = *(_avmStack.begin());
    const IOperand *second = *(_avmStack.begin() + 1);
    _avmStack.pop();
    _avmStack.pop();

    const IOperand *res = (*second) - (*first);// v2 op v1 !!!!!!!!!!
    delete (first);
    delete (second);

    _avmStack.push(res);
}

void AbstractVM::mul() {
    if (_avmStack.size() < 2)
        throw std::runtime_error("The stack is composed of strictly less that two values "\
                            "when an arithmetic instruction is executed");
    
    const IOperand *first = *(_avmStack.begin());
    const IOperand *second = *(_avmStack.begin() + 1);
    _avmStack.pop();
    _avmStack.pop();
    
    const IOperand *res = (*second) * (*first);// v2 op v1 !!!!!!!!!!
    delete (first);
    delete (second);
    
    _avmStack.push(res);
}

void AbstractVM::div() {
    if (_avmStack.size() < 2)
        throw std::runtime_error("The stack is composed of strictly less that two values "\
                            "when an arithmetic instruction is executed");
    
    const IOperand *first = *(_avmStack.begin());
    const IOperand *second = *(_avmStack.begin() + 1);
    _avmStack.pop();
    _avmStack.pop();
    
    const IOperand *res = (*second) / (*first);// v2 op v1 !!!!!!!!!!
    delete (first);
    delete (second);
    
    _avmStack.push(res);
}

void AbstractVM::mod() {
    if (_avmStack.size() < 2)
        throw std::runtime_error("The stack is composed of strictly less that two values "\
                            "when an arithmetic instruction is executed");
    
    const IOperand *first = *(_avmStack.begin());
    const IOperand *second = *(_avmStack.begin() + 1);
    _avmStack.pop();
    _avmStack.pop();
    
    const IOperand *res = (*second) % (*first);// v2 op v1 !!!!!!!!!!
    delete (first);
    delete (second);
    
    _avmStack.push(res);
}

void AbstractVM::print() {
    const IOperand *top = *(_avmStack.begin());

    if (top->getType() == eOperandType::INT8) {
        char c = std::atoi(top->toString().c_str());
        std::cout << "'" << c << "'" << std::endl;
    } else
        throw std::runtime_error("avm: An print instruction is not true");
}

void AbstractVM::fileRead(char *in) {
    try {
        AVMToken *tok;
        std::ifstream ifs(in, std::ios_base::in);
        std::string buff;
        while(std::getline(ifs, buff)) { 
            tok = NULL;
            if ((tok = AVMLexer::getLexer().lexIt(buff))) {
                if (tok->type == AVMToken::TokenType::PUSH) {
                    push(tok->operand, tok->value);
                } else if (tok->type == AVMToken::TokenType::ASSERT) {
                    //
                } else if (tok->type == AVMToken::TokenType::EXIT) {
                    //terminate program
                    //free all dynamic data end exit
                    //close all streams
                    _work = AbstractVM::Work::STOP;
                } else {
                    (this->*(_operations[tok->type]))();
                    std::cout << std::endl;//todo delete
                }
            }
        }

        ifs.close();
    } catch (std::exception &ex) {
        //todo обработать исключения
        std::cout << ex.what() << std::endl;
    }
}

void AbstractVM::consoleRead() {
    std::cout << " -------->>> console read debug" <<std::endl;
    try {

    } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
}

/*
AbstractVM is a stack based virtual machine. Whereas the stack is an actual stack or
another container that behaves like a stack is up to you. Whatever the container, it MUST
only contain pointers to the abstract type IOperand.
*/
void AbstractVM::run(char *in = NULL) {

    while (_work == AbstractVM::Work::RUN) {
        
        if (in)
            fileRead(in);
        else
            //читаем из стандартного ввода, отдаем лексеру, парсим валидный результат
            consoleRead();


        if (true) {//todo debug?
            std::cout << "All works\n";//todo debug
            _work = STOP;
        }
    }
}