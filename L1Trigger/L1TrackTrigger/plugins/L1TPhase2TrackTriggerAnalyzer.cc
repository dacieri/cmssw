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

  // register what you consume and keep token for later access:
  edm::InputTag nullTag("None");

  edm::InputTag stubTag = iConfig.getParameter<edm::InputTag>("stubToken");
  m_stubToken         = consumes<l1t::StubBxCollection>(stubTag);
  m_doStubs           = !(stubTag==nullTag);

  
    types_.push_back( MPStub );

    typeStr_.push_back( "stub" );


}


L1TPhase2TrackTriggerAnalyzer::~L1TPhase2TrackTriggerAnalyzer()
{
 
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

  edm::Service<TFileService> fs;

  auto itr = types_.cbegin();
  auto str = typeStr_.cbegin();

  for (; itr!=types_.end(); ++itr, ++str ) {
    
   

  }

  if (doEvtDisp_) {
    evtDispDir_ = fs->mkdir("Events");
  }

}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1TPhase2TrackTriggerAnalyzer::endJob() 
{
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
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

}

using namespace l1t;

//define this as a plug-in
DEFINE_FWK_MODULE(L1TPhase2TrackTriggerAnalyzer);
