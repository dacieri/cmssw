#ifndef L1TCollections_h
#define L1TCollections_h

#include "DataFormats/L1Trigger/interface/Stub.h"

#include "EventFilter/L1TRawToDigi/interface/UnpackerCollections.h"

namespace l1t {
   namespace phase2 {
     class L1TObjectCollections : public UnpackerCollections {
       public:
         L1TObjectCollections(edm::Event& e) :
           UnpackerCollections(e) { };
	 virtual ~L1TObjectCollections() ;

	 virtual StubBxCollection* getStubs() = 0;
	 
	 
      };
   }
}

#endif
