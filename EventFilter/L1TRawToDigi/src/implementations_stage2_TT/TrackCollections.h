#ifndef TrackCollections_h
#define TrackCollections_h

#include "DataFormats/L1TrackTrigger/interface/Stub.h"


//#include "EventFilter/L1TRawToDigi/interface/UnpackerCollections.h"
#include "EventFilter/L1TRawToDigi/interface/UnpackerCollections.h"

namespace l1t {
   namespace phase2 {
     class TrackCollections : public UnpackerCollections {
         public:
            TrackCollections(edm::Event& e) :
               UnpackerCollections(e),
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
