#include "cpu.h"

cpu::cpu()
{
    //ctor
}

cpu::~cpu()
{
    //dtor
}

IOperand * createInt8(const std::string & value)
{
	return(new Int8(value);)
}

IOperand * createInt16(const std::string & value)
{
	return(new Int8(value);)
}

IOperand * createInt32(const std::string & value)
{
	return(new Int8(value);)
}

IOperand * createFloat(const std::string & value)
{
	return(new Int8(value);)
}

IOperand * createDouble(const std::string & value)
{
	return(new Int8(value);)
}

IOperand *cpu::createOperand(eOperandType type, const std::string & value)
{
    std::map<eOperandType,IOperand*(*)(const std::string &)> createType;

    createType[Int8]=&createInt8;
    createType[Int16]=&createInt16;
    createType[Int32]=&createInt32;
    createType[Float]=&createFloat;
    createType[Double]=&createDouble;
    return(createType[type](value));
}
