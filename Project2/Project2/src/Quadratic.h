#pragma once
#include <string>
#include <limits>
#include "ExceptionInterface.h"

enum class EQuadraticCoeff
{
	A = 'A',
	B = 'B',
	C = 'C'
};

struct Roots
{
	float rootOne, rootTwo;

	constexpr static const float complex = std::numeric_limits<float>::min();
};

class Quadratic
{
public:

	void SetAt(EQuadraticCoeff p_CoeffNum, float p_Arg);

	float EvaluateAt(float p_Arg) const;

	size_t GetNumOfRoots() const;
	Roots GetRoots() const;
	std::string GetRootsAsString() const;
	std::string to_string() const;

	void Clear();

	float operator()(float p_Arg) const;
	float& operator[](size_t p_CoeffNum);

public:
	class E_NoRealRoots : public ExceptionInterface
	{
		private:
			std::string GetExceptionName() const override;
			std::string GetExceptionMessage() const override;
	};
	
private:
	float GetDiscriminant() const;
	bool IsLinear() const;
	bool IsConstant() const;

	float a, b, c;
};

