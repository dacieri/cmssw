import FWCore.ParameterSet.Config as cms

l1tPhase2TrackTriggerAnalyzer = cms.EDAnalyzer('L1TPhase2TrackTriggerAnalyzer',
    stubToken = cms.InputTag("tracktriggerPhase2Digis")

)
