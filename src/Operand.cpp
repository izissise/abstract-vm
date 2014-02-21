#include "Operand.hpp"

template<typename T>
Operand<T>::Operand(const std::string& value, eOperandType type)
{
  _value = value;
  _type = type;
}

template<typename T>
Operand<T>::~Operand()
{
}

template<typename T>
const std::string& Operand<T>::toString() const
{
  return (_value);
}

template<typename T>
int Operand<T>::getPrecision() const
{
  return (_type);
}

template<typename T>
eOperandType Operand<T>::getType() const
{
  return (_type);
}

template<typename T>
IOperand* Operand<T>::operator+(const IOperand &rhs) const
{
  std::stringstream stream(toString());
  IOperand* npreci;
  Cpu& proc = Cpu::Instance();
  T tmpa;
  T tmp;
  T res;

  if (getPrecision() < rhs.getPrecision())
    {
      npreci = proc.createOperand(rhs.getType(), toString());
      return ((*npreci) + rhs);
    }
  stream >> tmpa;
  stream.clear();
  stream.str(rhs.toString());
  stream >> tmp;
  stream.clear();
  res = (tmpa + tmp);
  stream << res;
  return (proc.createOperand(_type, stream.str()));
}

template<typename T>
IOperand* Operand<T>::operator-(const IOperand &rhs) const
{
  std::stringstream stream(toString());
  IOperand* npreci;
  Cpu& proc = Cpu::Instance();
  T tmpa;
  T tmp;
  T res;

  if (getPrecision() < rhs.getPrecision())
    {
      npreci = proc.createOperand(rhs.getType(), toString());
      return ((*npreci) - rhs);
    }
  stream >> tmpa;
  stream.clear();
  stream.str(rhs.toString());
  stream >> tmp;
  stream.clear();
  res = (tmpa - tmp);
  stream << res;
  return (proc.createOperand(_type, stream.str()));
}

template<typename T>
IOperand* Operand<T>::operator*(const IOperand &rhs) const
{
  std::stringstream stream(toString());
  IOperand* npreci;
  Cpu& proc = Cpu::Instance();
  T tmpa;
  T tmp;
  T res;

  if (getPrecision() < rhs.getPrecision())
    {
      npreci = proc.createOperand(rhs.getType(), toString());
      return ((*npreci) * rhs);
    }
  stream >> tmpa;
  stream.clear();
  stream.str(rhs.toString());
  stream >> tmp;
  stream.clear();
  res = (tmpa * tmp);
  stream << res;
  return (proc.createOperand(_type, stream.str()));
}

template<typename T>
IOperand* Operand<T>::operator/(const IOperand &rhs) const
{
  std::stringstream stream(toString());
  IOperand* npreci;
  Cpu& proc = Cpu::Instance();
  T tmpa;
  T tmp;
  T res;

  if (getPrecision() < rhs.getPrecision())
    {
      npreci = proc.createOperand(rhs.getType(), toString());
      return ((*npreci) / rhs);
    }
  stream >> tmpa;
  stream.clear();
  stream.str(rhs.toString());
  stream >> tmp;
  stream.clear();
  if (tmp == 0)
    throw nFault("Division by zero");
  res = (tmpa / tmp);
  stream << res;
  return (proc.createOperand(_type, stream.str()));
}

template<typename T>
IOperand* Operand<T>::operator%(const IOperand &rhs) const
{
  std::stringstream stream(toString());
  IOperand* npreci;
  Cpu& proc = Cpu::Instance();
  T tmpa;
  T tmp;
  T res;

  if (getPrecision() < rhs.getPrecision())
    {
      npreci = proc.createOperand(rhs.getType(), toString());
      return ((*npreci) % rhs);
    }
  stream >> tmpa;
  stream.clear();
  stream.str(rhs.toString());
  stream >> tmp;
  stream.clear();
  if (tmp == 0)
    throw nFault("Modulo by zero");
  res = (tmpa % tmp);
  stream << res;
  return (proc.createOperand(_type, stream.str()));
}

template<>
IOperand* Operand<double>::operator%(const IOperand &rhs) const
{
  std::stringstream stream(toString());
  IOperand* npreci;
  Cpu& proc = Cpu::Instance();
  double tmpa;
  double tmp;
  double res;

  if (getPrecision() < rhs.getPrecision())
    {
      npreci = proc.createOperand(rhs.getType(), toString());
      return ((*npreci) % rhs);
    }
  stream >> tmpa;
  stream.clear();
  stream.str(rhs.toString());
  stream >> tmp;
  stream.clear();
  if (tmp == 0)
    throw nFault("Modulo by zero");
  res = std::fmod(tmpa, tmp);
  stream << res;
  return (proc.createOperand(_type, stream.str()));
}

template<>
IOperand* Operand<float>::operator%(const IOperand &rhs) const
{
  std::stringstream stream(toString());
  IOperand* npreci;
  Cpu& proc = Cpu::Instance();
  float tmpa;
  float tmp;
  float res;

  if (getPrecision() < rhs.getPrecision())
    {
      npreci = proc.createOperand(rhs.getType(), toString());
      return ((*npreci) % rhs);
    }
  stream >> tmpa;
  stream.clear();
  stream.str(rhs.toString());
  stream >> tmp;
  stream.clear();
  if (tmp == 0)
    throw nFault("Modulo by zero");
  res = std::fmod(tmpa, tmp);
  stream << res;
  return (proc.createOperand(_type, stream.str()));
}

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;
