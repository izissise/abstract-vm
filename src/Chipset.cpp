#include  <cstdlib>
#include "Chipset.hpp"

Chipset::Chipset(const std::string &filename)
  : _currentCpu(Cpu::Instance())
{
  std::string line;
  std::vector<std::string> content;
  std::ifstream ifs(filename.c_str());
  unsigned int i = 0;
  size_t find;

  setOperand();
  setOperators();
  if (!ifs.is_open())
    throw nFault("Error openning '" + filename + "'\n");
  while(std::getline(ifs, line))
    {
      find = line.find("  ");
      while (std::string::npos != find)
        {
          line.erase(find, 1);
          find = line.find("  ");
        }
      line.erase(0, (line.find_first_not_of(" ")));
      if (line.substr(line.find_first_not_of(" "), 1) != ";")
        {
          find = line.find(";");
          if (std::string::npos != find)
            line.erase(find, line.size() - find);
          content.push_back(line);
          i++;
        }
    }
  i = 0;
  while (i < content.size() && _currentCpu.getExit() == false)
    {
      parse(content[i]);
      i++;
    }
  if (_currentCpu.getExit() == false)
    throw nFault("Error there is no 'exit'\n");
}

Chipset::Chipset()
  : _currentCpu(Cpu::Instance())
{
  std::string line;
  std::vector<std::string> content;
  unsigned int i = 0;
  size_t find;

  setOperand();
  setOperators();
  while(std::getline(std::cin, line) && line != ";;")
    {
      find = line.find("  ");
      while (std::string::npos != find)
        {
          line.erase(find, 1);
          find = line.find("  ");
        }
      line.erase(0, (line.find_first_not_of(" ")));
      if (line.substr(line.find_first_not_of(" "), 1) != ";")
        {
          find = line.find(";");
          if (std::string::npos != find)
            line.erase(find, line.size() - find);
          content.push_back(line);
          i++;
        }

    }
  i = 0;
  while (i < content.size() && _currentCpu.getExit() == false)
    {
      parse(content[i]);
      i++;
    }
  if (_currentCpu.getExit() == false)
    throw nFault("Error there is no 'exit'\n");
}

Chipset::~Chipset()
{
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
