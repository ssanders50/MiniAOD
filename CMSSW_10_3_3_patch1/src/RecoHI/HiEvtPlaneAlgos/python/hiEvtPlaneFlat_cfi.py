import FWCore.ParameterSet.Config as cms

hiEvtPlaneFlat = cms.EDProducer('HiEvtPlaneFlatProducer',
                                vertexTag = cms.InputTag("offlinePrimaryVerticesRecovery"),
                                centralityTag = cms.InputTag("hiCentrality"),
                                centralityBinTag = cms.InputTag("centralityBin","HFtowers"),
                                centralityVariable = cms.string("HFtowers"),
                                nonDefaultGlauberModel = cms.string(""),
                                inputPlanesTag = cms.InputTag("hiEvtPlane"),
                                trackTag = cms.InputTag("generalTracks"),
                                FlatOrder = cms.int32(9),
                                NumFlatBins = cms.int32(40),
                                Noffmin = cms.int32 (-1),
                                Noffmax = cms.int32 (10000),
                                CentBinCompression = cms.int32(5),
                                flatnvtxbins = cms.int32(10),
                                flatminvtx = cms.double(-15.0),
                                flatdelvtx = cms.double(3.0),
                                caloCentRef = cms.double(-1.),
                                caloCentRefWidth = cms.double(-1.),
                                useOffsetPsi = cms.bool(True)
                                )
