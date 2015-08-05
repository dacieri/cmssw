///
/// \class l1t::Phase2TrackTrigger
///
/// Description: interface for MP firmware - Track trigger
///
/// \author: Tom James
///

#ifndef Phase2TrackTrigger_h
#define Phase2TrackTrigger_h

#include "DataFormats/L1TrackTrigger/interface/Cell.h"

#include <vector>

namespace l1t {
    
  class Phase2TrackTrigger { 
  public:
    virtual void processEvent(const std::vector<l1t::Stub> & stubs, 
    std::vector<l1t::Stub> outstubs) = 0;    

    virtual ~Phase2TrackTrigger(){};
  }; 
  
} 

#endif
