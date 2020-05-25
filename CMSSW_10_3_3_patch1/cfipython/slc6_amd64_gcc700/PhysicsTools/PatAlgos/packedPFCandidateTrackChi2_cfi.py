import FWCore.ParameterSet.Config as cms

packedPFCandidateTrackChi2 = cms.EDProducer('PackedCandidateTrackChi2Producer',
  trackCollection = cms.InputTag('generalTracks'),
  candidates = cms.InputTag('packedPFCandidates')
)
