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
  _ram.pop();
}

void Cpu::dump() const
{
  _ram.dump();
}

void Cpu::assert(const IOperand* nb) const
{
  IOperand* tnb = _ram.top();
  std::string tmpa = nb->toString();
  std::string tmpb = tnb->toString();

  if (nb->getType() == tnb->getType())
    {
      if (tmpa == tmpb)
        {
          delete nb;
          return;
        }
    }
  delete nb;
  throw nFault(std::string("Assert(") + tmpa + " == " + tmpb + ") failed.");
}

void Cpu::add()
{
  IOperand* a;
  IOperand* b;
  IOperand* res;

  a = _ram.top(1);
  b = _ram.top();
  res = (*a) + (*b);
  _ram.pop();
  _ram.pop();
  _ram.push(res);
}

void Cpu::sub()
{
  IOperand* a;
  IOperand* b;
  IOperand* res;

  a = _ram.top(1);
  b = _ram.top();
  res = (*a) - (*b);
  _ram.pop();
  _ram.pop();
  _ram.push(res);
}

void Cpu::mul()
{
  IOperand* a;
  IOperand* b;
  IOperand* res;

  a = _ram.top(1);
  b = _ram.top();
  res = (*a) * (*b);
  _ram.pop();
  _ram.pop();
  _ram.push(res);
}

void Cpu::div()
{
  IOperand* a;
  IOperand* b;
  IOperand* res;

  a = _ram.top(1);
  b = _ram.top();
  res = (*a) / (*b);
  _ram.pop();
  _ram.pop();
  _ram.push(res);
}

void Cpu::mod()
{
  IOperand* a;
  IOperand* b;
  IOperand* res;

  a = _ram.top(1);
  b = _ram.top();
  res = (*a) % (*b);
  _ram.pop();
  _ram.pop();
  _ram.push(res);
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

int Cpu::jmp(IOperand* nb)
{
  int res;
  std::stringstream stream(nb->toString());

  if (nb->getType() != ::Int8)
    throw nFault("Type for jmp must be Int8");
  stream >> res;
  if (_ram.top()->toString() != std::string("0"))
    return (res);
  return (0);
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
