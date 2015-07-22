#ifndef __INPUTPATTERNCREATOR_H__
#define __INPUTPATTERNCREATOR_H__
#define _USE_MATH_DEFINES

// -*- C++ -*-
//
// Package:    InputPatternCreator
// Class:      InputPatternCreator
// 
/**\class InputPatternCreator InputPatternCreator.cc InputPattern/InputPatternCreator/plugins/InputPatternCreator.cc

   Description: [one line class summary]

   Implementation:
   [Notes on implementation]
*/
//
// Original Author:  Davide Cieri <davide.cieri@stfc.ac.uk>
//         Created:  Tue, 19 May 2015 12:42:06 GMT
// $Id$
//
//


// system include files
#include <memory>
#include <bitset>


// user include files
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"

#include "DataFormats/SiPixelDigi/interface/PixelDigi.h"
#include "SimDataFormats/TrackerDigiSimLink/interface/PixelDigiSimLink.h"
#include "DataFormats/Common/interface/DetSet.h"
#include "DataFormats/Common/interface/DetSetVector.h"

#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/TrackingGeometry.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/CommonTopologies/interface/PixelTopology.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXFDetId.h"

#include "Geometry/Records/interface/StackedTrackerGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/StackedTrackerGeometry.h"

#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/Ptr.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"

#include "SimTracker/TrackTriggerAssociation/interface/TTClusterAssociationMap.h"
#include "SimTracker/TrackTriggerAssociation/interface/TTStubAssociationMap.h"

#include "DataFormats/L1TrackTrigger/interface/TTCluster.h"
#include "DataFormats/L1TrackTrigger/interface/TTStub.h"
#include "DataFormats/L1TrackTrigger/interface/TTTrack.h"
#include "DataFormats/L1TrackTrigger/interface/TTTypes.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TCanvas.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "InputPattern/InputPatternCreator/interface/HwStub.h"
#include "InputPattern/InputPatternCreator/interface/Settings.h"
#include "InputPattern/InputPatternCreator/interface/Sectors.h"
#include "InputPattern/InputPatternCreator/interface/InputData.h"
#include "boost/numeric/ublas/matrix.hpp"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "DataFormats/L1Trigger/interface/Stub.h"

typedef vector< vector<int> > DataVec;
   
//
// class declaration
//

using namespace std; 

class InputPatternCreator : public edm::EDProducer {
   public:
    explicit InputPatternCreator(const edm::ParameterSet&);
    ~InputPatternCreator();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


  private:
    virtual void beginJob() override;
    virtual void produce(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    void WriteDataOverFrames(std::vector<HwStub> StoredStubs[]);
    void WriteDataOverLinks(std::vector<HwStub> StoredStubs[]);

    void write_file();

  //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

  // ----------member data ---------------------------
    Settings *settings_;
    // data arranged by link and frame
    DataVec data_[5];
  	unsigned nChan_;  // number of channels per quad
  	unsigned nQuad_;
   unsigned nHeaderFrames_;
   unsigned nPayloadFrames_;
   unsigned nClearFrames_;

   unsigned nLink_;
   string filename_;
   unsigned nFrame_[5];
   int nevent_;

  	// data valid flags (just one per frame for now)
   vector<int> dataValid_; 

   // Producer member data
   typedef std::vector<l1t::Stub> StubCollection;

 };
#endif
