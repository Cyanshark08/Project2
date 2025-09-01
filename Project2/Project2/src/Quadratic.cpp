#include "Quadratic.h"
#include <sstream>

std::string Quadratic::to_string() const
{
    std::stringstream ss;
    ss << a << "x^2 + " << b << "x + " << c;
    return ss.str();
}
