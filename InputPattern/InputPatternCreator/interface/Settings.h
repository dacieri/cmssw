#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <vector>


using namespace std;

// Stores all configuration parameters + some hard-wired constants.


class Settings {

public:
  Settings(const edm::ParameterSet& iConfig);
  ~Settings(){}

  string          getFilename()           const {  return filename_              ;}
  unsigned        getNChan()              const {  return nChan_                 ;}
  unsigned        getNQuad()              const {  return nQuad_                 ;}

  unsigned        getNLink()              const {  return nLink_                 ;}
  unsigned        getNHeaderFrames()      const {  return nHeaderFrames_         ;}
  unsigned        getNPayloadFrames()     const {  return nPayloadFrames_        ;}
  unsigned        getNClearFrames()       const {  return nClearFrames_          ;}
  int             getEventsPerFile()      const {  return nEventsPerFile_        ;}

  double          getEtaCut()             const {  return eta_cut_               ;}

  vector<double>  getEtaRegions()         const {  return eta_regions_           ;}
  bool            getSingleSegment()      const {  return single_segment_        ;}
  bool            getSingleRegion()       const {  return single_region_         ;}
  int             getPhiSegment()         const {  return phi_segment_           ;}
  int             getEtaRegion()          const {  return eta_region_            ;}
  unsigned int    getNPhiSectors()        const {  return n_phi_segments_        ;}
  unsigned int    getNEtaRegions()        const {  return eta_regions_.size()-1  ;}
  double          getChosenRofZ()         const {  return chosenRofZ_            ;}

  bool            getUseStubPhi()         const {  return UseStubPhi_            ;}
  bool            getUseStubPhiTrk()      const {  return UseStubPhiTrk_         ;}
  double          getChosenRofPhi()       const {  return chosenRofPhi_          ;}
  double          getMinPt()              const {  return minPt_                 ;}
  double          getAssumedPhiTrkRes()   const {  return AssumedPhiTrkRes_      ;}
  double          getBendResolution()     const {  return bendResolution_        ;}
  bool            getDataCorrection()     const {  return dataCorrection_        ;} 

  int             Splitting()             const {  return splitting_             ;}
  int             getSegmentBits()        const {  return segment_bits_          ;}
  int             getPhiSBits()           const {  return phiS_bits_             ;}
   int             getPhiSMultiplier()     const {  return phiS_multiplier_       ;}
  int             getZBits()              const {  return z_bits_                ;}
  int             getZMultiplier()        const {  return z_multiplier_          ;}
  int             getRtBits()             const {  return rt_bits_               ;}
  int             getRtMultiplier()       const {  return rt_multiplier_         ;}
  int             getDphiBits()           const {  return dphi_bits_             ;}
  int             getDphiMultiplier()     const {  return dphi_multiplier_       ;}
  int             getRhoBits()            const {  return rho_bits_              ;}
  int             getRhoMultiplier()      const {  return rho_multiplier_        ;}

  bool            getDebug()              const {  return debug_                 ;}

  double          getInvPtToDphi()        const {  return bField_*(3.0E8/2.0E11) ;} 
  double          pitchPS()               const {  return 0.010                  ;} // pitch of PS modules
  double          pitch2S()               const {  return 0.009                  ;} // pitch of 2S modules

  //=== Set and get B-field value in Tesla. 
  // N.B. This must bet set for each event, and can't be initialized at the beginning of the job.
  void                 setBfield(float bField)           {bField_ = bField;}
  float                getBfield()                       {return bField_;}
 


private:
  edm::ParameterSet OutputSpec_;
  edm::ParameterSet StubCut_;
  edm::ParameterSet PhiSectors_;
  edm::ParameterSet EtaRegions_;
  edm::ParameterSet DataFormats_;

  // Output Specifications

  string filename_; 
  unsigned nChan_;  // number of channels per quad
  unsigned nQuad_;
  unsigned nLink_;
  unsigned nHeaderFrames_;
  unsigned nPayloadFrames_;
  unsigned nClearFrames_;
  int      nEventsPerFile_;
  

  double eta_cut_;

  // Phi Sector parameters

  int n_phi_segments_;
  bool single_segment_; 
  int phi_segment_;
  bool UseStubPhi_;
  bool UseStubPhiTrk_;
  double AssumedPhiTrkRes_;
  double chosenRofPhi_;
  double minPt_;
  double bendResolution_;
  bool dataCorrection_;
  // Eta Segments
  vector<double> eta_regions_;
  bool single_region_;
  int eta_region_;
  double chosenRofZ_;

  // DataFormats
  int splitting_;
  int segment_bits_;
  int phiS_bits_;
  int phiS_multiplier_;
  int z_bits_;
  int z_multiplier_;
  int rt_bits_;
  int rt_multiplier_;
  int dphi_bits_;
  int dphi_multiplier_;
  int rho_bits_;
  int rho_multiplier_;

  // Debug printout
  bool debug_;
  float bField_;
};

#endif
