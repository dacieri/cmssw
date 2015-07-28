#include "FWCore/Framework/interface/Event.h"

#include "TrackCollections.h"

namespace l1t {
   namespace phase2 {
      TrackCollections::~TrackCollections()
      {
         event_.put(stubs_,"Input");
         event_.put(outstubs_,"Output");
        }
   }
}
