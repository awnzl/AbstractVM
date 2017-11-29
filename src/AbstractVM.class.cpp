#include "AbstractVM.hpp"

//todo debug
#include <typeinfo>

AbstractVM::AbstractVM() : _work(RUN) {}

AbstractVM::~AbstractVM() {
    //todo free pointers in stack
}

AbstractVM::AbstractVM(const AbstractVM &avm) {
    this->_work = avm._work;
    this->_avmStack = avm._avmStack;
    //...
}

AbstractVM &AbstractVM::operator=(AbstractVM &avm) {
    this->_work = avm._work;
    this->_avmStack = avm._avmStack;
    //...
    return (*this);
}

const IOperand *AbstractVM::produceOperand(std::string &operand, std::string &value) {
    const IOperand *op = NULL;

    if (operand == "int8")
        op = OperandsFactory::getFactory().createOperand(eOperandType::INT8, value);
    else if (operand == "int16")
        op = OperandsFactory::getFactory().createOperand(eOperandType::INT16, value);
    else if (operand == "int32")
        op = OperandsFactory::getFactory().createOperand(eOperandType::INT32, value);
    else if (operand == "float")
        op = OperandsFactory::getFactory().createOperand(eOperandType::FLOAT, value);
    else if (operand == "double")
        op = OperandsFactory::getFactory().createOperand(eOperandType::DOUBLE, value);
    else
        throw std::runtime_error("avm: some truble in push or assert func - wrong operand string value?");

    return (op);
}

void AbstractVM::push(std::string &operand, std::string &value) {
    _avmStack.push(produceOperand(operand, value));
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
    const IOperand *op = produceOperand(operand, value);
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
    std::cout << "add first: " << first->toString() << std::endl;
    std::cout << "add second: " << second->toString() << std::endl;
    
    const IOperand *res = (*second) + (*first);
    std::cout << "add res: " << res->toString() << std::endl;
    delete (first);
    delete (second);
    
    _avmStack.push(res);

}

void AbstractVM::run(char *in = NULL) {
    //получает отвалидированные данные и начинает свое дело...
    //нужно обрабатывать эксепшены, чтобы выполнение программы не прерывалось на этом,
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
                        }
                    }
                }

                ifs.close();
            } catch (std::exception &ex) {
                //todo обработать исключения
                std::cout << ex.what() << std::endl;
            }
/*          WARNING!!!         */
/*где-то не срабатывает присвоение типов или что-то такое
и в итоге в операнде на самом деле хз что происходит - кругом тип
s на возврате от typeid(_value).name()*/
/*                             */
        std::cout << "First Dump and Add:\n";
        dump();
        add();
        std::cout << "\n";
        std::cout << "Second Dump and Add:\n";
        dump();
        add();
        std::cout << "\n";
        std::cout << "Third Dump and Add:\n";
        dump();
        add();
        std::cout << "\n";
        std::cout << "Last Dump:\n";
        dump();

       
        } else {
            //читаем из стандартного ввода, отдаем лексеру, парсим валидный результат
        }


        if (true)
            std::cout << "All works\n";
            _work = STOP;
    }
}