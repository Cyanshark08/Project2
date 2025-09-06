#pragma once
#include <cstdint>
#include "ExceptionInterface.h"

class PseudoRandom
{
public:
    class E_InvalidModulus : public ExceptionInterface
    {
    private:
        int32_t modulus;

    private:
        std::string GetExceptionName() const override;
        std::string GetExceptionMessage() const override;

    public:
        E_InvalidModulus(int32_t mod) : modulus(mod) {}
    };

    PseudoRandom();
    PseudoRandom(int32_t seed, int32_t multiplier, int32_t increment, int32_t modulus);

    void Clear();

    // Accessors
    int32_t getSeed() const;
    int32_t getMultiplier() const;
    int32_t getModulus() const;
    int32_t getIncrement() const;

    // Mutators
    void setSeed(int32_t newSeed);
    void setMultiplier(int32_t newMultiplier);
    void setModulus(int32_t newModulus);
    void setIncrement(int32_t newIncrement);

    // Operations
    int32_t getNextNumber();
    int32_t getIndirectNextNumber();

private:
    int32_t m_seed;
    int32_t m_multiplier;
    int32_t m_increment;
    int32_t m_modulus;
    int32_t m_current;
};