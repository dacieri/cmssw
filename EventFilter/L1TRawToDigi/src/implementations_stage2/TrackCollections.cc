#include "FWCore/Framework/interface/Event.h"

#include "TrackCollections.h"

namespace l1t {
   namespace stage2 {
      TrackCollections::~TrackCollections()
      {
         event_.put(stubs_);
         event_.put(outstubs_);
        }
   }
}
