#include "PseudoRandom.h"
#include <sstream>
#include <iomanip>
#include <vector>
#include <unordered_map>

/*
* PreCondition: N/A
* PostCondition: Initializes with default values (seed=1, multiplier=40, increment=3641, modulus=729)
*/
PseudoRandom::PseudoRandom()
    : m_seed(1), m_multiplier(40), m_increment(3641), m_modulus(729), m_current(1)
{
}

/*
* PreCondition: All parameters must be integers, modulus cannot be 0
* PostCondition: Initializes with specified values
*/
PseudoRandom::PseudoRandom(int64_t seed, int64_t multiplier, int64_t increment, int64_t modulus)
    : m_seed(seed), m_multiplier(multiplier), m_increment(increment), m_modulus(modulus), m_current(seed)
{
    if (modulus == 0)
        throw E_InvalidModulus(modulus);
}

/*
* PreCondition: N/A
* PostCondition: Resets all values to defaults
*/
void PseudoRandom::Clear()
{
    m_seed = 1;
    m_multiplier = 40;
    m_increment = 3641;
    m_modulus = 729;
    m_current = 1;
}

int64_t PseudoRandom::getSeed() const { return m_seed; }
int64_t PseudoRandom::getMultiplier() const { return m_multiplier; }
int64_t PseudoRandom::getModulus() const { return m_modulus; }
int64_t PseudoRandom::getIncrement() const { return m_increment; }

void PseudoRandom::setSeed(int64_t newSeed)
{
    m_seed = newSeed;
    m_current = newSeed;
}

void PseudoRandom::setMultiplier(int64_t newMultiplier)
{
    m_multiplier = newMultiplier;
}

void PseudoRandom::setModulus(int64_t newModulus)
{
    if (newModulus == 0)
        throw E_InvalidModulus(newModulus);
    m_modulus = newModulus;
}

void PseudoRandom::setIncrement(int64_t newIncrement)
{
    m_increment = newIncrement;
}

/*
* PreCondition: N/A
* PostCondition: Returns the next pseudorandom number using linear congruential method
* @return Next pseudorandom number
*/
int64_t PseudoRandom::getNextNumber()
{
    // Use safe calculation to prevent overflow
    int64_t product = (m_multiplier * m_current) % m_modulus;
    int64_t sum = (product + m_increment) % m_modulus;

    // Handle negative results
    if (sum < 0)
        sum += m_modulus;

    m_current = sum;
    return sum;
}

/*
* PreCondition: N/A
* PostCondition: Returns the next pseudorandom number without storing it
* @return Next pseudorandom number
*/
float PseudoRandom::getIndirectNextNumber()
{
    int64_t product = (m_multiplier * m_current) % m_modulus;
    int64_t sum = (product + m_increment) % m_modulus;

    if (sum < 0)
        sum += m_modulus;

    m_current = sum;
    return (float) sum / (float) m_modulus;
}

/*
* PreCondition: N/A
* PostCondition: Generates 12 Random Numbers and returns the approximate Gaussian Distribution
* @return Approximate Gaussian Distribution
*/
float PseudoRandom::getGaussianDistribution()
{
    size_t count = 12;
    float  sum = 0;
    std::vector<float > randNums;
    randNums.reserve(count);

    for (size_t i = 0; i < count; i++)
    {
        float rand = this->getIndirectNextNumber();
        sum += rand;
        randNums.push_back(rand);
    }

    float median = (randNums[5] + randNums[6]) / 2.f;

    float mean = sum / (float) count;

    float standDev = 0.f;

    float sumOfSquareDifferences = 0.f;
    

    for (float  randNum : randNums)
        sumOfSquareDifferences += (randNum - mean) * (randNum - mean);

    standDev = std::sqrt(sumOfSquareDifferences / (float) count);

    return (median + (sum - 6.f) * standDev);
    
}

/*
* PreCondition: N/A
* PostCondition: Runs test that generates 1,000,000 Random Numbers and displays Frequency. Also returns Approximate Gaussian Distribution
* @return Test Results As String formatted as Table
*/
std::string PseudoRandom::getTestResults()
{
    std::unordered_map<size_t, size_t> occurences;
    std::stringstream ss;
    

    for (size_t i = 0; i < 1E6; i++)
    {
        float randNum = this->getIndirectNextNumber();
        for (int16_t j = 1; j <= 10; j++)
        {
            if (randNum < (float)j / 10.f)
            {
                occurences[j]++;
                break;
            }
        }
    }

    ss << "Multiplier : " << m_multiplier << " Increment : " << m_increment << " Modulus : " << m_modulus;

    ss << "\n\n\t" << std::left << std::setw(15) << "Range" << std::right << std::setw(22) << "Number Of Occurrences";


    for (size_t i = 1; i <= 10; i++)
    {
        std::stringstream ss1;
        ss1 << "(" << std::setprecision(2) << (float)i / 10.f - 0.1f << " ... " << std::setprecision(2) << (float)i / 10.f << ")";
        ss << "\n\t" << std::left << std::setw(15) << ss1.str() << std::right << std::setw(22) << occurences[i];
    }

    ss << "\n\t" << "With 12 uniformly distributed rand number in the range[0...1.0),";
    ss << "\n\t" << "the approximate Gaussian distribution is " << this->getGaussianDistribution();

    return ss.str();
}

// Exception implementations
inline std::string PseudoRandom::E_InvalidModulus::GetExceptionName() const
{
    return "Invalid modulus";
}

inline std::string PseudoRandom::E_InvalidModulus::GetExceptionMessage() const
{
    return "Modulus cannot be zero (received: " + std::to_string(modulus) + ")";
}