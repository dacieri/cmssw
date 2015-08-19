from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'PU140'
config.General.workArea = 'TTbar_StubFixed_Davide'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step2_PU.py'
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset ='/ttbar/dcieri-ttbar_SIM-130075366148575c102f0d64fd3ac8f7/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
#config.Data.totalUnits = 10
config.Data.outLFNDirBase = '/store/user/dcieri/ttbarPU140_stubfix_Davide' # or '/store/group/<subdir>'
config.Data.publication = True
config.Data.publishDataName = 'ttbarPU140_stubfix_Davide'
config.Data.ignoreLocality = True


config.Site.storageSite = 'T2_UK_SGrid_RALPP'
config.Site.whitelist = ['T3_UK_London_QMUL','T3_UK_London_RHUL','T3_UK_London_UCL','T3_UK_SGrid_Oxford','T3_UK_ScotGrid_ECDF','T3_UK_ScotGrid_GLA', 'T2_UK_London_Brunel','T2_UK_London_IC','T2_UK_SGrid_Bristol','T2_UK_SGrid_RALPP']

