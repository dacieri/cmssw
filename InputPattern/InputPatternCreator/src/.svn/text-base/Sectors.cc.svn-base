#include "InputPattern/InputPatternCreator/interface/Sectors.h"
#include "InputPattern/InputPatternCreator/interface/Settings.h"

#include "DataFormats/Math/interface/deltaPhi.h"
#include <iostream>

using namespace std;

//=== Initialise
 
void Sector::init(const Settings* settings, unsigned int iPhiSec, unsigned int iEtaReg) {
  settings_ = settings;

  //===  Characteristics of this eta region.

  // Using lines of specified rapidity drawn from centre of CMS, determine the z coords at which
  // they cross the radius rChosenRofZ_.
  etaMin_ = settings->getEtaRegions()[iEtaReg];
  etaMax_ = settings->getEtaRegions()[iEtaReg + 1];
  chosenRofZ_ = settings->getChosenRofZ();
  zOuterMin_ = chosenRofZ_ / tan( 2. * atan(exp(-etaMin_)) );
  zOuterMax_ = chosenRofZ_ / tan( 2. * atan(exp(-etaMax_)) );
  
  //=== Characteristics of this phi region.

  phiCentre_ = 2.*M_PI * (0.5 + float(iPhiSec)) / float(settings->getNPhiSectors()) - M_PI; // Centre of sector in phi
  sectorHalfWidth_ = M_PI / float(settings->getNPhiSectors()); // Sector half width excluding overlaps.

  chosenRofPhi_     = settings->getChosenRofPhi();
  useStubPhi_       = settings->getUseStubPhi();
  minPt_            = settings->getMinPt(); // Min Pt covered by  HT array.
  useStubPhiTrk_    = settings->getUseStubPhiTrk();
  assumedPhiTrkRes_ = settings->getAssumedPhiTrkRes();
  invPtToDphi_ = settings->getInvPtToDphi();
}

//=== Check if stub is inside this eta region.

bool Sector::insideEta( HwStub stub ) const {
  // Lower edge of this eta region defined by line from (r,z) = (0,-beamWindowZ) to (rOuterMin, zOuterMin).
  // Upper edge of this eta region defined by line from (r,z) = (0, beamWindowZ) to (rOuterMax, zOuterMax).

  float zMin, zMax;

  bool inside;

    //--- Don't modify algorithm to allow for uncertainty in stub (r,z) coordinates caused by 2S module strip length?

    // Calculate z coordinate of lower edge of this eta region, evaluated at radius of stub.
  zMin = ( zOuterMin_ * stub.r() - beamWindowZ_ * fabs(stub.r() - chosenRofZ_) ) / chosenRofZ_;
    // Calculate z coordinate of upper edge of this eta region, evaluated at radius of stub.
  zMax = ( zOuterMax_ * stub.r() + beamWindowZ_ * fabs(stub.r() - chosenRofZ_) ) / chosenRofZ_;

  // cout << "zMin " << zMin << ", zMax " << zMax <<endl;
  // cout << "stub z "<< stub.z() <<endl;
  // // zMin = ( zOuterMin_ * stub.r() - beamWindowZ_ * fabs(stub.r() - rOuterMin_) ) / rOuterMin_;
  // zMax = ( zOuterMax_ * stub.r() + beamWindowZ_ * fabs(stub.r() - rOuterMax_) ) / rOuterMax_;

  inside = (stub.z() > zMin && stub.z() < zMax);
  return inside;
}


//=== Check if stub is inside this phi region.

bool Sector::insidePhi( HwStub stub ) const {

  bool okPhi    = true;
  bool okPhiTrk = true;

  if (useStubPhi_) {
    float delPhi = reco::deltaPhi(stub.phi(), phiCentre_); // Phi difference between stub & sector in range -PI to +PI.
    float tolerancePhi = fabs(stub.r() - chosenRofPhi_)*invPtToDphi_/minPt_; // How much stub phi might differ from track phi because of track curvature.
    float outsidePhi = fabs(delPhi) - sectorHalfWidth_ - tolerancePhi; // If > 0, then stub is not compatible with being inside this sector. 
    if (outsidePhi > 0) okPhi = false;
  }

  if (useStubPhiTrk_) {
    // Estimate either phi0 of track from stub info, or phi of the track at radius chosenRofPhi_.
    float phiTrk = stub.trkPhiAtR( chosenRofPhi_ ).first; // N.B. This equals stub.beta() if chosenRofPhi_ = 0.
    float delPhiTrk = reco::deltaPhi(phiTrk, phiCentre_); // Phi difference between stub & sector in range -PI to +PI.
    float tolerancePhiTrk = assumedPhiTrkRes_ * (2*sectorHalfWidth_); // Set tolerance equal to nominal resolution assumed in phiTrk
    
    float outsidePhiTrk = fabs(delPhiTrk) - sectorHalfWidth_ - tolerancePhiTrk; // If > 0, then stub is not compatible with being inside this sector.

    if (outsidePhiTrk > 0) okPhiTrk = false;
  }
  
  return (okPhi && okPhiTrk);
}




