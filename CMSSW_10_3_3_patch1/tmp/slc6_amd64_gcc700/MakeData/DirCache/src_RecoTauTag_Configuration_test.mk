ALL_COMMONRULES += src_RecoTauTag_Configuration_test
src_RecoTauTag_Configuration_test_parent := RecoTauTag/Configuration
src_RecoTauTag_Configuration_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoTauTag_Configuration_test,src/RecoTauTag/Configuration/test,TEST))
