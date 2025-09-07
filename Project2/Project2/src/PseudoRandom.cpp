#include "PseudoRandom.h"
#include <sstream>

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
int64_t PseudoRandom::getIndirectNextNumber()
{
    int64_t product = (m_multiplier * m_current) % m_modulus;
    int64_t sum = (product + m_increment) % m_modulus;

    if (sum < 0)
        sum += m_modulus;

    return sum;
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