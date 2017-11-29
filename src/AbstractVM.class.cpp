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
    //todo free pointers in stack
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
    if (_avmStack.size() > 0)
        _avmStack.pop();
    else
        throw std::runtime_error("avm: Instruction pop on an empty stack");
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
        return (true);
    } else {
        delete (op);
        throw std::runtime_error("avm: An assert instruction is not true");
    }
    return (false);
}

void AbstractVM::add() {
    /*
    Unstacks the first two values on the stack, adds them together and stacks the
    result. If the number of values on the stack is strictly inferior to 2, the program
    execution must stop with an error.
    */
    if (_avmStack.size() < 2)
        throw std::runtime_error("The stack is composed of strictly less that two values "\
                            "when an arithmetic instruction is executed");

    const IOperand *first = *(_avmStack.begin());
    const IOperand *second = *(_avmStack.begin() + 1);
    _avmStack.pop();
    _avmStack.pop();
    // std::cout << "add first: " << first->toString() << std::endl;
    // std::cout << "add second: " << second->toString() << std::endl;
    
    const IOperand *res = (*second) + (*first);// v2 op v1 !!!!!!!!!!
    // std::cout << "add res: " << res->toString() << std::endl;
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

}


void AbstractVM::run(char *in = NULL) {
    //получает отвалидированные данные и начинает свое дело...
    //нужно обрабатывать эксепшены (ЗАПИЛИТЬ КЛАССЫ ДЛЯ ИСКЛЮЧЕНИЙ),
    //чтобы выполнение программы не прерывалось на этом,
    //как в калькуляторе dc
    /*
    AbstractVM is a stack based virtual machine. Whereas the stack is an actual stack or
    another container that behaves like a stack is up to you. Whatever the container, it MUST
    only contain pointers to the abstract type IOperand.
    */

    //лексер разбирает на токены, а токены парсятся парсером
    //т.е. по регекспу разобрать на токены? А токены уже парсонуть? 

    while (_work == RUN) {
        
        if (in) {//name of the arg file, c-string
            //open the file
            //read the string
            //lex and parse it
            //check result
            //do what result is need

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
                            //do what?
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
      
        } else {
            //читаем из стандартного ввода, отдаем лексеру, парсим валидный результат
        }


        if (true) {//todo debug?
            std::cout << "All works\n";//todo debug
            _work = STOP;
        }
    }
}