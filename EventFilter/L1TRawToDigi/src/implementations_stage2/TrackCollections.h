#ifndef TrackCollections_h
#define TrackCollections_h

#include "DataFormats/L1Trigger/interface/Stub.h"


//#include "EventFilter/L1TRawToDigi/interface/UnpackerCollections.h"
#include "L1TObjectCollections.h"

namespace l1t {
   namespace stage2 {
     class TrackCollections : public L1TObjectCollections {
         public:
            TrackCollections(edm::Event& e) :
               L1TObjectCollections(e),
               stubs_(new StubBxCollection()),
               outstubs_(new StubBxCollection()) {};

            virtual ~TrackCollections();
            
            inline StubBxCollection* getStubs() {return stubs_.get(); };
            inline StubBxCollection* getOutStubs() {return outstubs_.get(); };


         private:
            std::auto_ptr<StubBxCollection> stubs_;
            std::auto_ptr<StubBxCollection> outstubs_;
      };
   }
}

#endif
