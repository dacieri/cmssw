import FWCore.ParameterSet.Config as cms

tracktriggerPhase2Digis = cms.EDProducer(
    "L1TPhase2Producer",
    stubToken = cms.InputTag("tracktriggerPhase2Layer1Digis"),
    firmware = cms.int32(1)
)
