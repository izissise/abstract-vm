#ifndef CPU_H
#define CPU_H

#include <string>
#include <map>
#include <stdint.h>
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


  static Cpu& Instance();

  IOperand* createOperand(eOperandType type, const std::string& value);
private:
  static Cpu _instance;
  std::map<eOperandType, IOperand* (Cpu::*)(const std::string&)> _typemap;

private:
  Cpu& operator=(const Cpu&) {return (*this);};
  Cpu(const Cpu&) {};
  Cpu();
  ~Cpu();

  IOperand* createInt8(const std::string& value);
  IOperand* createInt16(const std::string& value);
  IOperand* createInt32(const std::string& value);
  IOperand* createFloat(const std::string& value);
  IOperand* createDouble(const std::string& value);
};

#endif // CPU_H
