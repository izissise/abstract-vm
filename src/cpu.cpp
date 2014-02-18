#include "Cpu.h"

Cpu::Cpu()
{
  _typemap[::Int8] = &createInt8;
  _typemap[::Int16] = &createInt16;
  _typemap[::Int32] = &createInt32;
  _typemap[::Float] = &createFloat;
  _typemap[::Double] = &createDouble;
}

Cpu::~Cpu()
{
}

IOperand* Cpu::createInt8(const std::string& value)
{
  return(new Int8(value, ::Int8));
}

IOperand* Cpu::createInt16(const std::string& value)
{
  return(new Int16(value, ::Int16));
}

IOperand* Cpu::createInt32(const std::string& value)
{
  return(new Int32(value, ::Int32)):
  }

IOperand* Cpu::createFloat(const std::string& value)
{
  return(new Float(value, ::Float));
}

IOperand* Cpu::createDouble(const std::string& value)
{
  return(new Double(value, ::Double));
}

IOperand* Cpu::createOperand(eOperandType type, const std::string& value)
{
  return(_typemap[type](value));
}


