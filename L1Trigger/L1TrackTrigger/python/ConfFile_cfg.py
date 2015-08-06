import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:../data/PU140_numEvent100.root'
    )
)

process.demo = cms.EDAnalyzer('L1TPhase2TrackTriggerAnalyzer'
)


process.p = cms.Path(process.demo)
