#include "ExceptionInterface.h"

std::string ExceptionInterface::Message() const
{
	std::stringstream ss;
	ss << "\n\tEXCEPTION ERROR: " << GetExceptionMessage() << "\n\n\t";
	return ss.str();
}
