#ifndef OPERAND_HPP_INCLUDED
#define OPERAND_HPP_INCLUDED

#include <stdint-gcc.h>
#include "IOperator.hpp"

template<typename T>
class Operand : public IOperand
{
public:
  Operand(const std::string& value);
  virtual ~Operand();

  virtual int getPrecision();
  virtual eOperandType getType();

  virtual IOperand* operator+(const IOperand &rhs) const; // Somme
  virtual IOperand* operator-(const IOperand &rhs) const; // Difference
  virtual IOperand* operator*(const IOperand &rhs) const; // Produit
  virtual IOperand* operator/(const IOperand &rhs) const; // Quotient
  virtual IOperand* operator%(const IOperand &rhs) const; // Modulo

private:
  std::string _value;
};

template<typename T>
Operand<T>::Operand(const std::string& value)
{
  _value = value;
}

template<typename T>
Operand<T>::~Operand()
{
}

template<typename T>
int Operand<T>::getPrecision()
{
  return (sizeof(T));
}

template<typename T>
eOperandType Operand<T>::getType()
{
  return (sizeof(T)); //not this
}

template<typename T>
IOperand* Operand<T>::operator+(const IOperand &rhs) const
{

}

template<typename T>
IOperand* Operand<T>::operator-(const IOperand &rhs) const
{

}

template<typename T>
IOperand* Operand<T>::operator*(const IOperand &rhs) const
{

}

template<typename T>
IOperand* Operand<T>::operator/(const IOperand &rhs) const
{

}

template<typename T>
IOperand* Operand<T>::operator%(const IOperand &rhs) const
{

}

#endif // OPERAND_HPP_INCLUDED
