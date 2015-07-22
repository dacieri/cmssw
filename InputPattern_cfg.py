import FWCore.ParameterSet.Config as cms

process = cms.Process("OWNPARTICLES")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.Geometry.GeometryExtended2023Pixel_cff')
process.load('Configuration.Geometry.GeometryExtended2023PixelReco_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Geometry.TrackerGeometryBuilder.StackedTrackerGeometry_cfi')

process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(4) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/user/dcieri/ttbarPU140_newbias/ttbar/ttbarPU140_newbias/150324_152914/0000/step2_1.root'
#        '/store/user/dcieri/DimuonsPt10_PU0_DIGI/dcieri/Muons/DimuonsPt10_PU0_DIGI/d2f69f653926a2b94fec506481bcf3c9/step2_100_1_hxJ.root'
    )
)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('myOutputFile.root'),
    outputCommands = cms.untracked.vstring('drop *',
     	"keep *_producer_*_*")
)

process.load('InputPattern.InputPatternCreator.InputPatter_cff')

process.p = cms.Path(process.producer)
process.e = cms.EndPath(process.out)
