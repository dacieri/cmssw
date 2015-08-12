# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: SingleElectronPt10_cfi.py -s GEN,SIM,DIGI,L1 
#--pileup=NoPileUp --geometry DB --conditions=auto:startup -n 1 --no_exec
import FWCore.ParameterSet.Config as cms


# options
import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing('analysis')
options.register('skipEvents',
                 0,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "Number of events to skip")
options.register('dump',
                 False,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool,
                 "Print RAW data")
#options.register('doLayer1',
#                 True,
#                 VarParsing.VarParsing.multiplicity.singleton,
#                 VarParsing.VarParsing.varType.bool,
#                 "Run layer 1 module")
#options.register('doLayer2',
#                 True,
#                 VarParsing.VarParsing.multiplicity.singleton,
#                 VarParsing.VarParsing.varType.bool,
#                 "Run layer 2 module")

                 
options.parseArguments()

if (options.maxEvents == -1):
    options.maxEvents = 1


process = cms.Process('L1Emulator')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

# Input source
inFile = 'file:../data/input/TTBar_PU140_hwEDM_numEvent100.root'
process.source = cms.Source("PoolSource",
    fileNames=cms.untracked.vstring(inFile),
    skipEvents=cms.untracked.uint32(options.skipEvents)
)

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)


# Output definition
process.output = cms.OutputModule(
    "PoolOutputModule",
    outputCommands = cms.untracked.vstring("keep *"),
    fileName = cms.untracked.string('../data/output/PU140_numEvent100_simEDM.root')
)

# Additional output definition
# TTree output file
process.load("CommonTools.UtilAlgos.TFileService_cfi")
process.TFileService.fileName = cms.string('../data/output/PU140_numEvent100_simEDM.root')

# enable debug message logging for our modules
process.MessageLogger = cms.Service(
    "MessageLogger",
    threshold  = cms.untracked.string('DEBUG'),
    categories = cms.untracked.vstring('L1T'),
    debugModules = cms.untracked.vstring('*')
#        'mp7BufferDumpToRaw',
#        'l1tDigis',
#        'caloStage1Digis'
#    )
)


# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:startup', '')


# emulator
#from L1Trigger.L1TCalorimeter.caloStage2Layer1Digis_cfi import caloStage2Layer1Digis
#process.simCaloStage2Layer1Digis = caloStage2Layer1Digis.clone()

#from L1Trigger.L1TrackTrigger.tracktriggerPhase2Digis_cfi import tracktriggerPhase2Digis
#process.simTrackTriggerPhase2Digis = tracktriggerPhase2Digis.clone()
#process.simTrackTriggerStage2Digis.stubToken = cms.InputTag("simTrackTriggerPhase2Layer1Digis")

# emulator ES
#process.load('L1Trigger.L1TrackTrigger.tracktriggerPhase2Params_cfi')

# histograms
process.load('L1Trigger.L1TrackTrigger.l1tPhase2TrackTriggerAnalyzer_cfi')
process.l1tPhase2TrackTriggerAnalyzer.stubToken = cms.InputTag("None")

# Path and EndPath definitions
process.path = cms.Path(
   # process.simTrackTriggerPhase2Layer1Digis
   # +process.simTrackTriggerPhase2Digis
    process.l1tPhase2TrackTriggerAnalyzer
)

#if (not options.doLayer1):
#    process.path.remove(process.simTrackTriggerPhase2Layer1Digis)
#    process.simTrackTriggerPhase2Digis.stubToken = cms.InputTag("tracktriggerPhase2Digis")

#if (not options.doLayer2):
 #   process.path.remove(process.simTrackTriggerPhase2Digis)


#if (not options.doMP):
#    process.path.remove(process.stage2MPRaw)

#if (not options.-doDemux):
#    process.path.remove(process.stage2DemuxRaw)

process.out = cms.EndPath(
    process.output
)

