#ifndef OPERAND_HPP_INCLUDED
#define OPERAND_HPP_INCLUDED

#include <stdint-gcc.h>
#include "EOperator.hpp"
#include "IOperator.hpp"

template<typename T>
class Operand : public IOperand
{
public:
  Operand(const std::string& value, eOperandType type);
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
int Operand<T>::getPrecision()
{
  return (_type);
}

template<typename T>
eOperandType Operand<T>::getType()
{
  return (_type); //not this
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
