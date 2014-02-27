#include <limits>
#include "Operand.hpp"

template<typename T>
Operand<T>::Operand(const std::string& value, eOperandType type)
{
  std::stringstream rvalue(value);

  _value = convertFromRType(convertToRType(value));
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
T Operand<T>::convertToRType(const std::string& value) const
{
  std::stringstream stream(value);
  T ret;

  if (!(stream >> ret))
    throw nFault("Under/Overflow on " + value + ".");
  return (ret);
}

template<>
int8_t Operand<int8_t>::convertToRType(const std::string& value) const
{
  std::stringstream stream(value);
  int ret;

  if (!(stream >> ret))
    throw nFault("Under/Overflow on " + value + ".");
  if (ret > std::numeric_limits<int8_t>::max() || ret < std::numeric_limits<int8_t>::min())
    throw nFault("Under/Overflow on " + value + ".");
  return (static_cast<int8_t>(ret));
}

template<typename T>
std::string Operand<T>::convertFromRType(T value) const
{
  std::stringstream stream;

  stream << value;
  return (stream.str());
}

template<>
std::string Operand<int8_t>::convertFromRType(int8_t value) const
{
  std::stringstream stream;

  stream << static_cast<int>(value);
  return (stream.str());
}

template<typename T>
IOperand* Operand<T>::operator+(const IOperand &rhs) const
{
  IOperand* npreci;
  IOperand* ntmp;
  Cpu& proc = Cpu::Instance();
  T tmpa;
  T tmp;
  T res;

  if (getPrecision() < rhs.getPrecision())
    {
      npreci = proc.createOperand(rhs.getType(), toString());
      ntmp = (*npreci) + rhs;
      delete npreci;
      return (ntmp);
    }
  tmpa = convertToRType(toString());
  tmp = convertToRType(rhs.toString());
  if (((tmp > 0) && (tmpa > std::numeric_limits<T>::max() - tmp))
      || ((tmp < 0) && (tmpa < std::numeric_limits<T>::min() - tmp)))
    throw nFault("Under/Overflow on " + _value + " + " + rhs.toString());
  res = (tmpa + tmp);
  return (proc.createOperand(_type, convertFromRType(res)));
}

template<typename T>
IOperand* Operand<T>::operator-(const IOperand &rhs) const
{
  IOperand* npreci;
  IOperand* ntmp;
  Cpu& proc = Cpu::Instance();
  T tmpa;
  T tmp;
  T res;

  if (getPrecision() < rhs.getPrecision())
    {
      npreci = proc.createOperand(rhs.getType(), toString());
      ntmp = (*npreci) - rhs;
      delete npreci;
      return (ntmp);
    }
  tmpa = convertToRType(toString());
  tmp = convertToRType(rhs.toString());
  if (((tmp < 0) && (tmpa > std::numeric_limits<T>::max() + tmp))
      || ((tmp > 0) && (tmpa < std::numeric_limits<T>::min() + tmp)))
    throw nFault("Under/Overflow on " + _value + " - " + rhs.toString());
  res = (tmpa - tmp);
  return (proc.createOperand(_type, convertFromRType(res)));
}

template<typename T>
IOperand* Operand<T>::operator*(const IOperand &rhs) const
{
  IOperand* npreci;
  IOperand* ntmp;
  Cpu& proc = Cpu::Instance();
  T tmpa;
  T tmp;
  T res;

  if (getPrecision() < rhs.getPrecision())
    {
      npreci = proc.createOperand(rhs.getType(), toString());
      ntmp = (*npreci) * rhs;
      delete npreci;
      return (ntmp);
    }
  tmpa = convertToRType(toString());
  tmp = convertToRType(rhs.toString());
  /* if (((tmp > 0) && (tmpa > std::numeric_limits<T>::max() / tmp))
       || ((tmp < 0) && (tmpa < std::numeric_limits<T>::min() / tmp)))
     throw nFault("Under/Overflow on " + _value + " * " + rhs.toString());*/
  res = (tmpa * tmp);
  return (proc.createOperand(_type, convertFromRType(res)));
}

template<typename T>
IOperand* Operand<T>::operator/(const IOperand &rhs) const
{
  IOperand* npreci;
  IOperand* ntmp;
  Cpu& proc = Cpu::Instance();
  T tmpa;
  T tmp;
  T res;

  if (getPrecision() < rhs.getPrecision())
    {
      npreci = proc.createOperand(rhs.getType(), toString());
      ntmp = (*npreci) / rhs;
      delete npreci;
      return (ntmp);
    }
  tmpa = convertToRType(toString());
  tmp = convertToRType(rhs.toString());
  if (tmp == 0)
    throw nFault("Division by zero");
  /* if (((tmp > 0) && (tmpa > std::numeric_limits<T>::max() / tmp))
       || ((tmp < 0) && (tmpa < std::numeric_limits<T>::min() / tmp)))
     throw nFault("Under/Overflow on " + _value + " - " + rhs.toString());*/
  res = (tmpa / tmp);
  return (proc.createOperand(_type, convertFromRType(res)));
}

template<typename T>
IOperand* Operand<T>::operator%(const IOperand &rhs) const
{
  IOperand* npreci;
  IOperand* ntmp;
  Cpu& proc = Cpu::Instance();
  T tmpa;
  T tmp;
  T res;

  if (getPrecision() < rhs.getPrecision())
    {
      npreci = proc.createOperand(rhs.getType(), toString());
      ntmp = (*npreci) % rhs;
      delete npreci;
      return (ntmp);
    }
  tmpa = convertToRType(toString());
  tmp = convertToRType(rhs.toString());
  if (tmp == 0)
    throw nFault("Modulo by zero");
  res = (tmpa % tmp);
  return (proc.createOperand(_type, convertFromRType(res)));
}

template<>
IOperand* Operand<double>::operator%(const IOperand &rhs) const
{
  IOperand* npreci;
  IOperand* ntmp;
  Cpu& proc = Cpu::Instance();
  double tmpa;
  double tmp;
  double res;

  if (getPrecision() < rhs.getPrecision())
    {
      npreci = proc.createOperand(rhs.getType(), toString());
      ntmp = (*npreci) % rhs;
      delete npreci;
      return (ntmp);
    }
  tmpa = convertToRType(toString());
  tmp = convertToRType(rhs.toString());
  if (tmp == 0)
    throw nFault("Modulo by zero");
  res = std::fmod(tmpa, tmp);
  return (proc.createOperand(_type, convertFromRType(res)));
}

template<>
IOperand* Operand<float>::operator%(const IOperand &rhs) const
{
  IOperand* npreci;
  IOperand* ntmp;
  Cpu& proc = Cpu::Instance();
  float tmpa;
  float tmp;
  float res;

  if (getPrecision() < rhs.getPrecision())
    {
      npreci = proc.createOperand(rhs.getType(), toString());
      ntmp = (*npreci) % rhs;
      delete npreci;
      return (ntmp);
    }
  tmpa = convertToRType(toString());
  tmp = convertToRType(rhs.toString());
  if (tmp == 0)
    throw nFault("Modulo by zero");
  res = std::fmod(tmpa, tmp);
  return (proc.createOperand(_type, convertFromRType(res)));
}

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;
