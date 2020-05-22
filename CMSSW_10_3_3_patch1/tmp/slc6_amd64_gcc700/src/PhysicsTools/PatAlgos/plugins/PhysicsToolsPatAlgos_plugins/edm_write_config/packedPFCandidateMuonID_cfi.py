import FWCore.ParameterSet.Config as cms

packedPFCandidateMuonID = cms.EDProducer('PackedCandidateMuonSelectorProducer',
  muons = cms.InputTag('patMuons'),
  candidates = cms.InputTag('packedPFCandidates'),
  muonSelectors = cms.vstring(),
  muonIDs = cms.vstring()
)
