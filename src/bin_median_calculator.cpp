#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include "bin_median_calculator.hpp"

BinMedianCalculator::BinMedianCalculator() {}
BinMedianCalculator::~BinMedianCalculator() {}

float
BinMedianCalculator::median( std::vector<float> &set ) {


  // compute mean of set 
  float sum = std::accumulate( set.begin(), set.end(), 0.f);
  float mean = sum / set.size();

  // compute variance and mu of set 
  float temp_accumulate = 0.f;
  for ( auto num : set ) {
    temp_accumulate += ( num - mean ) * ( num - mean);
  }
  float variance = temp_accumulate / set.size();
  float mu = sqrt(variance);

  float left_band = mean - mu;
  float right_band = mean + mu;
  
  int smaller_than_left_band , greater_than_right_band = 0;
  auto bin_region = std::vector<float>();
  for ( auto num : set ) {
    if ( num < left_band ) {
      smaller_than_left_band++;
    } else if ( num > right_band ) {
      greater_than_right_band++;
    } else {
      bin_region.push_back( num );
    }
  }
  if ( bin_region.size() < 10) {
    auto sorted_subset(bin_region);
    std::sort( sorted_subset.begin(), sorted_subset.end() );
    return sorted_subset[0];
  }else {
    return median(bin_region); // not right?
  }
}

void BinMedianCalculator::printVector( std::vector<float> &set ) {
  std::cout << "vector :";
  for (auto i = set.begin(); i !=set.end(); i++ ) {
    std::cout << *i << " ";
  }
  std::cout << std::endl;
}