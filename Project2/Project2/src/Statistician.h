#pragma once
#include <vector>
#include <limits>
#include <string>
#include "ExceptionInterface.h"

class Statistician
{
public:
    class E_EmptySequence : public ExceptionInterface
    {
    private:
        std::string GetExceptionName() const override;
        std::string GetExceptionMessage() const override;
    };

    Statistician();
    void Clear();

    // Operations
    void insertNumber(double number);
    int findLength() const;
    double findFirst() const;
    double findLast() const;
    double findSum() const;
    double findMean() const;
    double findMinimum() const;
    double findMaximum() const;
    std::string displaySequence() const;

    Statistician operator +(const Statistician &left) const;

private:
    std::vector<double> m_Sequence;
    double m_Sum;
    double m_Min;
    double m_Max;
};