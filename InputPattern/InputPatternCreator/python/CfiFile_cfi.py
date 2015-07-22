import FWCore.ParameterSet.Config as cms

producer = cms.EDProducer('InputPatternCreator',
	
	OutputSpec = cms.PSet(
		filename              = cms.untracked.string("Example/ttbarPU140_"), # Names of the output txt files
		nChanPerQuad          = cms.untracked.uint32(4), # Number of channels per quad (default=4)
		nQuads                = cms.untracked.uint32(18), # Number of Quads (Default = 18)
		nHeaderFrames         = cms.untracked.uint32(1), # Number of Empty header frames per each phi sector
		nPayloadFrames        = cms.untracked.uint32(288), # Number of payload frames assigned to each phi sector
		nClearFrames          = cms.untracked.uint32(6), # Number of empty frames at the end of each eta region
    nEventsPerFile        = cms.uint32(4) # Number of events to be written in a single file
    ),

	PhiSectors = cms.PSet(
    NumPhiSectors         = cms.uint32(48), # Number of phi sectors (32 or 64)
    SingleSegment         = cms.bool(True), # If True just data from a single phi sector are saved in the txt file
    PhiSegment           = cms.int32(5), # If SingleSegment=True just data this PhiSegment are saved in the txt file
		UseStubPhi         = cms.bool(True),  # Require stub phi to be consistent with track of Pt > HTArraySpec.HoughMinPt that crosses HT phi axis?
    UseStubPhiTrk      = cms.bool(True),  # Require stub phi0 (or phi65 etc.) as estimated from stub bend, to lie within HT phi axis, allowing tolerance(s) specified below?
    AssumedPhiTrkRes   = cms.double(0.5), # Tolerance in stub phi0 (or phi65) assumed to be this fraction of phi sector width. (N.B. If > 0.5, then stubs can be shared by more than 2 phi sectors). 
    ChosenRofPhi	   = cms.double(45.),
    BendResolution     = cms.double(1.05),
    DataCorrection     = cms.bool(True)
    ),

	EtaRegions = cms.PSet(
	  EtaRegions            = cms.vdouble(-2.4, -1.45, -0.61, 0.61, 1.45, 2.4), # Boundaries of eta regions defined at outer radius of tracker.
	  SingleRegion          = cms.bool(False), # If True just data from a single eta region are saved in the txt file
	  EtaRegion             = cms.int32(2), # If SingleRegion=True just data this EtaSegment are saved in the txt file
	  ChosenRofZ            = cms.double(65.) # Use z of track at this radius for assignment of tracks to eta sectors & also for one of the axes of the r-z HT. Do not set to zero!
    ),

	DataFormats = cms.PSet(
        Splitting         = cms.int32(0), # 0 Splitting over clock cycles (frames), 1 Splitting over links 
        SegmentBits			   = cms.int32(6),
    	PhiSBits               = cms.int32(12), # Number of Bits for phi
        PhiSMultiplier         = cms.int32(1000),
        ZBits                  = cms.int32(12), # Number of bits for z
        ZMultiplier            = cms.int32(7),
        RtBits                 = cms.int32(9),  # Number of bits for R65
        RtMultiplier           = cms.int32(4),
        DphiBits			   = cms.int32(6),
        DphiMultiplier         = cms.int32(10),
        RhoBits				   = cms.int32(6),
        RhoMultiplier          = cms.int32(5)
    ),

  Debug                 	  = cms.bool(True) # Print some debug statements
)
