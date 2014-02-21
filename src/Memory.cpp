#include "Memory.hpp"

Memory::Memory()
{
}

Memory::~Memory()
{
}

void Memory::push(IOperand* nb)
{
  _stack.push_front(nb);
}

void Memory::pop()
{
  if (_stack.empty())
    throw nFault("Stack is empty can't pop");
  _stack.pop_front();
}

IOperand* Memory::top() const
{
  IOperand* nb;
  if (_stack.empty())
    throw nFault("Stack is empty no top value");
  nb = _stack.front();
  return (nb);
}

void Memory::dump() const
{
  for (std::deque<IOperand*>::const_iterator it = _stack.begin(); it != _stack.end(); it++)
    std::cout << (*it)->toString() << std::endl;
}
