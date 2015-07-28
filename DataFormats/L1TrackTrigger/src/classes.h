#ifndef DataFormats_L1TrackTrigger_classes_h
#define DataFormats_L1TrackTrigger_classes_h

#include "DataFormats/L1TrackTrigger/interface/Stub.h"


namespace DataFormats_L1Trigger {
  struct dictionary {

    l1t::StubBxCollection    stubBxColl;
    edm::Wrapper<l1t::StubBxCollection>    w_stubBxColl;

  };
}

#endif
