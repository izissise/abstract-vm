#ifndef CPU_H
#define CPU_H

#include "EOperator.hpp"

class Cpu
{
	public:
		Cpu();
		~Cpu();
		IOperand *createOperand(eOperandType type, const std::string & value);
	private:
		IOperand * createInt8(const std::string & value);
		IOperand * createInt16(const std::string & value);
		IOperand * createInt32(const std::string & value);
		IOperand * createFloat(const std::string & value);
		IOperand * createDouble(const std::string & value);
};

#endif // CPU_H
