///
/// \class l1t::Phase2FirmwareFactory
///
///
/// \author:Thomas James
///

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "L1Trigger/L1TrackTrigger/interface/Phase2MainProcessorFirmware.h"
#include "L1Trigger/L1TrackTrigger/interface/Phase2FirmwareFactory.h"

#include "CondFormats/L1TObjects/interface/TrackTriggerParams.h"

using namespace std;
using namespace edm;

l1t::Phase2FirmwareFactory::ReturnType
l1t::Phase2FirmwareFactory::create(unsigned fwv, TrackTriggerParams* params) {

  ReturnType p;
  unsigned v = fwv;

  switch (v){
  case 1:
    p = ReturnType(new Phase2MainProcessorFirmware(fwv, params));
      break;
  default:
    // Invalid Firmware, log an error:
    LogError("l1t|TTPhase2") << "Invalid firmware version requested: " << v << "\n";
    break;
  }

  return p;

}







