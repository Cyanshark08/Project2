#include "Quadratic.h"
#include <sstream>
#include <iomanip>

/*
* Precondition: Pass the Coefficient to be altered and the value to set it to
* Postcondition: Sets that coefficient to the value
*/
void Quadratic::SetAt(EQuadraticCoeff p_CoeffNum, float p_Arg)
{
    switch (p_CoeffNum)
    {
    case EQuadraticCoeff::A:
        a = p_Arg;
        break;
    case EQuadraticCoeff::B:
        b = p_Arg;
        break;
    case EQuadraticCoeff::C:
        c = p_Arg;
        break;
    }
}

float Quadratic::EvaluateAt(float p_Arg) const
{
    return a * p_Arg * p_Arg + b * p_Arg + c;
}

std::string Quadratic::to_string() const
{
    std::stringstream ss;
    ss << a << "x^2 + " << b << "x + " << c;
    return ss.str();
}

void Quadratic::Clear()
{
    a = 0.f, b = 0.f, c = 0.f;
}

float Quadratic::GetDiscriminant() const
{
    return b * b - 4 * a * c;
}

bool Quadratic::IsLinear() const
{
    return a == 0;
}

bool Quadratic::IsConstant() const
{
    return (a == 0 && b == 0);
}


float Quadratic::operator()(float p_Arg) const
{
    return this->EvaluateAt(p_Arg);
}

float& Quadratic::operator[](size_t p_CoeffNum)
{
    switch (p_CoeffNum)
    {
    case 1:
        return a;
        break;
    case 2:
        return b;
        break;
    case 3:
        return c;
        break;
    }
}

size_t Quadratic::GetNumOfRoots() const
{
    if (IsConstant() && c == 0)
    {
        return std::numeric_limits<size_t>().max();
    }
    else if (IsConstant())
        return 0;
    else if (IsLinear())
    {
        return 1;
    }

    float cachedDiscriminant = this->GetDiscriminant();

    if (cachedDiscriminant > 0)
        return 2;
    else if (cachedDiscriminant < 0)
        return 0;
    else
        return 1;

}

Roots Quadratic::GetRoots() const
{
    if (this->GetNumOfRoots() >= 0)
        return { (- b - std::sqrt(this->GetDiscriminant())) / 2 / a, (- b + std::sqrt(this->GetDiscriminant())) / 2 / a};
    else
        return { Roots::complex, Roots::complex };
}

std::string Quadratic::GetRootsAsString() const
{
    std::stringstream ss;

    if (IsConstant() && c == 0)
    {
        ss << "All x are Real Roots";
        return ss.str();
    }
    else if (IsConstant())
        throw E_NoRealRoots();
    else if (IsLinear())
    {
        ss << "x = " << std::fixed << -c / b;
        return ss.str();
    }
    
    Roots roots = this->GetRoots();

    switch (GetNumOfRoots())
    {
    case 1:
        ss << "x = " << std::fixed << roots.rootOne;
        break;
    case 2:
        ss << "x = " << std::fixed << roots.rootOne << ", x = " << std::fixed << roots.rootTwo;
        break;
    default:
        throw E_NoRealRoots();
    }
    
    return ss.str();
}

std::string Quadratic::E_NoRealRoots::GetExceptionName() const
{
    return "No Real Roots";
}

std::string Quadratic::E_NoRealRoots::GetExceptionMessage() const
{
    return "No Real Root x Exists";
}
