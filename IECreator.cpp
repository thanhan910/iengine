#include "IECreator.h"

IE* IECreator::GetIEType(std::string IEType, std::string aKB, std::string aQuery)
{
	if (IEType == "TT")
		return new TT(aKB,aQuery);
	if (IEType == "FC")
		return new FC(aKB, aQuery);
	if (IEType == "BC")
		return new BC(aKB, aQuery);
	if (IEType == "DPLL")
		return new DPLL(aKB, aQuery);
	if (IEType == "RESOLUTION")
		return new Resolution(aKB, aQuery);

	std::cerr << "<method> when in uppercase should be TT, FC, BC, DPLL, RESOLUTION\n";

}