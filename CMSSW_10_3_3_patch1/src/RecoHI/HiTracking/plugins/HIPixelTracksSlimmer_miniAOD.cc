//Based on: PhysicsTools/PatAlgos/plugins/PATLostTracks.cc

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/Common/interface/Association.h"

#include <vector>

//
// class declaration
//

class HIPixelTracksSlimmer_miniAOD : public edm::stream::EDProducer<> {
   public:
      explicit HIPixelTracksSlimmer_miniAOD(const edm::ParameterSet&);
      ~HIPixelTracksSlimmer_miniAOD();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

      void addPackedCandidate(std::vector<pat::PackedCandidate>& cands,
                              const reco::TrackRef& trk,
                              const reco::VertexRef& pvSlimmed,
                              const reco::VertexRefProd& pvSlimmedColl,
                              bool  passPixelTrackSel)const;

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      const edm::EDGetTokenT<reco::TrackCollection> srcTracks_;
      const edm::EDGetTokenT<reco::VertexCollection> srcVertices_;
      const edm::EDGetTokenT<reco::VertexCollection> srcPrimaryVertices_;
      const double dzSigCut_;
      const double dxySigCut_;
      const double dzSigHP_;
      const double dxySigHP_;
      const double ptMax_;
      const int covarianceVersion_;
      const int covarianceSchema_;
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
HIPixelTracksSlimmer_miniAOD::HIPixelTracksSlimmer_miniAOD(const edm::ParameterSet& iConfig) : 
  srcTracks_(consumes<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("srcTracks"))),
  srcVertices_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("srcVertices"))),
  srcPrimaryVertices_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("srcPrimaryVertices"))),
  dzSigCut_(iConfig.getParameter<double>("dzSigCut")),
  dxySigCut_(iConfig.getParameter<double>("dxySigCut")),
  dzSigHP_(iConfig.getParameter<double>("dzSigHP")),
  dxySigHP_(iConfig.getParameter<double>("dxySigHP")),
  ptMax_(iConfig.getParameter<double>("ptMax")),
  covarianceVersion_(iConfig.getParameter<int>("covarianceVersion")),
  covarianceSchema_(iConfig.getParameter<int>("covarianceSchema"))
{
  produces< std::vector<reco::Track> >();
  produces< std::vector<pat::PackedCandidate> >();
  produces< edm::Association<pat::PackedCandidateCollection> >();
}


