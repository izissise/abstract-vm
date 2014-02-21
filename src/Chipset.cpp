#include  <cstdlib>
#include "Chipset.hpp"

/*
  TODO:
  -parseur qui zap les espace
  -parseIsOperator
  -parseIsType
*/

Chipset::Chipset(const std::string &filename)
  : _currentCpu(Cpu::Instance())
{
  std::string line;
  std::vector<std::string> content;
  std::ifstream ifs(filename.c_str());
  unsigned int i = 0;

  setOperand();
  setOperators();
  if (!ifs.is_open())
    nFault("Error openning '" + filename + "'\n");
  while(std::getline(ifs, line))
    {
      if (line.substr(line.find_first_not_of(" "), 1) != ";")
        {
          content.push_back(line);
          i++;
        }
    }
  if (content[i - 1] != std::string("exit"))
    throw nFault("Error there is no 'exit' at the end of file\n");
  i = 0;
  while (i < content.size())
    {
      parse(content[i]);
      i++;
    }
  //ctor
}

Chipset::Chipset()
  : _currentCpu(Cpu::Instance())
{
  std::string line;
  std::vector<std::string> content;
  unsigned int i = 0;

  setOperand();
  setOperators();
  while(std::getline(std::cin, line) && line != ";;")
    {
      if (line.substr(line.find_first_not_of(" "), 1) != ";")
        {
          content.push_back(line);
          i++;
        }

    }
  if (content[i - 1] != std::string("exit"))
    throw nFault("Error there is no 'exit' at the end of file\n");
  i = 0;
  while (i < content.size())
    {
      parse(content[i]);
      i++;
    }
  //ctor
}

Chipset::~Chipset()
{
  //dtor
}

void	Chipset::setOperators()
{
  _operators["pop"] = &Cpu::pop;
  _operators["add"] = &Cpu::add;
  _operators["sub"] = &Cpu::sub;
  _operators["mul"] = &Cpu::mul;
  _operators["div"] = &Cpu::div;
  _operators["mod"] = &Cpu::mod;
  _operatorsConst["dump"] = &Cpu::dump;
  _operatorsConst["print"] = &Cpu::print;
  _operatorsConst["exit"] = &Cpu::exit;
}

void	Chipset::setOperand()
{
  _typemap["Int8"] = ::Int8;
  _typemap["Int16"] = ::Int16;
  _typemap["Int32"] = ::Int32;
  _typemap["Float"] = ::Float;
  _typemap["Double"] = ::Double;
}

IOperand	*Chipset::getOperand(std::string str)
{
  eOperandType typeOperand;
  std::string value;

  try {
      typeOperand = _typemap.at(str.substr(str.find(" ") + 1, str.find("(") - (str.find(" ") + 1)));
    }
  catch (std::out_of_range&  e) {
      throw nFault("Error type '" + str.substr(str.find(" ") + 1, str.find("(") - (str.find(" ") + 1)) + "' doesn't exist\n");
    }
  value = str.substr(str.find("(") + 1, str.find(")") - 1 - str.find("("));
  return (_currentCpu.createOperand(typeOperand, value));
}

void	Chipset::parse(std::string str)
{
  void (Cpu::*ptr)(void);
  void (Cpu::*ptr2)(void) const;

  parseIsOperator(str);
  parseIsType(str);
  if (str.substr(0, str.find(" ")) == "push")
    _currentCpu.push(getOperand(str));
  else if (str.substr(0, str.find(" ")) == "assert")
    _currentCpu.assert(getOperand(str));
  else
    {
      try
        {
          ptr = _operators.at(str.substr(0, str.find(" ")));
          (_currentCpu.*ptr)();
        }
      catch(std::out_of_range e)
        {
          try
            {
              ptr2 = _operatorsConst.at(str.substr(0, str.find(" ")));
              (_currentCpu.*ptr2)();
            }
          catch(std::out_of_range e)
            {
              throw nFault("Error operator '" + str.substr(0, str.find(" ")) + "' doesn't exist\n");
            }
        }
    }
}

void	Chipset::parseIsOperator(std::string str)
{
  str = "toto";
}

void	Chipset::parseIsType(std::string str)
{
  str = "titi";
}
