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
