#ifndef QUICKSELECTMEDIANCALCULATOR_HPP_
#define QUICKSELECTMEDIANCALCULATOR_HPP_

#include "median_calculator_base.hpp"


class QuickSelectMedianCalculator: public MedianCalculatorBase{
    public:
    QuickSelectMedianCalculator();
    virtual ~QuickSelectMedianCalculator();

    virtual float median(std::vector<float> & set)=0;

}

#endif