#ifndef CPU_H
#define CPU_H

#include <string>

#include "IOperator.hpp"
#include "EOperator.hpp"

template<typename T>
class Operand;

class Cpu
{
public:
  typedef Operand<int8_t> Int8;
  typedef Operand<int16_t> Int16;
  typedef Operand<int32_t> Int32;
  typedef Operand<float> Float;
  typedef Operand<double> Double;

  Cpu();
  ~Cpu();
  static IOperand *createOperand(eOperandType type, const std::string & value);
private:
  static IOperand * createInt8(const std::string & value);
  static IOperand * createInt16(const std::string & value);
  static IOperand * createInt32(const std::string & value);
  static IOperand * createFloat(const std::string & value);
  static IOperand * createDouble(const std::string & value);
};

#endif // CPU_H
