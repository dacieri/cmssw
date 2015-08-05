///
/// \class l1t::TrackTriggerParams
///
/// Description: Placeholder for track trigger parameters
///
/// Implementation:
///
///
/// \author: Tom james

#ifndef TrackTriggerParams_h
#define TrackTriggerParams_h

#include <memory>
#include <iostream>
#include <vector>
#include <cmath>

#include "CondFormats/Serialization/interface/Serializable.h"
#include "CondFormats/L1TObjects/interface/LUT.h"

namespace l1t {


  class TrackTriggerParams {

  public:

std::vector<int> MAxisMax;
std::vector<int> MAxisMin;
std::vector<int> MAxisMav;

std::vector<unsigned int> CAxisMax;
std::vector<unsigned int> CAxisMin;
std::vector<unsigned int> CAxisMav;

int T;

   
  private:
    


    COND_SERIALIZABLE;
  };

}// namespace
#endif

