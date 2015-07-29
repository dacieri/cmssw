#ifndef DataFormats_L1TrackTrigger_classes_h
#define DataFormats_L1TrackTrigger_classes_h

#include "DataFormats/L1TrackTrigger/interface/Stub.h"
#include "DataFormats/Common/interface/Wrapper.h"
#include "DataFormats/Common/interface/RefVector.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "Rtypes.h"
#include "Math/Cartesian3D.h"
#include "Math/Polar3D.h"
#include "Math/CylindricalEta3D.h"
#include "Math/PxPyPzE4D.h"
#include <boost/cstdint.hpp>
#include "DataFormats/L1GlobalCaloTrigger/interface/L1GctCand.h"


namespace DataFormats_L1Trigger {
  struct dictionary {

    l1t::StubBxCollection    stubBxColl;
    edm::Wrapper<l1t::StubBxCollection>    w_stubBxColl;

  };
}

#endif
