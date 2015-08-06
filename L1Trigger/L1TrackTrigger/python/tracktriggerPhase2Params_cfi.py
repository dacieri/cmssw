import FWCore.ParameterSet.Config as cms

from L1Trigger.L1TrackTrigger.tracktriggerParams_cfi import tracktriggerParamsSource
import L1Trigger.L1TrackTrigger.tracktriggerParams_cfi
tracktriggerPhase2Params = L1Trigger.L1TrackTrigger.tracktriggerParams_cfi.tracktriggerParams.clone()


#Array axis m
tracktriggerPhase2Params.MAxisMin=cms.vint32(-480, -440, -400, -360, -320, -280, -240, -200, 
-160, -120, -80, -40, 0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480)

tracktriggerPhase2Params.MAxisMax=cms.vint32(-480, -440, -400, -360, -320, -280, -240, -200, 
-160, -120, -80, -40, 0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480)

tracktriggerPhase2Params.MAxisAv=cms.vint32(-480, -440, -400, -360, -320, -280, -240, -200, 
-160, -120, -80, -40, 0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480)

#Array axis c
tracktriggerPhase2Params.CAxisMin=cms.vint32(0, 80000, 160000, 240000, 320000, 400000, 480000, 
560000, 640000, 720000, 800000, 880000, 960000, 1040000, 1120000, 1200000, 1280000,
1360000, 1440000, 1520000, 1600000, 1680000, 1760000, 1840000, 1920000)

tracktriggerPhase2Params.CAxisMax=cms.vint32(82000, 162000, 242000, 322000, 402000, 482000, 
562000, 642000, 722000, 802000, 962000, 1042000, 1122000, 1202000, 1282000, 1362000,
1442000, 1522000, 1602000, 1682000, 1762000, 1842000, 1922000, 2000000)

tracktriggerPhase2Params.CAxisAv=cms.vint32(82000, 162000, 242000, 322000, 402000, 482000, 
562000, 642000, 722000, 802000, 962000, 1042000, 1122000, 1202000, 1282000, 1362000,
1442000, 1522000, 1602000, 1682000, 1762000, 1842000, 1922000, 2000000)

#number of boards in parallel
tracktriggerPhase2Params.NBoards=cms.int(2)

#Radial origin for Hough transform (cm)
tracktriggerPhase2Params.T=cms.int(45)
