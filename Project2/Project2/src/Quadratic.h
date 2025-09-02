#pragma once
#include <string>
#include <limits>

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

	float operator()(float p_Arg) const;
	float& operator[](size_t p_CoeffNum);

	size_t GetNumOfRoots() const;
	Roots GetRoots() const;

	std::string to_string() const;

	void Clear();
	
private:
	float GetDiscriminant() const;

	float a, b, c;
};

