#include "InputPattern/InputPatternCreator/interface/InputPatternCreator.h"

using boost::numeric::ublas::matrix;
using namespace std;
using namespace edm;

InputPatternCreator::InputPatternCreator(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed
  settings_ = new Settings(iConfig);
  nQuad_ = settings_->getNQuad();
  nChan_ = settings_->getNChan();
  nHeaderFrames_ = settings_->getNHeaderFrames();
  nPayloadFrames_ = settings_->getNPayloadFrames();
  nClearFrames_ = settings_->getNClearFrames();
  filename_ = settings_->getFilename();

  nLink_          = nChan_ * nQuad_;
  
  LogDebug("L1TDebug") << "Preparing for " << nLink_ << " links" << std::endl;

  nevent_=0;

  produces<StubCollection>( "inputStubs" ).setBranchAlias("inputStubs");
}


InputPatternCreator::~InputPatternCreator()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}

// ------------ method called for each event  ------------
void
InputPatternCreator::produce( edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  // Initialize the nFrame array
  if((nevent_)%2==0){
    for (unsigned int i = 0; i < settings_->getNEtaRegions(); i++)
    {
      nFrame_[i]=0;
            data_[i].resize(nLink_);
    }
  }

  

  // Collect data from the event
  InputData inputData(iEvent, iSetup, settings_);

  // Getting the stubs
  const vector<HwStub>& vhwStubs = inputData.getHwStubs();
  vector<HwStub>::const_iterator stub = vhwStubs.begin();
  cout << "Number of Stubs in the event " <<vhwStubs.size() << endl;
  auto_ptr<StubCollection> inputStubs ( new StubCollection );
  const int size = vhwStubs.size();
  inputStubs->reserve(size);
 
  // Creates matrix of Sector objects, which decide which stubs are in which (eta,phi) sector
  matrix<Sector>  mSectors(settings_->getNPhiSectors(), settings_->getNEtaRegions());
  // Creates matrix of HwStub objects 
  // matrix< std::vector<HwStub> > mStubs(settings_->getNPhiSectors(), settings_->getNEtaRegions());
  std::vector<HwStub> StoredStubs[5];
  // Initialization loop for sectors and stubs
  for (unsigned int iEtaReg = 0; iEtaReg < settings_->getNEtaRegions(); iEtaReg++) {

    for (unsigned int iPhiSec = 0; iPhiSec < settings_->getNPhiSectors(); iPhiSec++) {
      // Initialize sectors
      Sector& sector = mSectors(iPhiSec, iEtaReg);
      sector.init(settings_, iPhiSec, iEtaReg);
      int stub_in_sector =0;

      vector<HwStub>::const_iterator stub = vhwStubs.begin();
      for ( ; stub != vhwStubs.end(); stub++ ) {
        // Check if stub is inside this sector
        
        bool inside = sector.inside( *stub );
        // If so, then store it in the correspondent hwstub array for this sector.
        if (inside) {
          HwStub hws = *stub;
          hws.setSegment(iPhiSec);
          double phiS = hws.phi() - (2*M_PI/settings_->getNPhiSectors()) + M_PI;
          int phiS_multiplier = settings_->getPhiSMultiplier();
          
          int hwphi = (int)(phiS*phiS_multiplier );

          hws.setPhiS(hwphi); 
          // mStubs(iPhiSec, iEtaReg).push_back(hws);
          StoredStubs[iEtaReg].push_back(hws);

          l1t::Stub st(hws.hwSegment(), hws.hwPhiS(), hws.hwRt(), hws.hwZ(), hws.hwDphi(), hws.hwRho(), 0, 0, 0);
          inputStubs->push_back(st);
          stub_in_sector++;
        }
      }
      // cout << "Stubs in sector ("<<iEtaReg<<","<<iPhiSec<<") :"<< stub_in_sector << endl;
    }
  }

  iEvent.put( inputStubs, "inputStubs" );

  if(settings_->Splitting()==0)  
    WriteDataOverFrames(StoredStubs);
  else if(settings_->Splitting()==1)
    WriteDataOverLinks(StoredStubs);
  else {
    cout << "Splitting Parameter out of Range" << endl;
    exit(0);
  }


  

  if((nevent_-1)%settings_->getEventsPerFile()==0)
    write_file();

  nevent_++;

}


// ------------ method called once each job just before starting event loop  ------------
void 
InputPatternCreator::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
InputPatternCreator::endJob() 
{
  
}

