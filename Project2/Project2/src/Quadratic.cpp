#include "Quadratic.h"
#include <sstream>



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
        return { (- b - this->GetDiscriminant()) / 2 / a, (- b + this->GetDiscriminant()) / 2 / a};
    else
        return { Roots::complex, Roots::complex };
}
