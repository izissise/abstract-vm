#include <iostream>
#include "Fault.hpp"

int main()
{
  try
    {

    }
  catch (Fault& e)
    {
      std::cerr << e.what() << std::endl;
    }
  return 0;
}

