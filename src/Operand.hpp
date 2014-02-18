#ifndef OPERAND_HPP_INCLUDED
#define OPERAND_HPP_INCLUDED

#include "IOperator.hpp"

template<typename T>
class Operand : public IOperand
{
public:
  Operand(const std::string& value);
  virtual ~Operand();

  virtual int getPrecision();
  virtual eOperandType getType();

  virtual IOperand* operator+(const IOperand &rhs); // Somme
  virtual IOperand* operator-(const IOperand &rhs); // Difference
  virtual IOperand* operator*(const IOperand &rhs); // Produit
  virtual IOperand* operator/(const IOperand &rhs); // Quotient
  virtual IOperand* operator%(const IOperand &rhs); // Modulo

private:
  std::string _value;
};

template<>
Operand::Operand(const std::string& value)
{
  _value = value;
}

template<>
Operand::~Operand()
{
}

template<>
int Operand::getPrecision()
{
  return (sizeof(T));
}

template<>
int Operand::getType()
{
  return (sizeof(T)); //not this
}

#endif // OPERAND_HPP_INCLUDED
