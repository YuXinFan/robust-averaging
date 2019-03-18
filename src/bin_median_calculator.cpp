#include "bin_median_calculator.hpp"

#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>


BinMedianCalculator::BinMedianCalculator() {}
BinMedianCalculator::~BinMedianCalculator() {}

float
BinMedianCalculator::median( std::vector<float> &set ) {
  int k = 10; 
  auto n = set.size();
  std::cout << "size = " << set.size() << std::endl;
  // compute mean of set 
  float sum = std::accumulate( set.begin(), set.end(), 0.f);
  float mean = sum / n;

  // compute variance and mu of set 
  float temp_accumulate = 0.f;
  for ( auto num : set ) {
    temp_accumulate += ( num - mean ) * ( num - mean);
  }
  float variance = temp_accumulate / n;
  float sigma = sqrt(variance);

  float left_band = mean - sigma;
  float right_band = mean + sigma;
  
  if ( sigma == 0) {
    return mean;
  }
 

  int smaller_than_left_band = 0 , greater_than_right_band = 0;

  auto bin_region = std::vector<float>();
  float factor = k / (2 * sigma);
  float step = ( 2 * sigma ) / k;
  auto bins_count = std::vector<int>( k , 0);
  int bin; // whick bin we are operating
  for ( auto num : set ) {
    if ( num < left_band ) {
      smaller_than_left_band++;
    } else if ( num > right_band ) {
      greater_than_right_band++;
    } else {  
      bin = ( int ) ( ( num - left_band ) * factor );
      bins_count[bin]++;
      bin_region.push_back( num );
    }
  }


  if ( n % 2 == 0 ) {

    auto i1 = ( n + 1 ) / 2 , i2 = ( n + 2 ) / 2;
    int bin_i1 = smaller_than_left_band;
    for ( auto i = 0; i <= k; i++ ) {
      bin_i1 += bins_count[i];
      if ( bin_i1 >= i1) {
        i1 = i1 - ( bin_i1 - bins_count[i] );
        bin_i1 = i;
        break;
        }
    }
    int bin_i2 = smaller_than_left_band;
    for ( auto i = 0; i <= k; i++ ) {
      bin_i2 += bins_count[i];
        if ( bin_i2 >= i2) {
          i2 = i2 - ( bin_i2 - bins_count[i] );
          bin_i2 = i;
          break;
       }
     }     
    
    std::cout << bin_i1 << ":"<< bin_i2 <<std::endl;
    
  }
  return 0.f;
  // decide median position
  if ( n & 1 ) {   // when size is odd
    auto position = ( n + 1 ) / 2;
    int median_bin = smaller_than_left_band;
    for ( auto i = 0; i <= k; i++) {
      median_bin += bins_count[i];
      if (median_bin >= position) {
        position = position - (median_bin - bins_count[i]);
        median_bin = i;
        break;
      }
    }
    
    float median_left_band = left_band + ( median_bin )* step ;
    float median_right_band = median_left_band + step;
  

    //test 
    std::cout << "size = " << set.size() << ",["<<left_band <<","<<right_band << "]"<<std::endl;
    printVector(set); 
    std::cout << "smaller numer = " << smaller_than_left_band << std::endl;
    std::cout << "bin id = " << median_bin <<std::endl;
    std::cout << "step = " << step << std::endl;
    std::cout<< "median_left_band = " << median_left_band << ", median_right_band = " << median_right_band<< std::endl; 
    
    std::cout << "vector :";
    for (auto i : bins_count) {
      std::cout << i << " ";
    }
    std::cout << std::endl;

    //end
    return 2.f ;
  }
  if ( n & 0) {
    return 2.f ;
  }
  


  if ( bin_region.size() <= 1 ) {
    return bin_region[0];
  }else if ( bin_region.size() < 10) {
    auto sorted_subset(bin_region);
    std::sort( sorted_subset.begin(), sorted_subset.end() );
    return 2.f;
  }else {
    return 2.f; // not right?
  }
}

void BinMedianCalculator::printVector( std::vector<float> &set ) {
  std::cout << "vector :";
  for (auto i : set ) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}