void InputPatternCreator::WriteDataOverFrames(std::vector<HwStub> StoredStubs[]){
  // Frame Loop
  for (unsigned int iEtaReg = 0; iEtaReg < settings_->getNEtaRegions(); iEtaReg++) {
    // insert header frames
    unsigned int i = 0;
    for ( unsigned iFrame=0; iFrame<nHeaderFrames_; ++iFrame ) {
      dataValid_.push_back( 1 );
      // loop over links                                            
      for ( unsigned iQuad=0; iQuad<nQuad_; ++iQuad ) {
        for ( unsigned iChan=0; iChan<nChan_; ++iChan ) {
          int data=0;
          unsigned iLink = (iQuad*nChan_)+iChan;
            // add data to output                                                   
          data_[iEtaReg].at(iLink).push_back( data );
        }
      }
      nFrame_[iEtaReg]++;
    }
    // loop over payload frames
      
    int k=0;



  for ( unsigned iFrame=0; iFrame<nPayloadFrames_; ++iFrame ) {
      dataValid_.push_back( 1 );
      // loop over links
        
      if((k+2)%2==0)
        i=iFrame*36;
      else
        i=(iFrame-1)*36 ;

      k++;
      for ( unsigned iQuad=0; iQuad<nQuad_; ++iQuad ) {
        for ( unsigned iChan=0; iChan<nChan_; ++iChan ) {
          HwStub stub;
          if(i<StoredStubs[iEtaReg].size())
            stub = StoredStubs[iEtaReg].at(i);
          else if(i==StoredStubs[iEtaReg].size()){
            double fakePhi= 0.1;
            int hwFakePhi = (int)(fakePhi*settings_->getPhiSMultiplier());
            stub.setPhiS(hwFakePhi);
            stub.setSegment(48);
          }

          int data=0;

          int iLink = (iQuad*nChan_)+iChan;

          // Stub data are splitted in two links, so we increase the index i any two links
          if((k+2)%2==0){           
            data |= (stub.hwRt() & (int(pow(2.,double(settings_->getRtBits())))-1));//writing R65
            data |= (stub.hwDphi() & (int(pow(2.,double(settings_->getDphiBits())))-1)) << settings_->getRtBits();//writing the Dphi information
            data |= (stub.hwRho() & (int(pow(2.,double(settings_->getRhoBits())))-1)) << (settings_->getRtBits() + settings_->getDphiBits());//writing the Dphi information
            
          }
          else{
            data |= stub.hwSegment() & (int(pow(2., double(settings_->getSegmentBits())) -1 ) );

            data |= (stub.hwPhiS() & (int(pow(2.,double(settings_->getPhiSBits()))) -1)) << settings_->getSegmentBits(); // Writing the phi information
            data |= (stub.hwZ() & (int(pow(2.,double(settings_->getZBits())))-1)) << (settings_->getPhiSBits()+ settings_->getSegmentBits());//writing z          
            
          } 

          data_[iEtaReg].at(iLink).push_back( data );
          i++;
        }
      }

      nFrame_[iEtaReg]++;
      if(i>=StoredStubs[iEtaReg].size()+72)
        break;
    }
   
    // loop over clear frames
    for ( unsigned iFrame=0; iFrame<nClearFrames_; ++iFrame ) {

      dataValid_.push_back( 0 );

        // loop over links
      for ( unsigned iQuad=0; iQuad<nQuad_; ++iQuad ) {
        for ( unsigned iChan=0; iChan<nChan_; ++iChan ) {

          int data=0;

          unsigned iLink = (iQuad*nChan_)+iChan;

           // add data to output
          data_[iEtaReg].at(iLink).push_back( data );
        }
      }

      nFrame_[iEtaReg]++;

    }
  }
}


