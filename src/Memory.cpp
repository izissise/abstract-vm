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
  delete top();
  _stack.pop_front();
}

IOperand* Memory::top(size_t i) const
{
  IOperand* nb;
  if (_stack.size() <= i)
    throw nFault("Stack is empty no top value");
  nb = _stack[i];
  return (nb);
}

void Memory::dump() const
{
  for (std::deque<IOperand*>::const_iterator it = _stack.begin(); it != _stack.end(); it++)
    std::cout << (*it)->toString() << std::endl;
}
