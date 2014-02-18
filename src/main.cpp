#include <iostream>
#include "cpu.hpp"
#include "Fault.hpp"

int main()
{
  Cpu& proc = Cpu::Instance();

  try
    {

    }
  catch (Fault& e)
    {
      std::cerr << e.what() << std::endl;
    }
  return 0;
}