void InputPatternCreator::WriteDataOverLinks(std::vector<HwStub> StoredStubs[]){
  // Frame Loop
  for (unsigned int iEtaReg = 0; iEtaReg < settings_->getNEtaRegions(); iEtaReg++) {
    // insert header frames
    for ( unsigned iFrame=0; iFrame<nHeaderFrames_; ++iFrame ) {
      dataValid_.push_back( 1 );
      // loop over links                                            
      for ( unsigned iQuad=0; iQuad<nQuad_; ++iQuad ) {
        for ( unsigned iChan=0; iChan<nChan_; ++iChan ) {
          int data=0;
          unsigned iLink = (iQuad*nChan_)+iChan;
            // add data to output                                                   
          data_[iEtaReg].at(iLink).push_back( data );
        }
      }
      nFrame_[iEtaReg]++;
    }
    // loop over payload frames
        unsigned int i = 0;

  for ( unsigned iFrame=0; iFrame<nPayloadFrames_; ++iFrame ) {
      dataValid_.push_back( 1 );
      // loop over links
      for ( unsigned iQuad=0; iQuad<nQuad_; ++iQuad ) {
        for ( unsigned iChan=0; iChan<nChan_; ++iChan ) {
          HwStub stub;
          if(i<StoredStubs[iEtaReg].size())
            stub = StoredStubs[iEtaReg].at(i);
          else if(i==StoredStubs[iEtaReg].size()){
            double fakePhi= 0.1;
            int hwFakePhi = (int)(fakePhi*settings_->getPhiSMultiplier());
            stub.setPhiS(hwFakePhi);
            stub.setSegment(48);
          }

          int data=0;

          int iLink = (iQuad*nChan_)+iChan;

          // Stub data are splitted in two links, so we increase the index i any two links
          if((iLink+2)%2==0){
            
            data |= stub.hwSegment() & (int(pow(2., double(settings_->getSegmentBits())) -1 ) );
            data |= (stub.hwPhiS() & (int(pow(2.,double(settings_->getPhiSBits()))) -1)) << settings_->getSegmentBits(); // Writing the phi information
            data |= (stub.hwZ() & (int(pow(2.,double(settings_->getZBits())))-1)) << (settings_->getPhiSBits()+ settings_->getSegmentBits());//writing z
            data_[iEtaReg].at(iLink).push_back( data );
            
            data = 0;

            data |= (stub.hwRt() & (int(pow(2.,double(settings_->getRtBits()))) -1));//writing R65
            data |= (stub.hwDphi() & (int(pow(2.,double(settings_->getDphiBits())))-1)) << settings_->getRtBits();//writing the Dphi information
            data |= (stub.hwRho() & (int(pow(2.,double(settings_->getRhoBits())))-1)) << (settings_->getRtBits() + settings_->getDphiBits());//writing the Dphi information
 
            data_[iEtaReg].at(iLink+1).push_back(data);
            

            i++;
          }   
        }
      }

      nFrame_[iEtaReg]++;
      if(i>=StoredStubs[iEtaReg].size()+72)
        break;
    }
   
    // loop over clear frames
    for ( unsigned iFrame=0; iFrame<nClearFrames_; ++iFrame ) {

      dataValid_.push_back( 0 );

        // loop over links
      for ( unsigned iQuad=0; iQuad<nQuad_; ++iQuad ) {
        for ( unsigned iChan=0; iChan<nChan_; ++iChan ) {

          int data=0;

          unsigned iLink = (iQuad*nChan_)+iChan;

           // add data to output
          data_[iEtaReg].at(iLink).push_back( data );
        }
      }

      nFrame_[iEtaReg]++;

    }
  }
}




void InputPatternCreator::write_file()
{

// Loop over the trigger regions
  for (unsigned int i = 0; i < settings_->getNEtaRegions(); i++)
  {
    cout << "data size "<< data_[i].size() << endl;

  LogDebug("L1TDebug") << "Read " << nFrame_[i] << " frames" << std::endl;
  std::ostringstream filename;
  filename.str("");
  filename.clear();
  filename << filename_ << (nevent_-1)/2 << "_" << i << ".txt";

  // write file
  std::ofstream file( filename.str().c_str() );

  file << "Board MP7_TEST Event" << nevent_ << std::endl;

  // quad/chan numbers
  file << " Quad/Chan : ";
  for ( unsigned i=0; i<nQuad_; ++i ) {
    for ( unsigned j=0; j<nChan_; ++j ) {
      file << "   q" << i << "c" << j << "   ";
    }
  }
  file << std::endl;

  // link numbers
  file << "      Link : ";
  for ( unsigned i=0; i<nQuad_; ++i ) {
    for ( unsigned j=0; j<nChan_; ++j ) {
      file << "    " << (i*nChan_)+j << "       ";
    }
  }

  file << std::endl;

  // then the data
  for ( unsigned iFrame=0; iFrame<nFrame_[i]; ++iFrame ) {
    file << "Frame " << std::dec << std::setw(4) << std::setfill('0') << iFrame << " : ";
    for ( unsigned iQuad=0; iQuad<nQuad_; ++iQuad ) {
      for ( unsigned iChan=0; iChan<nChan_; ++iChan ) {
       unsigned iLink = (iQuad*nChan_)+iChan;
       if (iLink<data_[i].size() && iFrame<data_[i].at(iLink).size()) {
         file << std::hex << ::std::setw(1) << dataValid_.at(iFrame) << "v" << std::hex << std::setw(8) << std::setfill('0') << data_[i].at(iLink).at(iFrame) << " ";
       }
       else {
         std::cerr << "Out of range : " << iLink << ", " << iFrame << std::endl;
       }
     }
   }
   file << std::endl;
 }

 file.close();
 data_[i].clear();
  }


}

// ------------ method called when starting to processes a run  ------------
/*
  void 
  InputPatternCreator::beginRun(edm::Run const&, edm::EventSetup const&)
  {
  }
*/

// ------------ method called when ending the processing of a run  ------------
/*
  void 
  InputPatternCreator::endRun(edm::Run const&, edm::EventSetup const&)
  {
  }
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
  void 
  InputPatternCreator::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
  {
  }
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
  void 
  InputPatternCreator::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
  {
  }
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
  void
  InputPatternCreator::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
  }

//define this as a plug-in
  DEFINE_FWK_MODULE(InputPatternCreator);
