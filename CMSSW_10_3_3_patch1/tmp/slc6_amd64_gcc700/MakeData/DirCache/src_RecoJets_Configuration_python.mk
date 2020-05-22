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
