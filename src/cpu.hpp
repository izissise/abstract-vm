#ifndef CPU_H
#define CPU_H

#include "EOperator.hpp"

class Cpu
{
public:
  typedef Operand<int8_t> Int8;
  typedef Operand<int16_t> Int16;
  typedef Operand<int32_t> Int32;
  typedef Operand<int64_t> Int64;
  typedef Operand<float> Float;
  typedef Operand<double> Double;

  Cpu();
  ~Cpu();
  IOperand *createOperand(eOperandType type, const std::string & value);
private:
  IOperand * createInt8(const std::string & value);
  IOperand * createInt16(const std::string & value);
  IOperand * createInt32(const std::string & value);
  IOperand * createFloat(const std::string & value);
  IOperand * createDouble(const std::string & value);
};

#endif // CPU_H
