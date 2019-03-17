#include <algorithm>
#include "quick_select_median_calculator.hpp"

#include <iostream>

QuickSelectMedianCalculator::QuickSelectMedianCalculator() {}
QuickSelectMedianCalculator::~QuickSelectMedianCalculator() {}

float 
QuickSelectMedianCalculator::median( std::vector<float> &set ) {
  
  auto n = set.size();
  auto i1 = (n + 1) / 2, i2 =  (n + 2)/ 2;
  auto v1 = quickSelect( set, i1 );
  auto v2 = quickSelect( set, i2 );
  
  return  ( v1 + v2 ) / 2.f;
}

float
QuickSelectMedianCalculator::quickSelect( std::vector<float> &set, int k ) {
  auto n = set.size();
  auto less_than_pivot = std::vector<float>();  //less than pivot
  auto more_than_pivot = std::vector<float>();  //greater than pivot
  auto pivots = std::vector<float>(); //equal to pivot
  auto pivot = set[set.size() / 2];

  for ( int i = 0; i < n; i++ ) {
    float curr_number = set[i];
    if ( curr_number < pivot ) {
      less_than_pivot.push_back( curr_number );
    }else if ( curr_number > pivot ) {
      more_than_pivot.push_back( curr_number );
    }else {
      pivots.push_back( curr_number );
    }
  }
  
  // printVector(less_than_pivot);
  // printVector(pivots);
  // printVector(more_than_pivot);
  // std::cout<<std::endl;

  if ( less_than_pivot.size() >= k ) {
      return quickSelect( less_than_pivot, k );
  }else if ( less_than_pivot.size() + pivots.size() >= k)
  {
    return pivot;
  }else {
    return quickSelect( more_than_pivot, k-less_than_pivot.size()-pivots.size() );
  }
  return 404.f;
}

void 
QuickSelectMedianCalculator::printVector( std::vector<float> &set) {
  std::cout << "vector :";
  for (auto i = set.begin(); i !=set.end(); i++ ) {
    std::cout << *i << " ";
  }
  std::cout << std::endl;
}