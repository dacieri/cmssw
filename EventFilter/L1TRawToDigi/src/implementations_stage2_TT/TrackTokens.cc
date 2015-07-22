#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "TrackTokens.h"

namespace l1t {
   namespace phase2 {
      TrackTokens::TrackTokens(const edm::ParameterSet& cfg, edm::ConsumesCollector& cc) : PackerTokens(cfg, cc)
      {
         auto tag = cfg.getParameter<edm::InputTag>("InputLabel");

         stubToken_ = cc.consumes<StubBxCollection>(tag);
      }
   }
}
