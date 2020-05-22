from WMCore.Configuration import Configuration
config = Configuration()
from CRABClient.UserUtilities import getUsernameFromSiteDB
config.section_('General')
config.General.transferOutputs = True
config.General.transferLogs = True
config.section_('JobType')
config.JobType.outputFiles = ['check.root']
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/home/sanders/PbPb_2018_default/CheckEP/checkep_cfg.py'
config.JobType.maxJobRuntimeMin = 2500
config.section_('Data')
config.Data.allowNonValidInputDataset = True
config.Data.inputDataset = '/HIMinimumBias0/HIRun2018A-04Apr2019-v1/AOD'
config.Data.unitsPerJob = 160
config.Data.publication = False
config.Data.splitting = 'LumiBased'
config.section_('User')
config.section_('Site')
config.Site.storageSite = 'T2_US_Vanderbilt'

config.Data.runRange = '326381-327999'
config.General.requestName = 'PbPb2018_check_MB0'
config.Data.outLFNDirBase = '/store/user/ssanders/PbPb2018_check_MB0'
config.Data.lumiMask = 'Cert_326381-327564_HI_PromptReco_Collisions18_JSON.txt'
config.JobType.inputFiles=['Cert_326381-327564_HI_PromptReco_Collisions18_JSON.txt','HeavyIonRPRcd_PbPb2018_offline.db']
config.JobType.pyCfgParams = ['noprint','lumifile=Cert_326381-327564_HI_PromptReco_Collisions18_JSON.txt','dbfile=HeavyIonRPRcd_PbPb2018_offline.db']
config.JobType.allowUndistributedCMSSW = True
if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print hte.headers

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################
submit(config)
