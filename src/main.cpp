#include <iostream>
#include <string>
#include "cpu.hpp"
#include "Chipset.hpp"
#include "Fault.hpp"

int main(int argc, char **argv)
{
  Chipset chip;

  try
    {
      if (argc == 1)
        chip.parser();
      else
        chip.parser(std::string(argv[1]));
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  return 0;
}
