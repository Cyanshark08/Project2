#pragma once
#include <cstdint>
#include "ExceptionInterface.h"

class PseudoRandom
{
public:
    class E_InvalidModulus : public ExceptionInterface
    {
    private:
        int64_t modulus;

    private:
        std::string GetExceptionName() const override;
        std::string GetExceptionMessage() const override;

    public:
        E_InvalidModulus(int64_t mod) : modulus(mod) {}
    };

    PseudoRandom();
    PseudoRandom(int64_t seed, int64_t multiplier, int64_t increment, int64_t modulus);

    void Clear();

    // Accessors
    int64_t getSeed() const;
    int64_t getMultiplier() const;
    int64_t getModulus() const;
    int64_t getIncrement() const;

    // Mutators
    void setSeed(int64_t newSeed);
    void setMultiplier(int64_t newMultiplier);
    void setModulus(int64_t newModulus);
    void setIncrement(int64_t newIncrement);

    // Operations
    int64_t getNextNumber();
    int64_t getIndirectNextNumber();

private:
    int64_t m_seed;
    int64_t m_multiplier;
    int64_t m_increment;
    int64_t m_modulus;
    int64_t m_current;
};