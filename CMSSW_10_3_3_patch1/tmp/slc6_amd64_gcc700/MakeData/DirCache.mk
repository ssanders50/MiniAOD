ALL_SUBSYSTEMS+=RecoHI
subdirs_src_RecoHI = src_RecoHI_HiJetAlgos src_RecoHI_HiTracking
ifeq ($(strip $(PyRecoEgammaEgammaPhotonProducers)),)
PyRecoEgammaEgammaPhotonProducers := self/src/RecoEgamma/EgammaPhotonProducers/python
src_RecoEgamma_EgammaPhotonProducers_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/RecoEgamma/EgammaPhotonProducers/python)
PyRecoEgammaEgammaPhotonProducers_files := $(patsubst src/RecoEgamma/EgammaPhotonProducers/python/%,%,$(wildcard $(foreach dir,src/RecoEgamma/EgammaPhotonProducers/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyRecoEgammaEgammaPhotonProducers_LOC_USE := self cmssw 
PyRecoEgammaEgammaPhotonProducers_PACKAGE := self/src/RecoEgamma/EgammaPhotonProducers/python
ALL_PRODS += PyRecoEgammaEgammaPhotonProducers
PyRecoEgammaEgammaPhotonProducers_INIT_FUNC        += $$(eval $$(call PythonProduct,PyRecoEgammaEgammaPhotonProducers,src/RecoEgamma/EgammaPhotonProducers/python,src_RecoEgamma_EgammaPhotonProducers_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyRecoEgammaEgammaPhotonProducers,src/RecoEgamma/EgammaPhotonProducers/python))
endif
ALL_COMMONRULES += src_RecoEgamma_EgammaPhotonProducers_python
src_RecoEgamma_EgammaPhotonProducers_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoEgamma_EgammaPhotonProducers_python,src/RecoEgamma/EgammaPhotonProducers/python,PYTHON))
ifeq ($(strip $(PyRecoEgammaEgammaTools)),)
PyRecoEgammaEgammaTools := self/src/RecoEgamma/EgammaTools/python
src_RecoEgamma_EgammaTools_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/RecoEgamma/EgammaTools/python)
PyRecoEgammaEgammaTools_files := $(patsubst src/RecoEgamma/EgammaTools/python/%,%,$(wildcard $(foreach dir,src/RecoEgamma/EgammaTools/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyRecoEgammaEgammaTools_LOC_USE := self cmssw 
PyRecoEgammaEgammaTools_PACKAGE := self/src/RecoEgamma/EgammaTools/python
ALL_PRODS += PyRecoEgammaEgammaTools
PyRecoEgammaEgammaTools_INIT_FUNC        += $$(eval $$(call PythonProduct,PyRecoEgammaEgammaTools,src/RecoEgamma/EgammaTools/python,src_RecoEgamma_EgammaTools_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyRecoEgammaEgammaTools,src/RecoEgamma/EgammaTools/python))
endif
ALL_COMMONRULES += src_RecoEgamma_EgammaTools_python
src_RecoEgamma_EgammaTools_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoEgamma_EgammaTools_python,src/RecoEgamma/EgammaTools/python,PYTHON))
ALL_SUBSYSTEMS+=RecoEgamma
subdirs_src_RecoEgamma = src_RecoEgamma_EgammaTools src_RecoEgamma_EgammaPhotonProducers
ALL_PACKAGES += PhysicsTools/PatAlgos
subdirs_src_PhysicsTools_PatAlgos := src_PhysicsTools_PatAlgos_plugins src_PhysicsTools_PatAlgos_scripts src_PhysicsTools_PatAlgos_python src_PhysicsTools_PatAlgos_test src_PhysicsTools_PatAlgos_interface src_PhysicsTools_PatAlgos_src
ifeq ($(strip $(RecoEGammaGBRWrapperMaker)),)
RecoEGammaGBRWrapperMaker := self/src/RecoEgamma/EgammaTools/test
RecoEGammaGBRWrapperMaker_files := $(patsubst src/RecoEgamma/EgammaTools/test/%,%,$(foreach file,GBRWrapperMaker.cc,$(eval xfile:=$(wildcard src/RecoEgamma/EgammaTools/test/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/RecoEgamma/EgammaTools/test/$(file). Please fix src/RecoEgamma/EgammaTools/test/BuildFile.))))
RecoEGammaGBRWrapperMaker_BuildFile    := $(WORKINGDIR)/cache/bf/src/RecoEgamma/EgammaTools/test/BuildFile
RecoEGammaGBRWrapperMaker_LOC_USE := self cmssw FWCore/Framework PhysicsTools/MVAComputer PhysicsTools/MVATrainer CondCore/PluginSystem CondCore/DBOutputService CondFormats/DataRecord CondFormats/EgammaObjects DataFormats/EgammaCandidates RecoEgamma/EgammaTools
RecoEGammaGBRWrapperMaker_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,RecoEGammaGBRWrapperMaker,RecoEGammaGBRWrapperMaker,$(SCRAMSTORENAME_LIB),src/RecoEgamma/EgammaTools/test))
RecoEGammaGBRWrapperMaker_PACKAGE := self/src/RecoEgamma/EgammaTools/test
ALL_PRODS += RecoEGammaGBRWrapperMaker
RecoEGammaGBRWrapperMaker_INIT_FUNC        += $$(eval $$(call Library,RecoEGammaGBRWrapperMaker,src/RecoEgamma/EgammaTools/test,src_RecoEgamma_EgammaTools_test,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
RecoEGammaGBRWrapperMaker_CLASS := TEST_LIBRARY
else
$(eval $(call MultipleWarningMsg,RecoEGammaGBRWrapperMaker,src/RecoEgamma/EgammaTools/test))
endif
ALL_COMMONRULES += src_RecoEgamma_EgammaTools_test
src_RecoEgamma_EgammaTools_test_parent := RecoEgamma/EgammaTools
src_RecoEgamma_EgammaTools_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoEgamma_EgammaTools_test,src/RecoEgamma/EgammaTools/test,TEST))
ALL_COMMONRULES += src_HeavyIonsAnalysis_Configuration_test
src_HeavyIonsAnalysis_Configuration_test_parent := HeavyIonsAnalysis/Configuration
src_HeavyIonsAnalysis_Configuration_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_HeavyIonsAnalysis_Configuration_test,src/HeavyIonsAnalysis/Configuration/test,TEST))
src_PhysicsTools_PatAlgos_scripts_files := $(filter-out \#% %\#,$(notdir $(wildcard $(foreach dir,$(LOCALTOP)/src/PhysicsTools/PatAlgos/scripts,$(dir)/*))))
$(eval $(call Src2StoreCopy,src_PhysicsTools_PatAlgos_scripts,src/PhysicsTools/PatAlgos/scripts,$(SCRAMSTORENAME_BIN),*))
ifeq ($(strip $(PyPhysicsToolsPatAlgos)),)
PyPhysicsToolsPatAlgos := self/src/PhysicsTools/PatAlgos/python
src_PhysicsTools_PatAlgos_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/PhysicsTools/PatAlgos/python)
PyPhysicsToolsPatAlgos_files := $(patsubst src/PhysicsTools/PatAlgos/python/%,%,$(wildcard $(foreach dir,src/PhysicsTools/PatAlgos/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyPhysicsToolsPatAlgos_LOC_USE := self cmssw 
PyPhysicsToolsPatAlgos_PACKAGE := self/src/PhysicsTools/PatAlgos/python
ALL_PRODS += PyPhysicsToolsPatAlgos
PyPhysicsToolsPatAlgos_INIT_FUNC        += $$(eval $$(call PythonProduct,PyPhysicsToolsPatAlgos,src/PhysicsTools/PatAlgos/python,src_PhysicsTools_PatAlgos_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyPhysicsToolsPatAlgos,src/PhysicsTools/PatAlgos/python))
endif
ALL_COMMONRULES += src_PhysicsTools_PatAlgos_python
src_PhysicsTools_PatAlgos_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PhysicsTools_PatAlgos_python,src/PhysicsTools/PatAlgos/python,PYTHON))
ALL_PACKAGES += RecoEgamma/EgammaTools
subdirs_src_RecoEgamma_EgammaTools := src_RecoEgamma_EgammaTools_plugins src_RecoEgamma_EgammaTools_python src_RecoEgamma_EgammaTools_test src_RecoEgamma_EgammaTools_interface src_RecoEgamma_EgammaTools_src
ifeq ($(strip $(PyRecoHIHiJetAlgos)),)
PyRecoHIHiJetAlgos := self/src/RecoHI/HiJetAlgos/python
src_RecoHI_HiJetAlgos_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/RecoHI/HiJetAlgos/python)
PyRecoHIHiJetAlgos_files := $(patsubst src/RecoHI/HiJetAlgos/python/%,%,$(wildcard $(foreach dir,src/RecoHI/HiJetAlgos/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyRecoHIHiJetAlgos_LOC_USE := self cmssw 
PyRecoHIHiJetAlgos_PACKAGE := self/src/RecoHI/HiJetAlgos/python
ALL_PRODS += PyRecoHIHiJetAlgos
PyRecoHIHiJetAlgos_INIT_FUNC        += $$(eval $$(call PythonProduct,PyRecoHIHiJetAlgos,src/RecoHI/HiJetAlgos/python,src_RecoHI_HiJetAlgos_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyRecoHIHiJetAlgos,src/RecoHI/HiJetAlgos/python))
endif
ALL_COMMONRULES += src_RecoHI_HiJetAlgos_python
src_RecoHI_HiJetAlgos_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoHI_HiJetAlgos_python,src/RecoHI/HiJetAlgos/python,PYTHON))
ALL_COMMONRULES += src_RecoHI_HiJetAlgos_test
src_RecoHI_HiJetAlgos_test_parent := RecoHI/HiJetAlgos
src_RecoHI_HiJetAlgos_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoHI_HiJetAlgos_test,src/RecoHI/HiJetAlgos/test,TEST))
ALL_PACKAGES += RecoHI/HiJetAlgos
subdirs_src_RecoHI_HiJetAlgos := src_RecoHI_HiJetAlgos_plugins src_RecoHI_HiJetAlgos_python src_RecoHI_HiJetAlgos_test src_RecoHI_HiJetAlgos_src
ALL_SUBSYSTEMS+=RecoJets
subdirs_src_RecoJets = src_RecoJets_Configuration src_RecoJets_JetProducers
ALL_PACKAGES += RecoJets/JetProducers
subdirs_src_RecoJets_JetProducers := src_RecoJets_JetProducers_plugins src_RecoJets_JetProducers_doc src_RecoJets_JetProducers_python src_RecoJets_JetProducers_test src_RecoJets_JetProducers_src src_RecoJets_JetProducers_data src_RecoJets_JetProducers_validation
ifeq ($(strip $(PyHeavyIonsAnalysisConfiguration)),)
PyHeavyIonsAnalysisConfiguration := self/src/HeavyIonsAnalysis/Configuration/python
src_HeavyIonsAnalysis_Configuration_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/HeavyIonsAnalysis/Configuration/python)
PyHeavyIonsAnalysisConfiguration_files := $(patsubst src/HeavyIonsAnalysis/Configuration/python/%,%,$(wildcard $(foreach dir,src/HeavyIonsAnalysis/Configuration/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyHeavyIonsAnalysisConfiguration_LOC_USE := self cmssw 
PyHeavyIonsAnalysisConfiguration_PACKAGE := self/src/HeavyIonsAnalysis/Configuration/python
ALL_PRODS += PyHeavyIonsAnalysisConfiguration
PyHeavyIonsAnalysisConfiguration_INIT_FUNC        += $$(eval $$(call PythonProduct,PyHeavyIonsAnalysisConfiguration,src/HeavyIonsAnalysis/Configuration/python,src_HeavyIonsAnalysis_Configuration_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyHeavyIonsAnalysisConfiguration,src/HeavyIonsAnalysis/Configuration/python))
endif
ALL_COMMONRULES += src_HeavyIonsAnalysis_Configuration_python
src_HeavyIonsAnalysis_Configuration_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_HeavyIonsAnalysis_Configuration_python,src/HeavyIonsAnalysis/Configuration/python,PYTHON))
ALL_PACKAGES += RecoJets/Configuration
subdirs_src_RecoJets_Configuration := src_RecoJets_Configuration_doc src_RecoJets_Configuration_python
ifeq ($(strip $(runtestPhysicsToolsPatAlgos)),)
runtestPhysicsToolsPatAlgos := self/src/PhysicsTools/PatAlgos/test
runtestPhysicsToolsPatAlgos_files := $(patsubst src/PhysicsTools/PatAlgos/test/%,%,$(foreach file,runtestPhysicsToolsPatAlgos.cpp,$(eval xfile:=$(wildcard src/PhysicsTools/PatAlgos/test/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/PatAlgos/test/$(file). Please fix src/PhysicsTools/PatAlgos/test/BuildFile.))))
runtestPhysicsToolsPatAlgos_TEST_RUNNER_CMD :=  runtestPhysicsToolsPatAlgos  /bin/bash PhysicsTools/PatAlgos/test runtests.sh
runtestPhysicsToolsPatAlgos_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/PatAlgos/test/BuildFile
runtestPhysicsToolsPatAlgos_LOC_USE := self cmssw FWCore/Utilities
runtestPhysicsToolsPatAlgos_PACKAGE := self/src/PhysicsTools/PatAlgos/test
ALL_PRODS += runtestPhysicsToolsPatAlgos
runtestPhysicsToolsPatAlgos_INIT_FUNC        += $$(eval $$(call Binary,runtestPhysicsToolsPatAlgos,src/PhysicsTools/PatAlgos/test,src_PhysicsTools_PatAlgos_test,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_TEST),test,$(SCRAMSTORENAME_LOGS)))
runtestPhysicsToolsPatAlgos_CLASS := TEST
else
$(eval $(call MultipleWarningMsg,runtestPhysicsToolsPatAlgos,src/PhysicsTools/PatAlgos/test))
endif
ifeq ($(strip $(PhysicsToolsPatAlgos_testAnalyzers)),)
PhysicsToolsPatAlgos_testAnalyzers := self/src/PhysicsTools/PatAlgos/test
PhysicsToolsPatAlgos_testAnalyzers_files := $(patsubst src/PhysicsTools/PatAlgos/test/%,%,$(foreach file,private/*.cc,$(eval xfile:=$(wildcard src/PhysicsTools/PatAlgos/test/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PhysicsTools/PatAlgos/test/$(file). Please fix src/PhysicsTools/PatAlgos/test/BuildFile.))))
PhysicsToolsPatAlgos_testAnalyzers_BuildFile    := $(WORKINGDIR)/cache/bf/src/PhysicsTools/PatAlgos/test/BuildFile
PhysicsToolsPatAlgos_testAnalyzers_LOC_USE := self cmssw FWCore/Framework FWCore/ParameterSet DataFormats/BTauReco PhysicsTools/PatUtils DataFormats/PatCandidates root
PhysicsToolsPatAlgos_testAnalyzers_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,PhysicsToolsPatAlgos_testAnalyzers,PhysicsToolsPatAlgos_testAnalyzers,$(SCRAMSTORENAME_LIB),src/PhysicsTools/PatAlgos/test))
PhysicsToolsPatAlgos_testAnalyzers_PACKAGE := self/src/PhysicsTools/PatAlgos/test
ALL_PRODS += PhysicsToolsPatAlgos_testAnalyzers
PhysicsToolsPatAlgos_testAnalyzers_INIT_FUNC        += $$(eval $$(call Library,PhysicsToolsPatAlgos_testAnalyzers,src/PhysicsTools/PatAlgos/test,src_PhysicsTools_PatAlgos_test,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
PhysicsToolsPatAlgos_testAnalyzers_CLASS := TEST_LIBRARY
else
$(eval $(call MultipleWarningMsg,PhysicsToolsPatAlgos_testAnalyzers,src/PhysicsTools/PatAlgos/test))
endif
ALL_COMMONRULES += src_PhysicsTools_PatAlgos_test
src_PhysicsTools_PatAlgos_test_parent := PhysicsTools/PatAlgos
src_PhysicsTools_PatAlgos_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PhysicsTools_PatAlgos_test,src/PhysicsTools/PatAlgos/test,TEST))
ALL_PACKAGES += HeavyIonsAnalysis/Configuration
subdirs_src_HeavyIonsAnalysis_Configuration := src_HeavyIonsAnalysis_Configuration_python src_HeavyIonsAnalysis_Configuration_test
ALL_SUBSYSTEMS+=PhysicsTools
subdirs_src_PhysicsTools = src_PhysicsTools_PatAlgos
ALL_COMMONRULES += src_RecoJets_JetProducers_test
src_RecoJets_JetProducers_test_parent := RecoJets/JetProducers
src_RecoJets_JetProducers_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoJets_JetProducers_test,src/RecoJets/JetProducers/test,TEST))
ALL_PACKAGES += RecoEgamma/EgammaPhotonProducers
subdirs_src_RecoEgamma_EgammaPhotonProducers := src_RecoEgamma_EgammaPhotonProducers_python src_RecoEgamma_EgammaPhotonProducers_src
ifeq ($(strip $(PyRecoJetsConfiguration)),)
PyRecoJetsConfiguration := self/src/RecoJets/Configuration/python
src_RecoJets_Configuration_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/RecoJets/Configuration/python)
PyRecoJetsConfiguration_files := $(patsubst src/RecoJets/Configuration/python/%,%,$(wildcard $(foreach dir,src/RecoJets/Configuration/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyRecoJetsConfiguration_LOC_USE := self cmssw 
PyRecoJetsConfiguration_PACKAGE := self/src/RecoJets/Configuration/python
ALL_PRODS += PyRecoJetsConfiguration
PyRecoJetsConfiguration_INIT_FUNC        += $$(eval $$(call PythonProduct,PyRecoJetsConfiguration,src/RecoJets/Configuration/python,src_RecoJets_Configuration_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyRecoJetsConfiguration,src/RecoJets/Configuration/python))
endif
ALL_COMMONRULES += src_RecoJets_Configuration_python
src_RecoJets_Configuration_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoJets_Configuration_python,src/RecoJets/Configuration/python,PYTHON))
ALL_SUBSYSTEMS+=HeavyIonsAnalysis
subdirs_src_HeavyIonsAnalysis = src_HeavyIonsAnalysis_Configuration
ifeq ($(strip $(PyRecoHIHiTracking)),)
PyRecoHIHiTracking := self/src/RecoHI/HiTracking/python
src_RecoHI_HiTracking_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/RecoHI/HiTracking/python)
PyRecoHIHiTracking_files := $(patsubst src/RecoHI/HiTracking/python/%,%,$(wildcard $(foreach dir,src/RecoHI/HiTracking/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyRecoHIHiTracking_LOC_USE := self cmssw 
PyRecoHIHiTracking_PACKAGE := self/src/RecoHI/HiTracking/python
ALL_PRODS += PyRecoHIHiTracking
PyRecoHIHiTracking_INIT_FUNC        += $$(eval $$(call PythonProduct,PyRecoHIHiTracking,src/RecoHI/HiTracking/python,src_RecoHI_HiTracking_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyRecoHIHiTracking,src/RecoHI/HiTracking/python))
endif
ALL_COMMONRULES += src_RecoHI_HiTracking_python
src_RecoHI_HiTracking_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoHI_HiTracking_python,src/RecoHI/HiTracking/python,PYTHON))
ifeq ($(strip $(RecoHIHiTrackingTest)),)
RecoHIHiTrackingTest := self/src/RecoHI/HiTracking/test
RecoHIHiTrackingTest_files := $(patsubst src/RecoHI/HiTracking/test/%,%,$(foreach file,*.cc,$(eval xfile:=$(wildcard src/RecoHI/HiTracking/test/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/RecoHI/HiTracking/test/$(file). Please fix src/RecoHI/HiTracking/test/BuildFile.))))
RecoHIHiTrackingTest_BuildFile    := $(WORKINGDIR)/cache/bf/src/RecoHI/HiTracking/test/BuildFile
RecoHIHiTrackingTest_LOC_USE := self cmssw root RecoHI/HiTracking RecoPixelVertexing/PixelLowPtUtilities CommonTools/UtilAlgos
RecoHIHiTrackingTest_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,RecoHIHiTrackingTest,RecoHIHiTrackingTest,$(SCRAMSTORENAME_LIB),src/RecoHI/HiTracking/test))
RecoHIHiTrackingTest_PACKAGE := self/src/RecoHI/HiTracking/test
ALL_PRODS += RecoHIHiTrackingTest
RecoHIHiTrackingTest_INIT_FUNC        += $$(eval $$(call Library,RecoHIHiTrackingTest,src/RecoHI/HiTracking/test,src_RecoHI_HiTracking_test,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS)))
RecoHIHiTrackingTest_CLASS := TEST_LIBRARY
else
$(eval $(call MultipleWarningMsg,RecoHIHiTrackingTest,src/RecoHI/HiTracking/test))
endif
ALL_COMMONRULES += src_RecoHI_HiTracking_test
src_RecoHI_HiTracking_test_parent := RecoHI/HiTracking
src_RecoHI_HiTracking_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoHI_HiTracking_test,src/RecoHI/HiTracking/test,TEST))
ALL_PACKAGES += RecoHI/HiTracking
subdirs_src_RecoHI_HiTracking := src_RecoHI_HiTracking_plugins src_RecoHI_HiTracking_python src_RecoHI_HiTracking_test src_RecoHI_HiTracking_src
ifeq ($(strip $(PyRecoJetsJetProducers)),)
PyRecoJetsJetProducers := self/src/RecoJets/JetProducers/python
src_RecoJets_JetProducers_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/RecoJets/JetProducers/python)
PyRecoJetsJetProducers_files := $(patsubst src/RecoJets/JetProducers/python/%,%,$(wildcard $(foreach dir,src/RecoJets/JetProducers/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyRecoJetsJetProducers_LOC_USE := self cmssw 
PyRecoJetsJetProducers_PACKAGE := self/src/RecoJets/JetProducers/python
ALL_PRODS += PyRecoJetsJetProducers
PyRecoJetsJetProducers_INIT_FUNC        += $$(eval $$(call PythonProduct,PyRecoJetsJetProducers,src/RecoJets/JetProducers/python,src_RecoJets_JetProducers_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyRecoJetsJetProducers,src/RecoJets/JetProducers/python))
endif
ALL_COMMONRULES += src_RecoJets_JetProducers_python
src_RecoJets_JetProducers_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoJets_JetProducers_python,src/RecoJets/JetProducers/python,PYTHON))
