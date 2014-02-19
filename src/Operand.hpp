#ifndef OPERAND_HPP_INCLUDED
#define OPERAND_HPP_INCLUDED

#include <stdint.h>
#include <string>
#include <sstream>
#include "cpu.hpp"
#include "EOperator.hpp"
#include "IOperator.hpp"

template<typename T>
class Operand : public IOperand
{
public:
  Operand(const std::string& value, eOperandType type);
  virtual ~Operand();

  virtual const std::string& toString() const;
  virtual int getPrecision() const;
  virtual eOperandType getType() const;

  virtual IOperand* operator+(const IOperand &rhs) const; // Somme
  virtual IOperand* operator-(const IOperand &rhs) const; // Difference
  virtual IOperand* operator*(const IOperand &rhs) const; // Produit
  virtual IOperand* operator/(const IOperand &rhs) const; // Quotient
  virtual IOperand* operator%(const IOperand &rhs) const; // Modulo

private:
  std::string _value;
  eOperandType _type;
};

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
  tmpa << stream;
  stream.clear();
  stream.str(rhs.toString());
  tmp << stream;
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
  tmpa << stream;
  stream.clear();
  stream.str(rhs.toString());
  tmp << stream;
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
  tmpa << stream;
  stream.clear();
  stream.str(rhs.toString());
  tmp << stream;
  stream.clear();
  res = (tmpa * tmp);
  stream << res;
  return (proc.createOperand(_type, stream.str()));
}

template<typename T>
IOperand* Operand<T>::operator/(const IOperand &rhs) const //throw an exception in case of float double
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
  tmpa << stream;
  stream.clear();
  stream.str(rhs.toString());
  tmp << stream;
  stream.clear();
  res = (tmpa / tmp);
  stream << res;
  return (proc.createOperand(_type, stream.str()));
}

template<typename T>
IOperand* Operand<T>::operator%(const IOperand &rhs) const //throw an exception in case of float double
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
  tmpa << stream;
  stream.clear();
  stream.str(rhs.toString());
  tmp << stream;
  stream.clear();
  res = (tmpa % tmp);
  stream << res;
  return (proc.createOperand(_type, stream.str()));
}

#endif // OPERAND_HPP_INCLUDED

