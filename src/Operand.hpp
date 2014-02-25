#ifndef OPERAND_HPP_INCLUDED
#define OPERAND_HPP_INCLUDED

#include <stdint.h>
#include <string>
#include <sstream>
#include <cmath>
#include "cpu.hpp"
#include "EOperator.hpp"
#include "IOperator.hpp"

template<typename T>
class Operand : public IOperand
{
public:
  explicit Operand(const std::string& value, eOperandType type);
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
  T convertToRType(const std::string& value) const;
  std::string convertFromRType(T value) const;

  std::string _value;
  eOperandType _type;
};

#endif // OPERAND_HPP_INCLUDED
