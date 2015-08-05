
///
/// \class l1t::Phase2FirmwareFactory
///
/// \author: Tom James
///


#ifndef Phase2FirmwareFactory_h
#define Phase2FirmwareFactory_h

#include <boost/shared_ptr.hpp>

#include "L1Trigger/L1TrackTrigger/interface/Phase2MainProcessor.h"

#include "CondFormats/L1TObjects/interface/TrackTriggerParams.h"

//#include "FWCore/Framework/interface/Event.h"


namespace l1t {

  class Phase2FirmwareFactory {
  public:
    typedef boost::shared_ptr<Phase2MainProcessor> ReturnType;

    ReturnType create(unsigned fwv, TrackTriggerParams* params);

  };

} // namespace

#endif










