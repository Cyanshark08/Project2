#include "Rational.h"


/*
* PreCondition: N/A
* 
* PostCondition: reset the numerator and denominator
*/
void Rational::Clear()
{
	numerator = 0;
	denominator = 1;
	simplify();
}

/*
* PreCondition: N/A
*
* PostCondition: default the numerator and denominator
*/
Rational::Rational()
{
	numerator = 0;
	denominator = 1;
	simplify();
}

/*
* PreCondition: newNumerator and newDenominator must be integers. NewDenominator cannot equal 0
*
* PostCondition: set newNumerator and newDenominator to numerator and denominator, respectively
* @param The integers to set as the numerator and denominator
*/
Rational::Rational(int32_t newNumerator, int32_t newDenominator)
{
	if (newDenominator == 0)
		throw E_InvalidDemoninator(newNumerator, newDenominator);

	numerator = newNumerator;
	denominator = newDenominator;
	simplify();
}

/*
* PreCondition: x and y are intergers. y cannot equal 0.
*
* PostCondition: return the greatest common divisor between the two integers
* @param The two integers to find the greatest common divisor
* @return An integer representing the greatest common divisor
*/
int32_t Rational::gcd(int32_t x, int32_t y) const
{
	if (x % y == 0)
		return y;
	else
		return gcd(y, x % y);
}

/*
* PreCondition: N/A
*
* PostCondition: simplify the numerator and denominator
*/
void Rational::simplify()
{
	int32_t gcd = Rational::gcd(numerator, denominator);

	// divide numerator and denominator by the gcd
	numerator /= gcd;
	denominator /= gcd;

	// move negative to top
	if (denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}
}

/*
* PreCondition: newNumerator must be an integer
*
* PostCondition: set the numerator to the new numerator
* @param The integer to set as the numerator
*/
void Rational::setNumerator(int32_t newNumerator)
{
	numerator = newNumerator;
	simplify();
}

/*
* PreCondition: N/A
*
* PostCondition: return the numerator
* @return the integer in the numerator
*/
int Rational::getNumerator() const
{
	return numerator;
}

/*
* PreCondition: newDenominator must be an integer not equal to 0
*
* PostCondition: set the denominator to the new denominator
* @param the integer to set as the denominator
*/
void Rational::setDenominator(int32_t newDenominator)
{
	if (newDenominator == 0)
		throw E_InvalidDemoninator(getNumerator(), newDenominator);

	denominator = newDenominator;
	simplify();
}

/*
* PreCondition: N/A
*
* PostCondition: return the denominator
* @return the integer in the denominator
*/
int Rational::getDenominator() const
{
	return denominator;
}

/*
* PreCondition: N/A
* 
* PostCondition: return the class in string format 'n/n'
* @return The class as a string
*/
std::string Rational::to_string() const
{
	return std::to_string(numerator) + "/" + std::to_string(denominator);
}

// overloaded operators
Rational Rational::operator *(const Rational &right) const
{
	Rational temp;

	// multiply the numerator and denominator of each object
	temp.setNumerator(this->getNumerator() * right.getNumerator());
	temp.setDenominator(this->getDenominator() * right.getDenominator());

	return temp;
}

Rational Rational::operator /(const Rational &right) const
{
	Rational temp;

	if (right.getNumerator() == 0)
		throw E_InvalidDemoninator(getNumerator(), getDenominator());

	// multiply by the reciprocal
	temp.setNumerator(this->getNumerator() * right.getDenominator());
	temp.setDenominator(this->getDenominator() * right.getNumerator());

	return temp;
}

Rational Rational::operator +(const Rational &right) const
{
	Rational temp;

	// multiply the numerator by the denominator, then add the numerators
	temp.setNumerator((this->getNumerator() * right.getDenominator()) + (this->getDenominator() * right.getNumerator()));
	temp.setDenominator(this->getDenominator() * right.getDenominator());

	return temp;
}

Rational Rational::operator -(const Rational &right) const
{
	Rational temp;

	// multiply the numerator by the denominator, then subtract the numerators
	temp.setNumerator((this->getNumerator() * right.getDenominator()) - (this->getDenominator() * right.getNumerator()));
	temp.setDenominator(this->getDenominator() * right.getDenominator());

	return temp;
}

bool Rational::operator ==(const Rational &right) const
{
	return this->getNumerator() * right.getDenominator() == this->getDenominator() * right.getNumerator();
}

bool Rational::operator <(const Rational &right) const
{
	return this->getNumerator() * right.getDenominator() < this->getDenominator() * right.getNumerator();
}

// Exceptions
inline std::string Rational::E_InvalidDemoninator::GetExceptionName() const
{
	return "Invalid denominator";
}

inline std::string Rational::E_InvalidDemoninator::GetExceptionMessage() const
{
	return "(" + getNumber() + ") is invalid.";
}

