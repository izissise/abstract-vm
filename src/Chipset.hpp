#ifndef CHIPSET_H
#define CHIPSET_H

#include <map>
#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include "Fault.hpp"
#include "cpu.hpp"
#include "EOperator.hpp"

class Chipset
{
public:
  Chipset();
  ~Chipset();
public:
  void		parser();
  void		parser(const std::string &filename);
private:
  std::map<std::string, void (Cpu::*)(void)>		_operators;
  std::map<std::string, void (Cpu::*)(void) const>	_operatorsConst;
  std::map<std::string, eOperandType>			_typemap;
  Cpu							&_currentCpu;
  std::vector<std::string>				content;
private:
  void		parsing(std::string &line);
  void		setOperators();
  void		setOperand();
  IOperand	*getOperand(std::string str);
  void		parse(std::string str);
};

#endif // CHIPSET_H
