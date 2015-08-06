import FWCore.ParameterSet.Config as cms

tracktriggerParamsSource = cms.ESSource(
    "EmptyESSource",
    recordName = cms.string('L1TrackTriggerParamsRcd'),
    iovIsRunNotTime = cms.bool(True),
    firstValid = cms.vuint32(1)
)

#tracktriggerParams = cms.ESProducer(
#   "L1TrackTriggerParamsESProducer",)
