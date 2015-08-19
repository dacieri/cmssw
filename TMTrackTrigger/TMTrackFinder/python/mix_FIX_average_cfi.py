import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils
# configuration to model pileup for initial physics phase
from SimGeneral.MixingModule.mixObjects_cfi import theMixObjects
from SimGeneral.MixingModule.mixPoolSource_cfi import *
from SimGeneral.MixingModule.digitizers_cfi import *
from random import *

seed = randint(0,68)
string = '../TMTrackTrigger/TMTrackFinder/python/minbias'
string +=`seed`
string +='.txt'
print string

list = FileUtils.loadListFromFile('../minbias_new.txt')
readFiles = cms.untracked.vstring(*list)
secFiles = cms.untracked.vstring()

mix = cms.EDProducer("MixingModule",
    digitizers = cms.PSet(theDigitizers),
    LabelPlayback = cms.string(''),
    maxBunch = cms.int32(3),
    minBunch = cms.int32(-12), ## in terms of 25 nsec

    bunchspace = cms.int32(25), ##ns
    mixProdStep1 = cms.bool(False),
    mixProdStep2 = cms.bool(False),

    playback = cms.untracked.bool(False),
    useCurrentProcessOnly = cms.bool(False),
    input = cms.SecSource("PoolSource",
        nbPileupEvents = cms.PSet(
            averageNumber = cms.double(140.0)
            ),
        seed = cms.int32(randint(1,5000)),
        type = cms.string('poisson'),
        sequential = cms.untracked.bool(False),
        fileNames = readFiles,
        secondaryFileNames = secFiles
        ),

    mixObjects = cms.PSet(theMixObjects)
)

            #            'file:minbias.root',,
#'file:minbias1.root',
#'file:file3.root',,
#'file:fileN.root',

secFiles.extend([
        ])


