#ifndef TrackTokens_h
#define TrackTokens_h

#include "DataFormats/L1TrackTrigger/interface/Stub.h"

#include "EventFilter/L1TRawToDigi/interface/PackerTokens.h"

namespace l1t {
   namespace phase2 {
      class TrackTokens : public PackerTokens {
         public:
            TrackTokens(const edm::ParameterSet&, edm::ConsumesCollector&);

            inline const edm::EDGetTokenT<StubBxCollection>& getStubToken() const { return stubToken_;};

         private:
            edm::EDGetTokenT<StubBxCollection> stubToken_;
      };
   }
}

#endif
