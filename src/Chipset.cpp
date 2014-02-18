/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/
#include "Chipset.hpp"

Chipset::Chipset(std::string filename)
{
  std::ifstream ifs(filename.c_str());
  if (!ifs.is_open())
	nFault("Error openning \"" + filename + "\"\n");
  std::string content((std::istreambuf_iterator<char>(ifs) ),
					(std::istreambuf_iterator<char>()));
	//ctor
}

Chipset::Chipset(int fd)
{

	//ctor
}

Chipset::~Chipset()
{
	//dtor
}
