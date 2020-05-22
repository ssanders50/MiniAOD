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
