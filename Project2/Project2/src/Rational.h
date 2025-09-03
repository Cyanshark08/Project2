#pragma once
#include "ExceptionInterface.h"
#include <iostream>

class Rational
{
public:


	void Clear();

public:
	class E_InvalidDemoninator : public ExceptionInterface
	{

	};

	/*
	* PreCondition: N/A
	* 
	* PostCondition: default the numerator and denominator
	*/
	Rational();

	/*
	* PreCondition: newNumerator and newDenominator must be integers. NewDenominator cannot equal 0
	* 
	* PostCondition: set newNumerator and newDenominator to numerator and denominator, respectively
	* @param The integers to set as the numerator and denominator
	*/
	Rational(int newNumerator, int newDenominator);

	/*
	* PreCondition: x and y are intergers. y cannot equal 0.
	*
	* PostCondition: return the greatest common divisor between the two integers
	* @param The two integers to find the greatest common divisor
	* @return An integer representing the greatest common divisor
	*/
	int32_t gcd(int32_t x, int32_t y) const;

	/*
	* PreCondition: N/A
	* 
	* PostCondition: simplify the numerator and denominator
	*/
	void simplify();

	/*
	* PreCondition: newNumerator must be an integer
	* 
	* PostCondition: set the numerator to the new numerator
	* @param The integer to set as the numerator
	*/
	void setNumerator(int32_t newNumerator);

	/*
	* PreCondition: newDenominator must be an integer not equal to 0
	* 
	* PostCondition: set the denominator to the new denominator
	* @param the integer to set as the denominator
	*/
	void setDenominator(int32_t newDenominator);

	/*
	* PreCondition: N/A
	* 
	* PostCondition: return the numerator
	* @return the integer in the numerator
	*/
	int32_t getNumerator() const;

	/*
	* PreCondition: N/A
	* 
	* PostCondition: return the denominator
	* @return the integer in the denominator
	*/
	int32_t getDenominator() const;

	// OVERLOADED OPERATORS
	Rational operator *(const Rational &right);
	Rational operator /(const Rational &right);
	Rational operator +(const Rational &left);
	Rational operator -(const Rational &left);
	bool operator ==(const Rational &right);
	bool operator <(const Rational &right);
	friend std::ostream &operator <<(std::ostream &out, const Rational &obj);


private:
	int32_t numerator;
	int32_t denominator;

};

