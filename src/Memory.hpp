#ifndef MEMORY_H
#define MEMORY_H

#include <deque>
#include <iostream>
#include <iterator>
#include "Fault.hpp"
#include "IOperator.hpp"

class Memory
{
public:
  Memory();
  ~Memory();

  void push(IOperand* nb);
  void pop();
  IOperand* top() const;
  void dump() const;
private:
  std::deque<IOperand*> _stack;
};

#endif // MEMORY_H
