// -*- C++ -*-
//
// Package:    L1Trigger/L1TrackTrigger
// Class:      L1TrackTriggerAnalyzer
// 
/**\class L1TrackTriggerAnalyzer L1TrackTriggerAnalyzer.cc L1Trigger/
L1TrackTrigger/plugins/L1TTrackTriggerAnalyzer.cc
 Description: [one line class summary]
 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  T.James
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "CondFormats/L1TObjects/interface/CaloParams.h"
#include "CondFormats/DataRecord/interface/L1TCaloParamsRcd.h"

#include "DataFormats/L1TrackTrigger/interface/Stub.h"


#include "TH1F.h"
#include "TH2F.h"

//
// class declaration
//

namespace l1t {

class L1TPhase2TrackTriggerAnalyzer : public edm::EDAnalyzer {
public:
  explicit L1TPhase2TrackTriggerAnalyzer(const edm::ParameterSet&);
  ~L1TPhase2TrackTriggerAnalyzer();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
  //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void beginLuminosityBlock(edm::LuminosityBlock const&,
  // edm::EventSetup const&) override;
  //virtual void endLuminosityBlock(edm::LuminosityBlock const&,
  // edm::EventSetup const&) override;
  
  // ----------member data ---------------------------

    edm::EDGetToken m_stubToken;

    bool m_doStubs;

  
  bool doText_;
  bool doHistos_;
  bool doEvtDisp_;

  enum ObjectType{MPStub=0x1};
  
  std::vector< ObjectType > types_;
  std::vector< std::string > typeStr_;
  
  std::map< ObjectType, TFileDirectory > dirs_;


  TFileDirectory evtDispDir_;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
  L1TPhase2TrackTriggerAnalyzer::L1TPhase2TrackTriggerAnalyzer
  (const edm::ParameterSet& iConfig) :
    doText_(iConfig.getUntrackedParameter<bool>("doText", true)),
    doHistos_(iConfig.getUntrackedParameter<bool>("doHistos", true))
{
   //now do what ever initialization is needed

std::cout << "Track Trigger Analyzer constructed" << std::endl;
  // register what you consume and keep token for later access:
  edm::InputTag nullTag("None");
std::cout << "Track Trigger Analyzer Constructor debug1" << std::endl;

  edm::InputTag stubTag = iConfig.getParameter<edm::InputTag>("stubToken");
std::cout << "Track Trigger Analyzer Constructor debug2" << std::endl;

  m_stubToken         = consumes<l1t::StubBxCollection>(stubTag);
std::cout << "Track Trigger Analyzer Constructor debug3" << std::endl;

  m_doStubs           = !(stubTag==nullTag);

std::cout << "Track Trigger Analyzer Constructor debug4" << std::endl;
  
    types_.push_back( MPStub );
std::cout << "Track Trigger Analyzer Constructor debug5" << std::endl;

    typeStr_.push_back( "stub" );
std::cout << "Track Trigger Analyzer Constructor debug6" << std::endl;


}


L1TPhase2TrackTriggerAnalyzer::~L1TPhase2TrackTriggerAnalyzer()
{
std::cout << "Track Trigger Analyzer destruction" << std::endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
L1TPhase2TrackTriggerAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

std::cout << "Track Trigger Analyzer:: analyze started" << std::endl;
  using namespace edm;

  std::stringstream text;

//  TH2F* hEvtStub = new TH2F();


  if (doEvtDisp_) {
    std::stringstream ss;
    ss << iEvent.run() << "-" << iEvent.id().event();
    TFileDirectory dir = evtDispDir_.mkdir(ss.str());
  //  hEvtStub = dir.make<TH2F>("Stub", "", 83, -41.5, 41.5, 72, .5, 72.5);
    
  }

  // get TPs ?
  // get regions ?
  // get RCT clusters ?

  

//get stubs
if (m_doStubs) {
    Handle< BXVector<l1t::Stub> > mpstubs;
    iEvent.getByToken(m_stubToken,mpstubs);
    
    for ( int ibx=mpstubs->getFirstBX(); ibx<=mpstubs->getLastBX(); ++ibx) {

      for ( auto itr = mpstubs->begin(ibx); itr != mpstubs->end(ibx); ++itr ) {
       // hbx_.at(MPStub)->Fill( ibx );


	text << "MP Stub: " << " BX=" << ibx << std::endl;
	//" ipt=" << itr->hwPt() << " ieta=" << itr->hwEta() <<
	// " iphi=" << itr->hwPhi() << std::endl;

	//if (doEvtDisp_) hEvtMStub->Fill( itr->hwEta(), itr->hwPhi(), itr->hwPt() );
      }
      
    }

  }
  

  if (doText_) edm::LogInfo("L1TrackTriggerEvents") << text.str();

}



// ------------ method called once each job just before starting event loop  ------------
void 
L1TPhase2TrackTriggerAnalyzer::beginJob()
{

std::cout << "Track Trigger Analyzer begin job" << std::endl;

  edm::Service<TFileService> fs;

std::cout << "Track Trigger Analyzer begin job debug 1" << std::endl;


  auto itr = types_.cbegin();
std::cout << "Track Trigger Analyzer begin job debug 2" << std::endl;

  auto str = typeStr_.cbegin();
std::cout << "Track Trigger Analyzer begin job debug 3" << std::endl;

  for (; itr!=types_.end(); ++itr, ++str ) {
std::cout << "Track Trigger Analyzer begin job debug 4" << std::endl;
    
   

  }

std::cout << "Track Trigger Analyzer begin job debug 5" << std::endl;

  if (doEvtDisp_) {
std::cout << "Track Trigger Analyzer begin job debug 6" << std::endl;

    evtDispDir_ = fs->mkdir("Events");
std::cout << "Track Trigger Analyzer begin job debug 7" << std::endl;

  }

}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1TPhase2TrackTriggerAnalyzer::endJob() 
{
std::cout << "Track Trigger Analyzer end job" << std::endl;
}

// ------------ method called when starting to processes a run  ------------
/*
void 
L1TPhase2TrackTriggerAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
L1TPhase2TrackTriggerAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
L1TPhase2TrackTriggerAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, 
edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
L1TPhase2TrackTriggerAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&,
 edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters 
//for the module  ------------
void
L1TPhase2TrackTriggerAnalyzer::fillDescriptions
(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
std::cout << "Track Trigger Analyzer fillDescriptions" << std::endl;
  edm::ParameterSetDescription desc;
std::cout << "Track Trigger Analyzer fillDescriptions debug 1" << std::endl;
  desc.setUnknown();
std::cout << "Track Trigger Analyzer fillDescriptions debug 2" << std::endl;

  descriptions.addDefault(desc);
std::cout << "Track Trigger Analyzer fillDescriptions debug 3" << std::endl;

}

}

using namespace l1t;

//define this as a plug-in
DEFINE_FWK_MODULE(L1TPhase2TrackTriggerAnalyzer);
