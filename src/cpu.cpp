#include "cpu.hpp"
#include "Operand.hpp"

Cpu Cpu::_instance = Cpu();

Cpu::Cpu()
{
  _typemap[::Int8] = &Cpu::createInt8;
  _typemap[::Int16] = &Cpu::createInt16;
  _typemap[::Int32] = &Cpu::createInt32;
  _typemap[::Float] = &Cpu::createFloat;
  _typemap[::Double] = &Cpu::createDouble;
}

Cpu::~Cpu()
{
}

Cpu& Cpu::Instance()
{
  return (_instance);
}

void Cpu::push(IOperand* nb)
{
  //push on memory
}

IOperand* Cpu::pop()
{
  //pop from memory
  return (NULL);
}

void Cpu::dump()
{
}

bool Cpu::assert(IOperand* nb) const
{
  return (true);
}


void Cpu::add()
{

}

void Cpu::sub()
{

}

void Cpu::mul()
{

}

void Cpu::div()
{

}

void Cpu::mod()
{

}

void Cpu::print() const
{

}

void Cpu::exit() const
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
  return(new Int32(value, ::Int32));
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
  return((this->*(_typemap.at(type)))(value));
}
