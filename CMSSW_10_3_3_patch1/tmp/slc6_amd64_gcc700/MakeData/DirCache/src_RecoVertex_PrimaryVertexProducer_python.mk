ifeq ($(strip $(PyRecoVertexPrimaryVertexProducer)),)
PyRecoVertexPrimaryVertexProducer := self/src/RecoVertex/PrimaryVertexProducer/python
src_RecoVertex_PrimaryVertexProducer_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/RecoVertex/PrimaryVertexProducer/python)
PyRecoVertexPrimaryVertexProducer_files := $(patsubst src/RecoVertex/PrimaryVertexProducer/python/%,%,$(wildcard $(foreach dir,src/RecoVertex/PrimaryVertexProducer/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyRecoVertexPrimaryVertexProducer_LOC_USE := self cmssw 
PyRecoVertexPrimaryVertexProducer_PACKAGE := self/src/RecoVertex/PrimaryVertexProducer/python
ALL_PRODS += PyRecoVertexPrimaryVertexProducer
PyRecoVertexPrimaryVertexProducer_INIT_FUNC        += $$(eval $$(call PythonProduct,PyRecoVertexPrimaryVertexProducer,src/RecoVertex/PrimaryVertexProducer/python,src_RecoVertex_PrimaryVertexProducer_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyRecoVertexPrimaryVertexProducer,src/RecoVertex/PrimaryVertexProducer/python))
endif
ALL_COMMONRULES += src_RecoVertex_PrimaryVertexProducer_python
src_RecoVertex_PrimaryVertexProducer_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoVertex_PrimaryVertexProducer_python,src/RecoVertex/PrimaryVertexProducer/python,PYTHON))
