#include "Operand.hpp"

template<typename T>
Operand<T>::Operand(const std::string& value, eOperandType type)
{
  std::stringstream rvalue(value);
  T tmp;

  rvalue >> tmp;
  rvalue.clear();
  rvalue << tmp;
  _value = rvalue.str();
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
T Operand<T>::convertToRType(std::string value) const
{
  std::stringstream stream(value);
  T ret;

  if (!(stream >> ret))
    throw nFault("Can't convert " + value + " to type.");
  return (ret);
}

template<typename T>
IOperand* Operand<T>::operator+(const IOperand &rhs) const
{
  std::stringstream stream;
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
  tmpa = convertToRType(toString());
  tmp = convertToRType(rhs.toString());
 /* if (((tmp > 0) && (tmpa > INT_MAX - tmp)) || ((tmp < 0) && (tmpa < INT_MIN - tmp)))
    throw nFault("Overflow/Underflow");*/
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
  tmpa = convertToRType(toString());
  tmp = convertToRType(rhs.toString());
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
  tmpa = convertToRType(toString());
  tmp = convertToRType(rhs.toString());
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
  tmpa = convertToRType(toString());
  tmp = convertToRType(rhs.toString());
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
  tmpa = convertToRType(toString());
  tmp = convertToRType(rhs.toString());
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
  tmpa = convertToRType(toString());
  tmp = convertToRType(rhs.toString());
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
  tmpa = convertToRType(toString());
  tmp = convertToRType(rhs.toString());
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
