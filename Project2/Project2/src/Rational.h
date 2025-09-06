#pragma once
#include "ExceptionInterface.h"
#include <iostream>
#include <string>

class Rational
{
public:

	void Clear();

public:
	class E_InvalidDemoninator : public ExceptionInterface
	{
	private:
		int32_t numerator;
		int32_t denominator;

	public:
		E_InvalidDemoninator(int32_t n, int32_t d)
		{
			numerator = n;
			denominator = d;
		}

		std::string getNumber() const
		{
			return std::to_string(numerator) + "/" + std::to_string(denominator);
		}
	};

	Rational();
	Rational(int32_t newNumerator, int32_t newDenominator);

	void setNumerator(int32_t newNumerator);
	void setDenominator(int32_t newDenominator);
	int32_t getNumerator() const;
	int32_t getDenominator() const;
	std::string to_string() const;

	// overloaded operators
	Rational operator *(const Rational &right);
	Rational operator /(const Rational &right);
	Rational operator +(const Rational &left);
	Rational operator -(const Rational &left);
	bool operator ==(const Rational &right);
	bool operator <(const Rational &right);

private:
	int32_t numerator;
	int32_t denominator;

	int32_t gcd(int32_t x, int32_t y) const;
	void simplify();

};

