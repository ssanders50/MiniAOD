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
