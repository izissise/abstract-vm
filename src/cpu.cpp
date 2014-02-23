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
  _exited = false;
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
  _ram.push(nb);
}

void Cpu::pop()
{
  IOperand* a;

  a = _ram.top();
  _ram.pop();
  delete a;
}

void Cpu::dump() const
{
  _ram.dump();
}

void Cpu::assert(IOperand* nb) const
{
  IOperand* tnb = _ram.top();

  if (nb->getType() == tnb->getType())
    {
      double tmpa;
      double tmpb;
      std::stringstream a(nb->toString());
      std::stringstream b(tnb->toString());
      a >> tmpa;
      b >> tmpb;
      if (tmpa == tmpb)
        return;
    }
  throw nFault("Assert failed");
}

void Cpu::add()
{
  IOperand* a;
  IOperand* b;

  a = _ram.top();
  _ram.pop();
  b = _ram.top();
  _ram.pop();
  _ram.push((*a) + (*b));
}

void Cpu::sub()
{
  IOperand* a;
  IOperand* b;

  a = _ram.top();
  _ram.pop();
  b = _ram.top();
  _ram.pop();
  _ram.push((*a) - (*b));
}

void Cpu::mul()
{
  IOperand* a;
  IOperand* b;

  a = _ram.top();
  _ram.pop();
  b = _ram.top();
  _ram.pop();
  _ram.push((*a) * (*b));
}

void Cpu::div()
{
  IOperand* a;
  IOperand* b;

  a = _ram.top();
  _ram.pop();
  b = _ram.top();
  _ram.pop();
  _ram.push((*a) / (*b));
}

void Cpu::mod()
{
  IOperand* a;
  IOperand* b;

  a = _ram.top();
  _ram.pop();
  b = _ram.top();
  _ram.pop();
  _ram.push((*a) % (*b));
}

void Cpu::print() const
{
  IOperand* nb = _ram.top();
  std::stringstream stream(nb->toString());
  int tmpnb;

  if (nb->getType() != ::Int8)
    throw nFault("Print: Not a Int8");
  stream >> tmpnb;
  std::cout << static_cast<char>(tmpnb) << std::endl;
}

void Cpu::exit()
{
  _exited = true;
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
