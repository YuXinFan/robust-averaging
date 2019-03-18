#include "randomized_median_calculator.hpp"

#include <algorithm>

#include <cstdlib>
#include <ctime>
#include <cmath>
RandomizedMedianCalculator::RandomizedMedianCalculator() {}

RandomizedMedianCalculator::~RandomizedMedianCalculator() {}

float
RandomizedMedianCalculator::median( std::vector<float> &set ) {
  //random_shuffle( set.begin(), set.end());
  
  int vector_size = set.size();
  float var_n = pow( vector_size, 3.f/4.f );
  int size = ceil( var_n );

  srand( (unsigned) time (0));
  int random_num;
  auto subset_R = std::vector<float>();
  for ( int i = 0; i < size; i++ ) {
    random_num = rand()%vector_size;
    subset_R.push_back( set[random_num] );
  }
  auto sorted_subset_R( subset_R );
  std::sort( sorted_subset_R.begin(), sorted_subset_R.end() );
  auto index_d = floor( ( 1.f/2.f ) * var_n - sqrt( vector_size ) ) -1.f ;
  auto index_u = ceil( ( 1.f/2.f ) * var_n + sqrt( vector_size ) ) -1.f ;
  auto element_d = sorted_subset_R[index_d];
  auto element_u = sorted_subset_R[index_u];

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
  if ( Ld > ( vector_size / 2 ) 
    || Lu > ( vector_size / 2 ) ) {
    return median( set_C );
  }else if ( set_C.size() > ( 4 * size ) ) {
    return median( set_C );
  }else{
    int i1 = floor( vector_size / 2.f ) - Ld;
    int i2 = floor( (vector_size + 1) / 2.f) - Ld;

    std::sort( set_C.begin(), set_C.end() );
    return ( set_C[i1] + set_C[i2] ) / 2.f;
  } 
}