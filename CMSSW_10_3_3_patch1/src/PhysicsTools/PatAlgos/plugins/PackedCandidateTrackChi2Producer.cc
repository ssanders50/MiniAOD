#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

namespace pat {

  class PackedCandidateTrackChi2Producer : public edm::stream::EDProducer<> {

    typedef edm::ValueMap<float> FloatMap;

    public:

      explicit PackedCandidateTrackChi2Producer(const edm::ParameterSet & iConfig):
          trackToken_(consumes<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("trackCollection"))),
          candidateToken_(consumes<edm::View<pat::PackedCandidate> >(iConfig.getParameter<edm::InputTag>("candidates")))
      {
        produces<FloatMap>();
      }
      ~PackedCandidateTrackChi2Producer() override {};

      void produce(edm::Event&, const edm::EventSetup&) override;

      static void fillDescriptions(edm::ConfigurationDescriptions&);

    private:

      edm::EDGetTokenT<reco::TrackCollection> trackToken_;
      edm::EDGetTokenT<edm::View<pat::PackedCandidate> > candidateToken_;

  };

}

void pat::PackedCandidateTrackChi2Producer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<reco::TrackCollection> trks;
  edm::Handle<edm::View<pat::PackedCandidate> > candidates;

  iEvent.getByToken(trackToken_, trks);
  iEvent.getByToken(candidateToken_, candidates);

  const auto& nCand = candidates->size();
  std::vector< float > trkChi2Map(nCand, 0);

  for (size_t i = 0; i < nCand; i++) {
    const auto& cand = candidates->refAt(i);
    // ignore neutral candidates or without track
    if (cand->charge()==0 || !cand->hasTrackDetails()) continue;

    const auto& candTrack = cand->pseudoTrack();
    //check tracks for a match
    for(size_t j = 0; j<trks->size(); j++){
      reco::TrackRef trk(trks,j);

      if (trk->charge()==candTrack.charge() &&
        trk->numberOfValidHits()==candTrack.numberOfValidHits() &&
        std::abs(trk->eta()-candTrack.eta())<1E-3 &&
        std::abs(trk->phi()-candTrack.phi())<1E-3 &&
        std::abs((trk->pt()-candTrack.pt())/trk->pt())<1E-2) {

        trkChi2Map.at(i) = trk->normalizedChi2();        
     
        break;
      }
    }
  }

  // fill the value maps
  std::unique_ptr<FloatMap> valueMap(new FloatMap());
  FloatMap::Filler filler(*valueMap);
  filler.insert(candidates, trkChi2Map.begin(), trkChi2Map.end());
  filler.fill();
  iEvent.put(std::move(valueMap),"");
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void pat::PackedCandidateTrackChi2Producer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.add<edm::InputTag>("trackCollection", edm::InputTag("generalTracks"))->setComment("track input collection");
  desc.add<edm::InputTag>("candidates", edm::InputTag("packedPFCandidates"))->setComment("packed candidate input collection");
  descriptions.add("packedPFCandidateTrackChi2", desc);
}

#include "FWCore/Framework/interface/MakerMacros.h"
using namespace pat;
DEFINE_FWK_MODULE(PackedCandidateTrackChi2Producer);
