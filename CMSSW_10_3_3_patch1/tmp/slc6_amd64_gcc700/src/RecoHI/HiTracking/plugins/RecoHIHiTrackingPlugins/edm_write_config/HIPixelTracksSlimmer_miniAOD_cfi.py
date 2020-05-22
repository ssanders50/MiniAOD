import FWCore.ParameterSet.Config as cms

HIPixelTracksSlimmer_miniAOD = cms.EDProducer('HIPixelTracksSlimmer_miniAOD',
  srcTracks = cms.InputTag('hiConformalPixelTracks'),
  srcVertices = cms.InputTag('offlinePrimaryVertices'),
  srcPrimaryVertices = cms.InputTag('offlineSlimmedPrimaryVertices'),
  dzSigCut = cms.double(100),
  dxySigCut = cms.double(100),
  dzSigHP = cms.double(100),
  dxySigHP = cms.double(100),
  ptMax = cms.double(1),
  covarianceVersion = cms.int32(1),
  covarianceSchema = cms.int32(0)
)
