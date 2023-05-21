#pragma once
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include "TT.h"
#include "FC.h"
#include "BC.h"
#include "DPLL.h"
#include "Resolution.h"

class IECreator
{
public:

	virtual ~IECreator() {};
	IE* GetIEType(std::string IEType, std::string aKB, std::string aQuery);
};