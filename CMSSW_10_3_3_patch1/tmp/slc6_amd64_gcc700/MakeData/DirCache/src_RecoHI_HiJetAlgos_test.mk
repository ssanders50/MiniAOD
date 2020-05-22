ALL_COMMONRULES += src_RecoHI_HiJetAlgos_test
src_RecoHI_HiJetAlgos_test_parent := RecoHI/HiJetAlgos
src_RecoHI_HiJetAlgos_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoHI_HiJetAlgos_test,src/RecoHI/HiJetAlgos/test,TEST))
