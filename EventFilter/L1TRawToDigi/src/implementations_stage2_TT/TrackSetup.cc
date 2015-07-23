#include "FWCore/Framework/interface/stream/EDProducerBase.h"

#include "EventFilter/L1TRawToDigi/interface/Packer.h"
#include "EventFilter/L1TRawToDigi/interface/Unpacker.h"

#include "EventFilter/L1TRawToDigi/interface/PackingSetup.h"

#include "TrackCollections.h"
#include "TrackTokens.h"

namespace l1t {
   namespace phase2 {
      class TrackSetup : public PackingSetup {
         public:
            virtual std::unique_ptr<PackerTokens> registerConsumes(const edm::ParameterSet& cfg, edm::ConsumesCollector& cc) override {
               return std::unique_ptr<PackerTokens>(new TrackTokens(cfg, cc));
            };

            virtual void fillDescription(edm::ParameterSetDescription& desc) override {};

            virtual PackerMap getPackers(int fed, unsigned int fw) override {
               PackerMap res;

               if (fed == 1366) {
                  // Use board id 1 for packing
                  res[{1, 1}] = {
                     //PackerFactory::get()->make("phase2::StubPacker"),
                     
                  };
               }

               return res;
            };

            virtual void registerProducts(edm::stream::EDProducerBase& prod) override {
               prod.produces<StubBxCollection>("Input");
               prod.produces<StubBxCollection>("Output");
            };

            virtual std::unique_ptr<UnpackerCollections> getCollections(edm::Event& e) override {
               return std::unique_ptr<UnpackerCollections>(new TrackCollections(e));
            };

            virtual UnpackerMap getUnpackers(int fed, int board, int amc, unsigned int fw) override {
               auto stubs_unp = UnpackerFactory::get()->make("phase2::StubUnpacker");
               
               UnpackerMap res;
               if (fed == 1409){
               for (int link = 0; link < 144; link += 2)
                     res[link] = stubs_unp;
               }

               return res;
            };
      };
   }
}

DEFINE_L1T_PACKING_SETUP(l1t::phase2::TrackSetup);
