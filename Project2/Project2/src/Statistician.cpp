#include "Statistician.h"
#include <sstream>

/*
* PreCondition: N/A
* PostCondition: Initializes empty statistician
*/
Statistician::Statistician()
    : m_Sum(0), m_Min(std::numeric_limits<double>::max()), m_Max(std::numeric_limits<double>::lowest())
{
}

/*
* PreCondition: N/A
* PostCondition: Clears all numbers from the sequence
*/
void Statistician::Clear()
{
    m_Sequence.clear();
    m_Sum = 0;
    m_Min = std::numeric_limits<double>::max();
    m_Max = std::numeric_limits<double>::lowest();
}

/*
* PreCondition: number is a valid double
* PostCondition: Adds number to the sequence and updates statistics
*/
void Statistician::insertNumber(double number)
{
    m_Sequence.push_back(number);
    m_Sum += number;

    if (number < m_Min) m_Min = number;
    if (number > m_Max) m_Max = number;
}

/*
* PreCondition: N/A
* PostCondition: Returns the number of elements in the sequence
* @return Length of sequence
*/
int Statistician::findLength() const
{
    return m_Sequence.size();
}

/*
* PreCondition: Sequence must not be empty
* PostCondition: Returns the first number in the sequence
* @return First number
*/
double Statistician::findFirst() const
{
    if (m_Sequence.empty())
        throw E_EmptySequence();
    return m_Sequence.front();
}

/*
* PreCondition: Sequence must not be empty
* PostCondition: Returns the last number in the sequence
* @return Last number
*/
double Statistician::findLast() const
{
    if (m_Sequence.empty())
        throw E_EmptySequence();
    return m_Sequence.back();
}

/*
* PreCondition: N/A
* PostCondition: Returns the sum of all numbers
* @return Sum of numbers
*/
double Statistician::findSum() const
{
    return m_Sum;
}

/*
* PreCondition: Sequence must not be empty
* PostCondition: Returns the mean of all numbers
* @return Mean of numbers
*/
double Statistician::findMean() const
{
    if (m_Sequence.empty())
        throw E_EmptySequence();
    return m_Sum / m_Sequence.size();
}

/*
* PreCondition: Sequence must not be empty
* PostCondition: Returns the smallest number
* @return Minimum value
*/
double Statistician::findMinimum() const
{
    if (m_Sequence.empty())
        throw E_EmptySequence();
    return m_Min;
}

/*
* PreCondition: Sequence must not be empty
* PostCondition: Returns the largest number
* @return Maximum value
*/
double Statistician::findMaximum() const
{
    if (m_Sequence.empty())
        throw E_EmptySequence();
    return m_Max;
}

/*
* PreCondition: N/A
* PostCondition: Returns a string representation of the sequence
* @return String containing all numbers
*/
std::string Statistician::displaySequence() const
{
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < m_Sequence.size(); i++)
    {
        ss << m_Sequence[i];
        if (i < m_Sequence.size() - 1)
            ss << ", ";
    }
    ss << "]";
    return ss.str();
}

// Exception implementations
inline std::string Statistician::E_EmptySequence::GetExceptionName() const
{
    return "Empty sequence";
}

inline std::string Statistician::E_EmptySequence::GetExceptionMessage() const
{
    return "Cannot perform operation on empty sequence";
}