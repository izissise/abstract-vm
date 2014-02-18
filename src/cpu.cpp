#include "Cpu.h"

Cpu::Cpu()
{
    //ctor
}

Cpu::~Cpu()
{
    //dtor
}

IOperand * Cpu::createInt8(const std::string & value)
{
	return(new Int8(value);)
}

IOperand * Cpu::createInt16(const std::string & value)
{
	return(new Int8(value);)
}

IOperand * Cpu::createInt32(const std::string & value)
{
	return(new Int8(value);)
}

IOperand * Cpu::createFloat(const std::string & value)
{
	return(new Int8(value);)
}

IOperand * Cpu::createDouble(const std::string & value)
{
	return(new Int8(value);)
}

IOperand *Cpu::createOperand(eOperandType type, const std::string & value)
{
    std::map<eOperandType,IOperand*(*)(const std::string &)> createType;

    createType[Int8]=&createInt8;
    createType[Int16]=&createInt16;
    createType[Int32]=&createInt32;
    createType[Float]=&createFloat;
    createType[Double]=&createDouble;
    return(createType[type](value));
}
