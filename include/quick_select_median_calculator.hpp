#ifndef CS133_QUICKSELECTMEDIANCALCULATOR_HPP_
#define CS133_QUICKSELECTMEDIANCALCULATOR_HPP_

#include "median_calculator_base.hpp"


class QuickSelectMedianCalculator: public MedianCalculatorBase {
    public:
    QuickSelectMedianCalculator();
    virtual ~QuickSelectMedianCalculator();

    virtual float median(std::vector<float> & set);
    virtual float quickSelect(std::vector<float> &set, int k);
    /*
    **help function
    */
    virtual void printVector(std::vector<float> &set);

};

#endif