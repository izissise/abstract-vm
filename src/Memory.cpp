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
  top();
  _stack.pop_front();
}

IOperand* Memory::top()
{
  IOperand* nb;
  if (_stack.empty())
    nFault("Regarder message a mettre un truc a propos du stack vide et de tenter de pop");
  nb = _stack.front();
  return (nb);
}

void Memory::dump()
{
  for (std::deque<IOperand*>::iterator it = _stack.begin(); it != _stack.end(); it++)
    std::cout << (*it)->toString() << std::endl;
}
