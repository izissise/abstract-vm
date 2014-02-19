#ifndef MEMORY_H
#define MEMORY_H

#include <deque>
#include "Fault.hpp"
#include "IOperator.hpp"

class Memory
{
public:
  Memory();
  ~Memory();

  void push(IOperand* nb);
  IOperand* pop();
  void dump();
private:
  std::deque<IOperand*> _stack;
};

#endif // MEMORY_H
