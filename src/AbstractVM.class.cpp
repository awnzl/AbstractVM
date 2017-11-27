#include "AbstractVM.hpp"

AbstractVM::AbstractVM() : work(RUN) {}

AbstractVM::~AbstractVM() {
    //todo free pointers in stack
}

AbstractVM::AbstractVM(const AbstractVM &avm) {
    this->work = avm.work;
    this->avmStack = avm.avmStack;
    this->factory = avm.factory;
    //...
}

AbstractVM &AbstractVM::operator=(AbstractVM &avm) {
    this->work = avm.work;
    this->avmStack = avm.avmStack;
    this->factory = avm.factory;
    //...
    return (*this);
}

void AbstractVM::push(std::string &operand, std::string &value) {
    const IOperand *op = NULL;

    if (operand == "int8")
        op = factory.createOperand(eOperandType::INT8, value);
    else if (operand == "int16")
        op = factory.createOperand(eOperandType::INT16, value);
    else if (operand == "int32")
        op = factory.createOperand(eOperandType::INT32, value);
    else if (operand == "float")
        op = factory.createOperand(eOperandType::FLOAT, value);
    else if (operand == "double")
        op = factory.createOperand(eOperandType::DOUBLE, value);
    else
        throw std::runtime_error("avm: some truble in push func - wrong operand string value?");

    if (op)
        avmStack.push(op);
    else
        throw std::runtime_error("avm: some truble in push func - op is NULL?");
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

    while (work == RUN) {
        
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
                    tok = AVMLexer::getLexer().lexIt(buff);
                    if (tok && tok->type == AVMToken::TokenType::PUSH) {
                        push(tok->operand, tok->value);
                    } else if (tok && tok->type == AVMToken::TokenType::ASSERT) {
                        //
                    }
                }

                ifs.close();
            } catch (std::exception &ex) {
                //todo обработать исключения
                std::cout << ex.what() << std::endl;
            }

            AVMStack<const IOperand*>::iterator st = avmStack.begin();
            AVMStack<const IOperand*>::iterator en = avmStack.end();

            while (st != en) {
                std::cout << "--> " << (*st++)->toString() << std::endl;
            }
            
        } else {
            //читаем из стандартного ввода, отдаем лексеру, парсим валидный результат
        }


        if (true)
            std::cout << "All works\n";
            work = STOP;
    }
}