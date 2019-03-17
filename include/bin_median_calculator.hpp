#ifndef CS133_BINMEDIANCALCULATOR_HPP_
#define CS133_BINMEDIANCALCULATOR_HPP_

#include "median_calculator_base.hpp"

class BinMedianCalculator: public MedianCalculatorBase{
  public: 
    BinMedianCalculator();
    virtual ~BinMedianCalculator();

    virtual float median( std::vector<float> &set );

    virtual void printVector( std::vector<float> &set );
};



#endif