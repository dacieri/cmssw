///
/// Description: Firmware headers
///
/// Implementation:
///    Concrete firmware implementations
///	Tom James 
///

#ifndef Phase2MainProcessorFirmware_H
#define Phase2MainProcessorFirmware_H

#include "L1Trigger/L1TrackTrigger/interface/Phase2MainProcessor.h"
#include "L1Trigger/L1TrackTrigger/interface/Phase2TrackTriggerFirmware.h"
#include "L1Trigger/L1TrackTrigger/interface/Phase2TrackTrigger.h"

#include "CondFormats/L1TObjects/interface/TrackTriggerParams.h"


namespace l1t {

  // first iteration
  class Phase2MainProcessorFirmware : public Phase2MainProcessor {
  public:
    Phase2MainProcessorFirmware(unsigned fwv, TrackTriggerParams* params);

    virtual ~Phase2MainProcessorFirmware();

    virtual void processEvent(
    const std::vector<l1t::Stub> & stubs,
    std::vector<l1t::Stub> & outstubs
);

    void print(std::ostream&) const;

    friend std::ostream& operator<<(std::ostream& o, 
    const Phase2MainProcessorFirmware & p) { p.print(o); return o; }

  private:
    
    TrackTriggerParams* m_params;

    Phase2TrackTrigger* m_trackTrigger;
    
  };
  
}

#endif