HIPixelTracksSlimmer_miniAOD::~HIPixelTracksSlimmer_miniAOD()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
HIPixelTracksSlimmer_miniAOD::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;


  //track collection
  edm::Handle<reco::TrackCollection > tracks;
  iEvent.getByToken(srcTracks_, tracks); 

  auto outPtrTrks = std::make_unique<std::vector<reco::Track>>();
  auto outPtrTrksAsCands = std::make_unique<std::vector<pat::PackedCandidate>>();

  //vtx collections 
  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByToken(srcVertices_,vertices);

  edm::Handle<reco::VertexCollection> pvs;
  iEvent.getByToken(srcPrimaryVertices_, pvs);
  reco::VertexRef pv(pvs.id());
  reco::VertexRefProd pvRefProd(pvs);
  if(!pvs->empty()){
    pv = reco::VertexRef(pvs, 0);
  } 

  //best vertex
  double bestvz=-999.9, bestvx=-999.9, bestvy=-999.9;
  double bestvzError=-999.9, bestvxError=-999.9, bestvyError=-999.9;
  const reco::Vertex & vtx = (*vertices)[0];
  bestvz = vtx.z(); bestvx = vtx.x(); bestvy = vtx.y();
  bestvzError = vtx.zError(); bestvxError = vtx.xError(); bestvyError = vtx.yError();
  math::XYZPoint bestvtx(bestvx,bestvy,bestvz); 

  std::vector<int> mapping(tracks->size(),-1);
  int pixelTrkIndx=0;
  for(unsigned int trkIndx=0; trkIndx < tracks->size(); trkIndx++){

    reco::TrackRef trk(tracks,trkIndx);

    double dzvtx = trk->dz(bestvtx);
    double dxyvtx = trk->dxy(bestvtx);
    double dzerror = sqrt(trk->dzError()*trk->dzError()+bestvzError*bestvzError);
    double dxyerror = sqrt(trk->d0Error()*trk->d0Error()+bestvxError*bestvyError);

    if(fabs(dzvtx/dzerror) >= dzSigCut_)continue;
    if(fabs(dxyvtx/dxyerror) >= dxySigCut_)continue;
    if(trk->pt() >= ptMax_)continue;

    bool passSelection=false;
    if(fabs(dzvtx/dzerror) < dzSigHP_ && fabs(dxyvtx/dxyerror) < dxySigHP_)passSelection=true;

    outPtrTrks->emplace_back(*trk);

    addPackedCandidate(*outPtrTrksAsCands,trk,pv,pvRefProd,passSelection);

    //for creating the reco::Track -> pat::PackedCandidate map
    mapping[trkIndx]=pixelTrkIndx;
    pixelTrkIndx++;
    
  }
  iEvent.put(std::move(outPtrTrks));
  edm::OrphanHandle<pat::PackedCandidateCollection> oh = iEvent.put(std::move(outPtrTrksAsCands));
  auto tk2pc = std::make_unique<edm::Association<pat::PackedCandidateCollection>>(oh);
  edm::Association<pat::PackedCandidateCollection>::Filler tk2pcFiller(*tk2pc);
  tk2pcFiller.insert(tracks, mapping.begin(), mapping.end());
  tk2pcFiller.fill();
  iEvent.put(std::move(tk2pc));
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
HIPixelTracksSlimmer_miniAOD::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
HIPixelTracksSlimmer_miniAOD::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
HIPixelTracksSlimmer_miniAOD::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
HIPixelTracksSlimmer_miniAOD::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
HIPixelTracksSlimmer_miniAOD::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
HIPixelTracksSlimmer_miniAOD::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

void 
HIPixelTracksSlimmer_miniAOD::addPackedCandidate(std::vector<pat::PackedCandidate>& cands,
					    const reco::TrackRef& trk,
					    const reco::VertexRef& pvSlimmed,
					    const reco::VertexRefProd& pvSlimmedColl,
                                            bool passPixelTrackSel)const
{
  const float mass = 0.13957018;
  
  int id=211*trk->charge();
  
  reco::Candidate::PolarLorentzVector p4(trk->pt(),trk->eta(),trk->phi(),mass);
  cands.emplace_back(pat::PackedCandidate(p4,trk->vertex(),
      				    trk->pt(),trk->eta(),trk->phi(),
      				    id,pvSlimmedColl,pvSlimmed.key()));


  if(passPixelTrackSel)
     cands.back().setTrackHighPurity(true);
  else
     cands.back().setTrackHighPurity(false);


  cands.back().setTrackProperties(*trk,covarianceSchema_,covarianceVersion_);   

}


// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HIPixelTracksSlimmer_miniAOD::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.add<edm::InputTag>("srcTracks",edm::InputTag("hiConformalPixelTracks"));
  desc.add<edm::InputTag>("srcVertices",edm::InputTag("offlinePrimaryVertices"));
  desc.add<edm::InputTag>("srcPrimaryVertices",edm::InputTag("offlineSlimmedPrimaryVertices"));
  desc.add<double>("dzSigCut",double(100.0));
  desc.add<double>("dxySigCut",double(100.0));
  desc.add<double>("dzSigHP",double(100.0));
  desc.add<double>("dxySigHP",double(100.0));
  desc.add<double>("ptMax",double(1.0));
  desc.add<int>("covarianceVersion",int(1));
  desc.add<int>("covarianceSchema",int(0));
  descriptions.add("HIPixelTracksSlimmer_miniAOD", desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HIPixelTracksSlimmer_miniAOD);
