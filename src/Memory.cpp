/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/
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

IOperand* Memory::pop()
{
  IOperand* nb;
  if (_stack.empty())
    nFault("Regarder message a mettre un truc a propos du stack vide et de tenter de pop");
  nb = _stack.front();
  _stack.pop_front();
  return (nb);
}

void Memory::dump()
{
}
