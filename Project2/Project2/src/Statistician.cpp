#include "Statistician.h"
#include <sstream>

/*
* PreCondition: N/A
* PostCondition: Initializes empty statistician
*/
Statistician::Statistician()
    : m_sum(0), m_min(std::numeric_limits<double>::max()), m_max(std::numeric_limits<double>::lowest())
{
}

/*
* PreCondition: N/A
* PostCondition: Clears all numbers from the sequence
*/
void Statistician::Clear()
{
    m_sequence.clear();
    m_sum = 0;
    m_min = std::numeric_limits<double>::max();
    m_max = std::numeric_limits<double>::lowest();
}

/*
* PreCondition: number is a valid double
* PostCondition: Adds number to the sequence and updates statistics
*/
void Statistician::insertNumber(double number)
{
    m_sequence.push_back(number);
    m_sum += number;

    if (number < m_min) m_min = number;
    if (number > m_max) m_max = number;
}

/*
* PreCondition: N/A
* PostCondition: Returns the number of elements in the sequence
* @return Length of sequence
*/
int Statistician::findLength() const
{
    return m_sequence.size();
}

/*
* PreCondition: Sequence must not be empty
* PostCondition: Returns the first number in the sequence
* @return First number
*/
double Statistician::findFirst() const
{
    if (m_sequence.empty())
        throw E_EmptySequence();
    return m_sequence.front();
}

/*
* PreCondition: Sequence must not be empty
* PostCondition: Returns the last number in the sequence
* @return Last number
*/
double Statistician::findLast() const
{
    if (m_sequence.empty())
        throw E_EmptySequence();
    return m_sequence.back();
}

/*
* PreCondition: N/A
* PostCondition: Returns the sum of all numbers
* @return Sum of numbers
*/
double Statistician::findSum() const
{
    return m_sum;
}

/*
* PreCondition: Sequence must not be empty
* PostCondition: Returns the mean of all numbers
* @return Mean of numbers
*/
double Statistician::findMean() const
{
    if (m_sequence.empty())
        throw E_EmptySequence();
    return m_sum / m_sequence.size();
}

/*
* PreCondition: Sequence must not be empty
* PostCondition: Returns the smallest number
* @return Minimum value
*/
double Statistician::findMinimum() const
{
    if (m_sequence.empty())
        throw E_EmptySequence();
    return m_min;
}

/*
* PreCondition: Sequence must not be empty
* PostCondition: Returns the largest number
* @return Maximum value
*/
double Statistician::findMaximum() const
{
    if (m_sequence.empty())
        throw E_EmptySequence();
    return m_max;
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
    for (size_t i = 0; i < m_sequence.size(); i++)
    {
        ss << m_sequence[i];
        if (i < m_sequence.size() - 1)
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