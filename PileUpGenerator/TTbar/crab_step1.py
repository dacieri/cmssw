from CRABClient.client_utilities import getBasicConfig
config = getBasicConfig()

config.General.requestName = 'SIM'
config.General.workArea = 'ttbar'

config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'TTbar_Tauola_14TeV_cfi_GEN_SIM.py'
config.JobType.allowNonProductionCMSSW = True

config.Data.primaryDataset = 'ttbar'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 10
NJOBS = 500  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFN = '/store/user/dcieri/ttbar_SIM' # or '/store/group/<subdir>'
config.Data.publication = True
config.Data.publishDataName = 'ttbar_SIM'

config.Site.storageSite = 'T2_UK_SGrid_RALPP'
