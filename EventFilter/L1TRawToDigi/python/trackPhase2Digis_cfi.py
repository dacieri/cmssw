import FWCore.ParameterSet.Config as cms

trackPhase2Digis = cms.EDProducer(
    "L1TRawToDigi",
    Setup           = cms.string("phase2::TrackSetup"),
    InputLabel      = cms.InputTag("rawDataCollector"),
    FedIds          = cms.vint32( 1409 ),
    #FWId            = cms.uint32(2),
    lenSlinkHeader  = cms.untracked.int32(8),
    lenSlinkTrailer = cms.untracked.int32(8),
    lenAMCHeader    = cms.untracked.int32(8),
    lenAMCTrailer   = cms.untracked.int32(0),
    lenAMC13Header  = cms.untracked.int32(8),
    lenAMC13Trailer = cms.untracked.int32(8)
)
