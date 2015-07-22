#ifndef __SECTOR_H__
#define __SECTOR_H__

#include <vector>
#include <unordered_map>
#include "InputPattern/InputPatternCreator/interface/HwStub.h"


class Settings;

class Sector {

public:
  
  Sector() {}
  ~Sector() {}

  // Initialization.
  void init(const Settings* settings, unsigned int iPhiSec, unsigned int iEtaSec);

  // Check if stub within the eta and/or phi boundaries of this sector.
  bool inside   (  HwStub stub ) const {return (this->insideEta(stub) && this->insidePhi(stub));}
  bool insideEta(  HwStub stub ) const;
  bool insidePhi(  HwStub stub ) const;

  float phiCentre() const { return phiCentre_; } // Return phi of centre of this sector.
  float etaMin()    const { return etaMin_; } // Eta range covered by this sector.
  float etaMax()    const { return etaMax_; } // Eta range covered by this sector.

  

private:

  const Settings* settings_;

  float  beamWindowZ_;
  float  trackerOuterRadius_;
  float  trackerInnerRadius_;
  float  trackerHalfLength_;
  bool   handleStripsPhiSec_;
  bool   handleStripsEtaSec_;
  // Define eta region.
  float  etaMin_; // Range in eta covered by this sector.
  float  etaMax_;
  float  chosenRofZ_; // Use z of track at radius="chosenRofZ" to define eta sectors.
  float  rOuterMax_; // Larger eta boundary point (r,z)
  float  zOuterMax_;
  float  rOuterMin_; // Smaller eta boundary point (r,z)
  float  zOuterMin_;
  float invPtToDphi_;

  // Define phi sector.
  float  phiCentre_; // phi of centre of sector.
  float  sectorHalfWidth_; // sector half-width excluding overlaps.
  float  chosenRofPhi_; // Use phi of track at radius="chosenRofPhi" to define phi sectors.
  bool   useStubPhi_; // Require stub phi to be consistent with track of Pt > HTArraySpec.HoughMinPt that crosses HT phi axis?
  float  minPt_; // Min Pt covered by HT array.
  bool   useStubPhiTrk_;  // Require stub phi0 (or phi65 etc.) as estimated from stub bend, to lie within HT phi axis, allowing tolerance specified below?
  float  assumedPhiTrkRes_; // Tolerance in stub phi0 (or phi65) assumed to be this fraction of phi sector width. (N.B. If > 0.5, then stubs can be shared by more than 2 phi sectors). 
  bool   calcPhiTrkRes_; // If true, tolerance in stub phi0 (or phi65 etc.) will be reduced below AssumedPhiTrkRes if stub bend resolution specified in HTFilling.BendResolution suggests it is safe to do so.
};
#endif

