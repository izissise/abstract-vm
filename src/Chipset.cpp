#include "Chipset.hpp"

Chipset::Chipset(const std::string &filename)
  : _currentCpu(Cpu::Instance())
{
  std::string content;
  std::ifstream ifs(filename.c_str());

  setOperand();
  setOperators();
  if (!ifs.is_open())
	nFault("Error openning '" + filename + "'\n");
  while(std::getline(ifs, content))
    {
      if (content.find_first_not_of(" ") + 1 > content.size() &&
	  content.substr(content.find_first_not_of(" ") + 1, 1) != ";")
	parse(content);
    }
	//ctor
}

Chipset::Chipset()
  : _currentCpu(Cpu::Instance())
{
  std::string content;

  setOperand();
  setOperators();
  while(std::getline(std::cin, content) && content != ";;")
    {
      if (content.find_first_not_of(" ") + 1 > content.size() &&
	  content.substr(content.find_first_not_of(" ") + 1, 1) == ";")
	parse(content);
    }
	//ctor
}

Chipset::~Chipset()
{
	//dtor
}

void	Chipset::setOperators()
{
  _operators[std::string("pop")] = &Cpu::pop;
  _operators[std::string("add")] = &Cpu::add;
  _operators[std::string("sub")] = &Cpu::sub;
  _operators[std::string("mul")] = &Cpu::mul;
  _operators[std::string("div")] = &Cpu::div;
  _operators[std::string("mod")] = &Cpu::mod;

  _operatorsConst[std::string("dump")] = &Cpu::dump;
  _operatorsConst[std::string("print")] = &Cpu::print;
  _operatorsConst[std::string("exit")] = &Cpu::exit;
}

void	Chipset::setOperand()
{
  _typemap[std::string("Int8")] = ::Int8;
  _typemap[std::string("Int16")] = ::Int16;
  _typemap[std::string("Int32")] = ::Int32;
  _typemap[std::string("Float")] = ::Float;
  _typemap[std::string("Double")] = ::Double;
}

IOperand	*Chipset::getOperand(std::string str)
{
  return (_currentCpu.createOperand(_typemap[str.substr(str.find(" ") + 1,
							str.find("(") - str.find(" ") + 1)],
				    str.substr(str.find("(")+ 1 ,
					       str.find(")"))));
}

void	Chipset::parse(std::string str)
{
  void (Cpu::*ptr)(void);
  void (Cpu::*ptr2)(void) const;

  try
    {
      ptr = _operators.at(str.substr(0, str.find(" ")));
      (_currentCpu.*ptr)();
    }
  catch(std::exception e)
    {
      try
	{
	  ptr2 = _operatorsConst.at(str.substr(0, str.find(" ")));
	  (_currentCpu.*ptr2)();
	}
      catch(std::exception e)
	{
	  if (str.substr(0, str.find(" ")) == "push")
	    _currentCpu.push(getOperand(str));
	  else if (str.substr(0, str.find(" ")) == "assert")
	    _currentCpu.assert(getOperand(str));
	  else
	    nFault("Error operator '" + str.substr(0, str.find(" ")) + "' doesn't exist\n");
	}
    }

}
