#include "InputPattern/InputPatternCreator/interface/HwStub.h"
#include <math.h>
#include <iomanip>
#include <iostream>

HwStub::HwStub(
				int hwPhiS,
				int hwRt,
				int hwZ,
				int hwDphi,
        int hwSegment,
        int hwRho,
        double phi,
        double r,
        double z
				)
  : 
    hwPhiS_(hwPhiS),
    hwRt_(hwRt),
    hwZ_(hwZ),
    hwDphi_(hwDphi),
    hwSegment_(hwSegment),
    hwRho_(hwRho),
    phi_(phi),
    r_(r),
    z_(z)
{
  
}

HwStub::~HwStub() 
{

}


std::pair <float, float> HwStub::trkPhiAtR(float rad) const { 
  float rStubMax = r_ + rErr_; // Uncertainty in radial stub coordinate due to strip length.
  float rStubMin = r_ - rErr_;
  float trkPhi1 = (phi_ + dphi_*(1. - rad/rStubMin));
  float trkPhi2 = (phi_ + dphi_*(1. - rad/rStubMax));
  float trkPhi    = 0.5*    (trkPhi1 + trkPhi2);
  float errTrkPhi = 0.5*fabs(trkPhi1 - trkPhi2); 
  return std::pair<float, float>(trkPhi, errTrkPhi);
}
