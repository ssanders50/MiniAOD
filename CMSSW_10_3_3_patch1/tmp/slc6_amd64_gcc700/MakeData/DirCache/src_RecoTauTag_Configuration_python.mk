ifeq ($(strip $(PyRecoTauTagConfiguration)),)
PyRecoTauTagConfiguration := self/src/RecoTauTag/Configuration/python
src_RecoTauTag_Configuration_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/RecoTauTag/Configuration/python)
PyRecoTauTagConfiguration_files := $(patsubst src/RecoTauTag/Configuration/python/%,%,$(wildcard $(foreach dir,src/RecoTauTag/Configuration/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyRecoTauTagConfiguration_LOC_USE := self cmssw 
PyRecoTauTagConfiguration_PACKAGE := self/src/RecoTauTag/Configuration/python
ALL_PRODS += PyRecoTauTagConfiguration
PyRecoTauTagConfiguration_INIT_FUNC        += $$(eval $$(call PythonProduct,PyRecoTauTagConfiguration,src/RecoTauTag/Configuration/python,src_RecoTauTag_Configuration_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyRecoTauTagConfiguration,src/RecoTauTag/Configuration/python))
endif
ALL_COMMONRULES += src_RecoTauTag_Configuration_python
src_RecoTauTag_Configuration_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoTauTag_Configuration_python,src/RecoTauTag/Configuration/python,PYTHON))
