#include "Rational.h"

void Rational::Clear()
{

}

Rational::Rational()
{
	numerator = 0;
	denominator = 1;
	simplify();
}

Rational::Rational(int32_t newNumerator, int32_t newDenominator)
{
	numerator = newNumerator;
	denominator = newDenominator;
	simplify();
}

int32_t Rational::gcd(int32_t x, int32_t y) const
{
	if (x % y == 0)
		return y;
	else
		return gcd(y, x % y);
}

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

void Rational::setNumerator(int32_t newNumerator)
{
	numerator = newNumerator;
	simplify();
}

int Rational::getNumerator() const
{
	return numerator;
}

void Rational::setDenominator(int32_t newDenominator)
{
	denominator = newDenominator;
	simplify();
}

int Rational::getDenominator() const
{
	return denominator;
}

Rational Rational::operator *(const Rational &right)
{
	Rational temp;

	// multiply the numerator and denominator of each object
	temp.setNumerator(this->getNumerator() * right.getNumerator());
	temp.setDenominator(this->getDenominator() * right.getDenominator());

	return temp;
}


Rational Rational::operator /(const Rational &right)
{
	Rational temp;

	// multiply by the reciprocal
	temp.setNumerator(this->getNumerator() * right.getDenominator());
	temp.setDenominator(this->getDenominator() * right.getNumerator());

	return temp;
}

Rational Rational::operator +(const Rational &right)
{
	Rational temp;

	// multiply the numerator by the denominator, then add the numerators
	temp.setNumerator((right.getDenominator() * this->getNumerator()) + (this->getDenominator() * right.getNumerator()));
	temp.setDenominator(this->getDenominator() * right.getDenominator());

	return temp;
}

Rational Rational::operator -(const Rational &right)
{
	Rational temp;

	// multiply the numerator by the denominator, then subtract the numerators
	temp.setNumerator((right.getDenominator() * this->getNumerator()) - (this->getDenominator() * right.getNumerator()));
	temp.setDenominator(this->getDenominator() * right.getDenominator());

	return temp;
}

bool Rational::operator ==(const Rational &right)
{
	return ((this->getNumerator() * right.getDenominator()) == (this->getDenominator() * right.getNumerator()));
}

bool Rational::operator <(const Rational &right)
{
	return ((this->getNumerator() * right.getDenominator()) < (this->getDenominator() * right.getNumerator()));
}

std::ostream &operator <<(std::ostream &out, const Rational &obj)
{
	out << obj.getNumerator() << "/" << obj.getDenominator();
	return out;
}