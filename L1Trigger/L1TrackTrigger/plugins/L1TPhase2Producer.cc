// -*- C++ -*-
//
// Package:    L1Trigger/skeleton
// Class:      skeleton
// 
/**\class skeleton skeleton.cc L1Trigger/skeleton/plugins/skeleton.cc
 Description: [one line class summary]
 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  James Brooke
//         Created:  Thu, 05 Dec 2013 17:39:27 GMT
//
//


// system include files
#include <boost/shared_ptr.hpp>

// user include files

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "L1Trigger/L1TrackTrigger/interface/Phase2FirmwareFactory.h"
#include "L1Trigger/L1TrackTrigger/interface/Phase2MainProcessor.h"

#include "CondFormats/L1TObjects/interface/TrackTriggerParams.h"
#include "CondFormats/DataRecord/interface/L1TCaloParamsRcd.h"

#include "DataFormats/L1TrackTrigger/interface/Stub.h"

//
// class declaration
//

using namespace l1t;
  
  class L1TPhase2Producer : public edm::EDProducer { 
  public:
    explicit L1TPhase2Producer(const edm::ParameterSet& ps);
    ~L1TPhase2Producer();
    
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions)
      ;
    
  private:
    virtual void beginJob() override;
    virtual void produce(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    
    virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, 
    //edm::EventSetup const&) override;
    //virtual void endLuminosityBlock(edm::LuminosityBlock 
    //const&, edm::EventSetup const&) override;
    
    // ----------member data ---------------------------

    // input token
    edm::EDGetToken m_stubToken;

    // parameters
    unsigned long long m_paramsCacheId;
    unsigned m_fwv;
    TrackTriggerParams* m_params;

    // the processor
    Phase2FirmwareFactory m_factory;
    boost::shared_ptr<Phase2MainProcessor> m_processor;
     
  }; 
  


L1TPhase2Producer::L1TPhase2Producer(const edm::ParameterSet& ps) {

std::cout<< "L1T Phase2 Producer constructor" << std::endl;
  // register what you produce
  produces<StubBxCollection> ("MP");

  
  // register what you consume and keep token for later access:
  m_stubToken = consumes<StubBxCollection>(ps.getParameter<edm::InputTag>("stubToken"));
  
  // placeholder for the parameters
  m_params = new TrackTriggerParams;

  // set firmware version from python config for now
  m_fwv = ps.getParameter<int>("firmware");
 
}

L1TPhase2Producer::~L1TPhase2Producer() {
  
  delete m_params;

}

// ------------ method called to produce the data  ------------
void
L1TPhase2Producer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  
  LogDebug("l1t|phase 2") << "L1TPhase2Producer::produce function called..." << std::endl;
  
  
  //inputs
  Handle< BXVector<Stub> > stubs;
  iEvent.getByToken(m_stubToken,stubs);
  
  int bxFirst = stubs->getFirstBX();
  int bxLast = stubs->getLastBX();

  LogDebug("L1TDebug") << "First BX=" << bxFirst << ", last BX=" << bxLast << std::endl;
  
  //outputs
  std::auto_ptr<StubBxCollection> outStubs (new StubBxCollection(0, bxFirst, bxLast));

  
  // loop over BX
  for(int ibx = bxFirst; ibx < bxLast+1; ++ibx) {
    std::auto_ptr< std::vector<Stub> > localStubs (new std::vector<Stub>);
    std::auto_ptr< std::vector<Stub> > localOutStubs (new std::vector<Stub>);
   
    
    LogDebug("L1TDebug") << "BX=" << ibx << ", N(Stubs)=" << stubs->size(ibx) << std::endl;

    for(std::vector<Stub>::const_iterator stub = stubs->begin(ibx);
	stub != stubs->end(ibx);
	++stub) {
      localStubs->push_back(*stub);
    }

    LogDebug("L1TDebug") << "BX=" << ibx << ", N(Stubs)=" << localStubs->size() << std::endl;    

    m_processor->processEvent(*localStubs,
			      *localOutStubs
);
    
    for(std::vector<Stub>::const_iterator stu = localOutStubs->begin(); 
    stu != localOutStubs->end(); ++stu) outStubs->push_back(ibx, *stu);



    LogDebug("L1TDebug") << "BX=" << ibx << ", N(Stub)=" 
    << localStubs->size() << std::endl;    

  }
  
  iEvent.put(outStubs, "MP");

  
}

// ------------ method called once each job just before starting event loop  ------------
void 
L1TPhase2Producer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1TPhase2Producer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
L1TPhase2Producer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{

  // update parameters and algorithms at run start, if they have changed
  // update params first because the firmware factory relies on pointer to params

  // parameters

 /* unsigned long long id = iSetup.get<L1TCaloParamsRcd>().cacheIdentifier();  
  
  if (id != m_paramsCacheId) {

    m_paramsCacheId = id;

    edm::ESHandle<TrackTriggerParams> paramsHandle;
    iSetup.get<L1TCaloParamsRcd>().get(paramsHandle);

    // replace our local copy of the parameters with a new one using placement new
    m_params->~TrackTriggerParams();
    m_params = new (m_params) TrackTriggerParams(*paramsHandle.product());
    
    LogDebug("L1TDebug") << *m_params << std::endl;

    if (! m_params){
      edm::LogError("l1t|tracktriggerPhase2") << "Could not retrieve params from Event Setup" 
      << std::endl;            
    }

  }*/

  // firmware

  if ( !m_processor ) { // in future, also check if the firmware cache ID has changed !
    
    //     m_fwv = ; // get new firmware version in future
    
    // Set the current algorithm version based on DB pars from database:
    m_processor = m_factory.create(m_fwv, m_params);
    
    if (! m_processor) {
      // we complain here once per run
      edm::LogError("l1t|tracktriggerStage2") 
      << "Firmware could not be configured.\n";
    }
    
    LogDebug("L1TDebug") << "Processor object : " << (m_processor?1:0) << std::endl;
    
  }
  

}


// ------------ method called when ending the processing of a run  ------------
void
L1TPhase2Producer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
/*
void
L1TPhase2Producer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup cons
t&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
L1TPhase2Producer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&
)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
L1TPhase2Producer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(L1TPhase2Producer);
