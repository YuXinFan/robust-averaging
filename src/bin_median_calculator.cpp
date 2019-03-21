#include "bin_median_calculator.hpp"

#include <iostream>
#include <numeric>
#include <algorithm>

#include <cmath>


BinMedianCalculator::BinMedianCalculator() {}
BinMedianCalculator::~BinMedianCalculator() {}

float
BinMedianCalculator::median( std::vector<float> &set ) {
  auto n = set.size();
  int i1 = (n + 1)/2;
  int i2 = (n+2)/2;
  int k = 100; 

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
 

  int smaller_than_left_band = 0;
  auto subset_bins = std::vector<float>();
  for ( auto num : set ) {
    if ( num < left_band ) {
      smaller_than_left_band++;
    } else if ( num <= right_band ) {
      subset_bins.push_back( num );
    }
  }
  float val_i1 = findNthNumberWithBand(subset_bins, i1-smaller_than_left_band, left_band, right_band);
  float val_i2 = findNthNumberWithBand(subset_bins, i2-smaller_than_left_band, left_band, right_band);
  return ( val_i1 + val_i2 ) / 2.f;
}

float BinMedianCalculator::findNthNumberWithBand( std::vector<float> &set , int k, float left_band, float right_band)
{
  int bin_number; int K = 100;
  float bin_length = ( right_band - left_band ) / K; 
  auto bin_number_counts = std::vector<int>(K, 0);
  for ( auto num : set) {
    bin_number = (int)( (num - left_band) / bin_length);
    bin_number_counts[bin_number]++;
  }
 
  std::cout << k << std::endl;
  int count = 0; int bin_of_kth;
  for ( int i = 0; i < K; i++) {
    count += bin_number_counts[i];
    if (count >= k) {
      k = k-(count-bin_number_counts[i]);
      bin_of_kth = i;
      break;
    }
  }
 
  int left_number_count = 0;
  float tight_left_band = left_band + bin_of_kth * bin_length;
  float tight_right_band = tight_left_band + bin_length;
  auto bin_set = std::vector<float>();
  for ( auto num : set) {
    if ( num < tight_left_band) {
      left_number_count++;
    }else if ( num <= tight_right_band ) {
      bin_set.push_back(num);
    }
  }
  //printVector(set);
  // printVector(bin_set);
  // std::cout << "k="<<k<<", bin_len="<<bin_length<<std::endl;
  // std::cout << "band=["<<left_band <<","<<right_band<<"]"<<std::endl;
  // std::cout << "tight band=["<<tight_left_band <<","<<tight_right_band<<"]"<<std::endl;
  if (bin_set.size() < 10) {
    std::sort(bin_set.begin(), bin_set.end());
    //return 0.f;
    return bin_set[k-1];
  } else {
    return findNthNumberWithBand(bin_set, k, tight_left_band, tight_right_band);
  }

  return 0.f;
}

void BinMedianCalculator::printVector( std::vector<float> &set ) {
  std::cout << "vector :";
  for (auto i : set ) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

