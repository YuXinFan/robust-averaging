#include "randomized_median_calculator.hpp"

#include <algorithm>
#include <iostream>
#include <random>

#include <cstdlib>
#include <ctime>
#include <cmath>
RandomizedMedianCalculator::RandomizedMedianCalculator() {}

RandomizedMedianCalculator::~RandomizedMedianCalculator() {}

float
RandomizedMedianCalculator::median( std::vector<float> &set ) {
  //random_shuffle( set.begin(), set.end());
  
  int size_set_S = set.size();
  float var_n = pow( size_set_S, 3.f/4.f );
  int size = ceil( var_n );

  std::random_device random;
  std::default_random_engine random_engine(random());
  std::uniform_int_distribution<int> uniform_random(0, size_set_S-1);  
  // #ifndef RandomizedMedianCalculator_Set_Random_Seed
  // #define RandomizedMedianCalculator_Set_Random_Seed
  // srand( (unsigned) time (0));
  // #endif
  int random_num;
  auto subset_R = std::vector<float>();
  for ( int i = 0; i < size; i++ ) {
    random_num = uniform_random(random);
    subset_R.push_back( set[random_num] );
  }
  
  auto sorted_subset_R( subset_R );
  std::sort( sorted_subset_R.begin(), sorted_subset_R.end() );
  auto index_d = floor( ( 1.f/2.f ) * var_n - sqrt( size_set_S ) ) -1.f ;
  auto index_u = ceil( ( 1.f/2.f ) * var_n + sqrt( size_set_S ) ) -1.f ;
  if (index_d < 0) index_d = 0;
  if (index_u >= size) index_u = size -1 ;
  auto element_d = sorted_subset_R[index_d];
  auto element_u = sorted_subset_R[index_u];

  std::cout << " var_n="<<var_n << std::endl;
  printVector(set);
  printVector(sorted_subset_R);
  std::cout << " d ="<<index_d<<", u="<<index_u<<std::endl;
  std::cout << " ****** "<<std::endl;

  auto set_C = std::vector<float>();
  int Ld = 0;
  int Lu = 0;
  for ( auto num : set ) {
    if ( num < element_d ) {
      Ld++;
    }else if ( num >= element_d && num <= element_u) {
      set_C.push_back( num );
    }else {
      Lu++;
    }
  }
  if ( Ld >= ( size_set_S / 2 ) 
    || Lu >= ( size_set_S / 2 ) ) {
    return median( set );
  }else if ( set_C.size() > ( 4 * var_n ) ) {
    return median( set );
  }else{
    int i1 = floor( (size_set_S + 1) / 2.f ) - Ld;
    int i2 = floor( (size_set_S + 2) / 2.f) - Ld;

    std::sort( set_C.begin(), set_C.end() );
    return ( set_C[i1-1] + set_C[i2-1] ) / 2.f;
  } 
}

void RandomizedMedianCalculator::printVector( std::vector<float> &set) {
  std::cout << "vector :";
  for (auto i = set.begin(); i !=set.end(); i++ ) {
    std::cout << *i << " ";
  }
  std::cout << std::endl;
}