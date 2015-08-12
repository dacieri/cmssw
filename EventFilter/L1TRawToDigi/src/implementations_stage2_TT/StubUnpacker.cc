#include "FWCore/Framework/interface/MakerMacros.h"

#include "EventFilter/L1TRawToDigi/interface/Unpacker.h"

#include "TrackCollections.h"

namespace l1t {
   namespace phase2 {
      class StubUnpacker : public Unpacker {
         public:
            virtual bool unpack(const Block& block, UnpackerCollections *coll) override;
      };
   }
}

// Implementation

namespace l1t {
namespace phase2 {
   bool
   StubUnpacker::unpack(const Block& block, UnpackerCollections *coll)
   {

     LogDebug("L1T") << "Block ID  = " << block.header().getID() << " size = " 
     << block.header().getSize();

     int nBX = int(ceil(block.header().getSize()/288.)); 
     // Since there are two Rx links per block with 2*28 slices in barrel and endca$

     // Find the first and last BXs
     int firstBX = -(std::ceil((double)nBX/2.)-1);
     int lastBX;
     if (nBX % 2 == 0) {
       lastBX = std::ceil((double)nBX/2.);
     } else {
       lastBX = std::ceil((double)nBX/2.)-1;
     }

     auto res_ = static_cast<TrackCollections*>(coll)->getStubs();
     res_->setBXRange(std::min(firstBX, res_->getFirstBX()), std::max(lastBX, 
     res_->getLastBX()));

     LogDebug("L1T") << "nBX = " << nBX << " first BX = " << firstBX <<
      " lastBX = " << lastBX;

     // Initialise index
     int unsigned i = 0;

     // Link number is block_ID / 2
     // unsigned link = block.header().getID()/2;

     // Also need link number rounded down to even number


     // Loop over multiple BX and fill towers collection
     int bx=firstBX;

     for (unsigned frame=1; frame<288 && frame<(block.header().getSize()+1); frame+=2){

       uint32_t raw_data = block.payload()[i++];
       l1t::Stub stub = l1t::Stub();
       if ((raw_data & 0xFFFFFFFF) != 0) {
        // First calo tower is in the LSW with phi
        stub.setS(raw_data & 0x3F);
        stub.setphiS((raw_data >> 6) & 0xFFF );
        stub.setz((raw_data >> 18) & 0xFFF );
      }
      raw_data = block.payload()[i++];

      if ((raw_data & 0xFFFFFFFF) != 0) {
        stub.setrT(raw_data & 0x1FF);
        stub.setdphi((raw_data >> 9) & 0x3F);
        stub.setrho((raw_data >> 15)& 0x3F );
        stub.setm_bin((raw_data >> 21) & 0x3F);
        stub.setc_bin((raw_data >> 27) & 0x1F);
      }

     /* LogDebug("L1T") << "Stub : Segment " << stub.S()
      << " phi " << stub.phiS()
     LogDebug("L1T") << "Stub : Segment " << stub.S()
      << " phi " << stub.phiS()
      << " rT " << stub.rT()
      << " z " << stub.z()
      << " dphi " << stub.dphi()
      << " rho " << stub.rho()
      << " m_bin " << stub.m_bin()
      << " c_bin " << stub.c_bin();*/

      if(stub.S()==48){
        bx++;
	break;
      }
      else
       res_->push_back(bx,stub);
   }




     return true;

  }
}
}

DEFINE_L1T_UNPACKER(l1t::phase2::StubUnpacker);


