#include <InputPattern/InputPatternCreator/interface/Settings.h>
#include "FWCore/Utilities/interface/Exception.h"

///=== Get configuration parameters

Settings::Settings(const edm::ParameterSet& iConfig)

  // See either Analyze_Defaults_cfi.py or Settings.h for description of these parameters.

  // Parameter sets for differents types of configuration parameter.
  
{

  OutputSpec_     = iConfig.getParameter< edm::ParameterSet >   ( "OutputSpec"            );
  PhiSectors_     = iConfig.getParameter< edm::ParameterSet >   ( "PhiSectors"            );
  EtaRegions_     = iConfig.getParameter< edm::ParameterSet >   ( "EtaRegions"            );
  DataFormats_    = iConfig.getParameter< edm::ParameterSet >   ( "DataFormats"            );

  filename_       = OutputSpec_.getUntrackedParameter<std::string>  ("filename");
  nChan_          = OutputSpec_.getUntrackedParameter<unsigned>     ("nChanPerQuad"        );
  nQuad_          = OutputSpec_.getUntrackedParameter<unsigned>     ("nQuads"             );
  nHeaderFrames_  = OutputSpec_.getUntrackedParameter<unsigned>     ("nHeaderFrames"       );
  nPayloadFrames_ = OutputSpec_.getUntrackedParameter<unsigned>     ("nPayloadFrames"     );
  nClearFrames_   = OutputSpec_.getUntrackedParameter<unsigned>     ("nClearFrames"      );
  nEventsPerFile_ = OutputSpec_.getParameter<unsigned int>          ("nEventsPerFile"    );
  
  n_phi_segments_ = PhiSectors_.getParameter<unsigned int>     ( "NumPhiSectors"         );
  single_segment_ = PhiSectors_.getParameter<bool>             ( "SingleSegment"         );
  phi_segment_    = PhiSectors_.getParameter<int>              ( "PhiSegment"            );
  UseStubPhi_     = PhiSectors_.getParameter<bool>             ( "UseStubPhi"            );
  UseStubPhiTrk_  = PhiSectors_.getParameter<bool>             ( "UseStubPhiTrk"         );
  AssumedPhiTrkRes_ = PhiSectors_.getParameter<double>         ( "AssumedPhiTrkRes"      );
  chosenRofPhi_   = PhiSectors_.getParameter<double>           ( "ChosenRofPhi"          );
  bendResolution_ = PhiSectors_.getParameter<double>           ( "BendResolution"        );
  dataCorrection_ = PhiSectors_.getParameter<bool>             ( "DataCorrection"        );

  eta_regions_    = EtaRegions_.getParameter<std::vector<double> >  ( "EtaRegions"            );
  single_region_  = EtaRegions_.getParameter<bool>                  ( "SingleRegion"          );
  eta_region_     = EtaRegions_.getParameter<int>                   ( "EtaRegion"            );
  chosenRofZ_     = EtaRegions_.getParameter<double>                ( "ChosenRofZ"            );

  splitting_      = DataFormats_.getParameter<int>                  ( "Splitting"             );
  segment_bits_   = DataFormats_.getParameter<int>                  ( "SegmentBits"           );
  phiS_bits_       = DataFormats_.getParameter<int>                   ( "PhiSBits"               );
   phiS_multiplier_ = DataFormats_.getParameter<int>                 ( "PhiSMultiplier"        );
  z_bits_         = DataFormats_.getParameter<int>                   ( "ZBits"                 );
  z_multiplier_ = DataFormats_.getParameter<int>                      ("ZMultiplier"          );
  rt_bits_       = DataFormats_.getParameter<int>                    ( "RtBits"               );
  rt_multiplier_ = DataFormats_.getParameter<int>                    ( "RtMultiplier"           );
  dphi_bits_       = DataFormats_.getParameter<int>                    ( "DphiBits"               );
  dphi_multiplier_ = DataFormats_.getParameter<int>                   ( "DphiMultiplier"        );
  rho_bits_       = DataFormats_.getParameter<int>                    ( "RhoBits"               );
  rho_multiplier_ = DataFormats_.getParameter<int>                    ( "RhoMultiplier"       );
  bField_ = 0.;
 
  debug_          = iConfig.getParameter<bool>                  ( "Debug"                 );

  


}

