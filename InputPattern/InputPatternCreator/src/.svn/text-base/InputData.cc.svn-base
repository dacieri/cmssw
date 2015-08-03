#include "InputPattern/InputPatternCreator/interface/InputData.h"
#include "InputPattern/InputPatternCreator/interface/Settings.h"

using namespace std;
 
InputData::InputData(const edm::Event& iEvent, const edm::EventSetup& iSetup, Settings* settings) {

  // Get the B-field and store its value in the Settings class.
 
  edm::ESHandle<MagneticField> magneticFieldHandle;
  iSetup.get<IdealMagneticFieldRecord>().get(magneticFieldHandle);
  const MagneticField* theMagneticField = magneticFieldHandle.product();
  float bField = theMagneticField->inTesla(GlobalPoint(0,0,0)).z(); // B field in Tesla.
  static bool first = true;
  if (first) {  
    first = false;
    cout<<endl<<"--- B field ="<<bField<<" Tesla ---"<<endl<<endl;
  }
  settings->setBfield(bField);

  vHwStubs_.reserve(35000);

  // Get the tracker geometry info needed to unpack the stub info.

  edm::ESHandle<StackedTrackerGeometry> stackedGeometryHandle;
  iSetup.get<StackedTrackerGeometryRecord>().get( stackedGeometryHandle );

  const StackedTrackerGeometry*  stackedGeometry = stackedGeometryHandle.product();

  // Get stub info, by looping over modules and then Hwstubs inside each module.
  // Also get the association map from Hwstubs to tracking particles.

  edm::Handle<DetSetVec>       ttStubHandle;
  iEvent.getByLabel("TTStubsFromPixelDigis", "StubAccepted"    , ttStubHandle           );

  unsigned int stubCount = 0;
  for (DetSetVec::const_iterator p_module = ttStubHandle->begin(); p_module != ttStubHandle->end(); p_module++) {

    for (DetSet::const_iterator p_ttstub = p_module->begin(); p_ttstub != p_module->end(); p_ttstub++) {

      TTStubRef ttStubRef = edmNew::makeRefTo(ttStubHandle, p_ttstub );
      // Store the Stub info, using class Stub to provide easy access to the most useful info.
      HwStub hwstub;
      FillHwStub(ttStubRef, stackedGeometry, settings, hwstub);
      // Also fill truth associating stubs to tracking particles.
      if(fabs(hwstub.eta())<=settings->getEtaCut()){
              vHwStubs_.push_back( hwstub );
            stubCount++;}
    }
  }

  // Produced reduced list containing only the subset of stubs that the user has declared will be 
  // output by the front-end readout electronics.
  
}


void InputData::FillHwStub(TTStubRef tf, const StackedTrackerGeometry*  stackedGeometry, const Settings* settings, HwStub& hwstub){
   // Get coordinates of stub.


  const TTStub<Ref_PixelDigi_> *ttStubP = tf.get(); 

  GlobalPoint pos = stackedGeometry->findGlobalPosition(ttStubP);
  StackedTrackerDetId stDetId = tf->getDetId();

  double bend = 0.;
  double bend0 = tf->getTriggerBend();
  if (stDetId.isEndcap() && pos.z() > 0) bend0 *= -1;

  if(settings->getDataCorrection()){
        if (stDetId.isBarrel()) {
          unsigned int layer = stDetId.iLayer();
          bend = ConvertBarrelBend( bend0, layer );
        } 
        else {
          unsigned int ring = stDetId.iRing();
          bend = ConvertEndcapBend( bend0, ring );
        }
  }
  else
    bend = bend0;  
  

  double chosenRofPhi = settings->getChosenRofPhi();
  int hwz = (int)(pos.z()*settings->getZMultiplier());
  int hwRt = (int)((pos.perp()-chosenRofPhi)*settings->getRtMultiplier());

  float rErr_ = 0.;
  if ( ! stackedGeometry->isPSModule(stDetId) ) {
    if (!stDetId.isBarrel()) 
      rErr_ = 0.5*5.; 
  }
  const GeomDetUnit* det0 = stackedGeometry->idToDetUnit( stDetId, 0 );
  const GeomDetUnit* det1 = stackedGeometry->idToDetUnit( stDetId, 1 );
  

  float R0 = det0->position().perp();
  float R1 = det1->position().perp();
  float Z0 = det0->position().z();
  float Z1 = det1->position().z();
  float sensorSpacing = stDetId.isBarrel() ? fabs(R1 - R0) : fabs(Z1 - Z0);

  float pitch = stackedGeometry->isPSModule(stDetId) ? settings->pitchPS() : settings->pitch2S();
  float deltaR = stDetId.isBarrel() ? sensorSpacing : sensorSpacing*pos.perp()/fabs(pos.z()) ; // Diff in radius of coords where track crosses the two sensors.
  float dphiOverBend = pitch/deltaR;
  float dphi = bend * dphiOverBend;
  float rho = dphiOverBend * settings->getBendResolution();

  int hwRho = (int)(rho*settings->getRhoMultiplier()); 
  int hwDphi = (int)(dphi*settings->getDphiMultiplier());
   

  
  hwstub.setRho(hwRho);
  hwstub.setDphi(hwDphi);
  hwstub.setRt(hwRt);
  hwstub.setZ(hwz);
  hwstub.setDoubleZ(pos.z());
  hwstub.setDoubleR(pos.perp());
  hwstub.setDoublePhi(pos.phi());
  hwstub.setDoubleBend(bend);
  hwstub.setDphi(dphi);
  hwstub.setRerr(rErr_);
  hwstub.setEta(pos.eta());

  
}

