#include  <cstdlib>
#include "Chipset.hpp"


Chipset::Chipset()
  : _currentCpu(Cpu::Instance())
{
  setOperand();
  setOperators();
}

void	Chipset::parser(const std::string &filename)
{
  std::string line;
  std::ifstream ifs(filename.c_str());
  unsigned int i = 0;

  if (!ifs.is_open())
    throw nFault("Error openning '" + filename + "'\n");
  while(std::getline(ifs, line))
    parsing(line);
  i = 0;
  while (i < content.size() && _currentCpu.getExit() == false)
    i += parse(content[i]);
  if (_currentCpu.getExit() == false)
    throw nFault("Error there is no 'exit'\n");

}

void	Chipset::parser()
{
  std::string line;
  std::string tmp;
  unsigned int i = 0;

  while(std::getline(std::cin, line) && (tmp = line) != ";;")
    parsing(line);
  if (tmp != ";;")
    throw nFault("Error there is no ;; at end of file\n");
  i = 0;
  while (i < content.size() && _currentCpu.getExit() == false)
    i += parse(content[i]);
  if (_currentCpu.getExit() == false)
    throw nFault("Error there is no 'exit'\n");
}

Chipset::~Chipset()
{
}

void          Chipset::parsing(std::string &line)
{
  size_t find;

  find = line.find("  ");
  while (std::string::npos != find)
    {
      line.erase(find, 1);
      find = line.find("  ");
    }
  find = line.find_first_not_of(" ");
  if (std::string::npos != find)
    line.erase(0, find);
  if (line.substr(0, 1) != ";")
    {
      find = line.find(";");
      if (std::string::npos != find)
        line.erase(find, line.size() - find);
      if (line.size() != 0)
        content.push_back(line);
    }
}

void	Chipset::setOperators()
{
  _operators["pop"] = &Cpu::pop;
  _operators["add"] = &Cpu::add;
  _operators["sub"] = &Cpu::sub;
  _operators["mul"] = &Cpu::mul;
  _operators["div"] = &Cpu::div;
  _operators["mod"] = &Cpu::mod;
  _operators["exit"] = &Cpu::exit;
  _operatorsConst["dump"] = &Cpu::dump;
  _operatorsConst["print"] = &Cpu::print;
}

void	Chipset::setOperand()
{
  _typemap["int8"] = ::Int8;
  _typemap["int16"] = ::Int16;
  _typemap["int32"] = ::Int32;
  _typemap["float"] = ::Float;
  _typemap["double"] = ::Double;
}

IOperand	*Chipset::getOperand(std::string str)
{
  eOperandType typeOperand;
  std::string value;

  str = str.substr(str.find(" ") + 1, str.size() - str.find(" ") + 1);
  while (str.find(" ") != std::string::npos)
    str.erase(str.find(" "), 1);
  try {
      typeOperand = _typemap.at(str.substr(str.find(" ") + 1, str.find("(") - (str.find(" ") + 1)));
    }
  catch (std::out_of_range&  e) {
      throw nFault("Error type '" + str.substr(str.find(" ") + 1, str.find("(") - (str.find(" ") + 1)) + "' doesn't exist\n");
    }
  value = str.substr(str.find("(") + 1, str.find(")") - 1 - str.find("("));
  return (_currentCpu.createOperand(typeOperand, value));
}

int	Chipset::parse(std::string str)
{
  void (Cpu::*ptr)(void);
  void (Cpu::*ptr2)(void) const;

  if (str.substr(0, str.find(" ")) == "push")
    _currentCpu.push(getOperand(str));
  else if (str.substr(0, str.find(" ")) == "assert")
    _currentCpu.assert(getOperand(str));
  else if (str.substr(0, str.find(" ")) == "jmp")
    return _currentCpu.jmp(getOperand(str));
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
  return (1);
}
