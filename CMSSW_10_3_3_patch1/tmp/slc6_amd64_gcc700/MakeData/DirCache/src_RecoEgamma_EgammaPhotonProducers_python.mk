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
