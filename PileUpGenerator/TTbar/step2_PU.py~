# Auto generated configuration file
# using:
# Revision: 1.20
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v
# with command line options: step2 --conditions auto:upgradePLS3 -n 10 --eventcontent FEVTDEBUGHLT -s DIGI:pdigi_valid,L1,DIGI2RAW --datatier GEN-SIM-DIGI-RAW --customise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2023 --geometry Extended2023,Extended2023Reco --magField 38T_PostLS1 --filein file:step1.root --fileout file:step2.root
import FWCore.ParameterSet.Config as cms

process = cms.Process('DIGI')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometryExtended2023PixelReco_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.L1TrackTrigger_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.load('TMTrackTrigger.TMTrackFinder.mix_FIX_average_cfi')

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(5)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring('file:step1.root')
)

#process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
#        mix = cms.PSet(
#            initialSeed = cms.untracked.uint32(231321),
#            engineName = cms.untracked.string('HepJamesRandom')
#           )
#)

process.options = cms.untracked.PSet(
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.20 $'),
    annotation = cms.untracked.string('step2 nevts:10'),
    name = cms.untracked.string('Applications')
)

# Output definition

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    fileName = cms.untracked.string('file:step2.root')
)

process.FEVTDEBUGHLToutput.outputCommands.append('keep *_TTClustersFromPixelDigis_*_*')
process.FEVTDEBUGHLToutput.outputCommands.append('keep *_TTStubsFromPixelDigis_*_*')

process.FEVTDEBUGHLToutput.outputCommands.append('keep *_TTTracksFromPixelDigis_*_*')

process.FEVTDEBUGHLToutput.outputCommands.append('keep *_TTClusterAssociatorFromPixelDigis_*_*')

process.FEVTDEBUGHLToutput.outputCommands.append('keep *_TTStubAssociatorFromPixelDigis_*_*')

process.FEVTDEBUGHLToutput.outputCommands.append('keep *_TTTrackAssociatorFromPixelDigis_*_*')
process.FEVTDEBUGHLToutput.outputCommands.append('keep *_simSiPixelDigis_*_*')
process.FEVTDEBUGHLToutput.outputCommands.append('keep *_*_MergedTrackTruth_*')


# Additional output definition

# Other statements
process.mix.digitizers = cms.PSet(process.theDigitizersValid)
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:upgradePLS3', '')


process.mix.digitizers.mergedtruth.select.signalOnlyTP = cms.bool(False)



# Path and EndPath definitions
process.digitisation_step = cms.Path(process.pdigi_valid)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.L1TrackTrigger_step = cms.Path(process.L1TrackTrigger)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

# Schedule definition
process.schedule = cms.Schedule(process.digitisation_step,process.L1simulation_step,process.L1TrackTrigger_step,process.digi2raw_step,process.endjob_step,process.FEVTDEBUGHLToutput_step)

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.combinedCustoms
from SLHCUpgradeSimulations.Configuration.combinedCustoms import cust_2023Pixel

#call to customisation function cust_2023 imported from SLHCUpgradeSimulations.Configuration.combinedCustoms
process = cust_2023Pixel(process)

# End of customisation functions
