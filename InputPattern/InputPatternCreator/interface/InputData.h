#ifndef __INPUTDATA_H__
#define __INPUTDATA_H__
#define _USE_MATH_DEFINES

#include "InputPattern/InputPatternCreator/interface/HwStub.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/EncodedEventId/interface/EncodedEventId.h"

#include "Geometry/Records/interface/StackedTrackerGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/StackedTrackerGeometry.h"

// TTStubAssociationMap.h forgets to two needed files, so must include them here ...
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimTracker/TrackTriggerAssociation/interface/TTClusterAssociationMap.h"
#include "SimTracker/TrackTriggerAssociation/interface/TTStubAssociationMap.h"


#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/DetSetVector.h"

#include "DataFormats/L1TrackTrigger/interface/TTTypes.h"
#include "DataFormats/L1TrackTrigger/interface/TTStub.h"
#include "DataFormats/SiPixelDigi/interface/PixelDigi.h"
#include "InputPattern/InputPatternCreator/interface/DataCorrection.h"
#include "InputPattern/InputPatternCreator/interface/Sectors.h"
#include <math.h>
#include <vector>
#include "boost/numeric/ublas/matrix.hpp"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"

class StackedTrackerGeometry;
class StackedTrackerDetId;

typedef edmNew::DetSetVector< TTStub<Ref_PixelDigi_> > DetSetVec;
typedef edmNew::DetSet< TTStub<Ref_PixelDigi_> > DetSet;
typedef edm::Ref<DetSetVec, TTStub<Ref_PixelDigi_> > TTStubRef;
typedef TTStubAssociationMap<Ref_PixelDigi_> TTStubAssMap;

class Settings;

using namespace std;

class InputData {

public:
  
  InputData(const edm::Event& iEvent, const edm::EventSetup& iSetup,  Settings* settings);

  // Get stubs that would be output by the front-end readout electronics 
  const vector<HwStub>& getHwStubs()    const {return vHwStubs_;}

  //--- of minor importance ...

  // Get number of stubs prior to applying tighted front-end readout electronics cuts specified in section StubCuts of Analyze_Defaults_cfi.py. (Only used to measure the efficiency of these cuts).

  void FillHwStub(TTStubRef tf, const StackedTrackerGeometry*  stackedGeometry, const Settings* settings, HwStub& hwstub);

private:

  
  vector<HwStub> vHwStubs_; // Hwstubs that would be output by the front-end readout electronics.

  //--- of minor importance ...

};
#endif