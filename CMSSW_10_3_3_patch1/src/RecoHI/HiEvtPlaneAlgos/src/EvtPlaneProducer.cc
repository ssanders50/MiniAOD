// -*- C++ -*-
//
// Package:    EvtPlaneProducer
// Class:      EvtPlaneProducer
// 
/**\class EvtPlaneProducer EvtPlaneProducer.cc RecoHI/EvtPlaneProducer/src/EvtPlaneProducer.cc
   
Description: <one line class summary>

Implementation:
<Notes on implementation>
*/
//
// Original Author:  Sergey Petrushanko
//         Created:  Fri Jul 11 10:05:00 2008
//
//

// system include files
#include <memory>
#include <iostream>
#include <ctime>
#include <cmath>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/ESWatcher.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"


#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/Common/interface/Ref.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/CastorReco/interface/CastorTower.h"
#include "DataFormats/Common/interface/ValueMap.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include <cstdlib>
#include "RecoHI/HiEvtPlaneAlgos/interface/HiEvtPlaneList.h"
#include "CondFormats/HIObjects/interface/RPFlatParams.h"
#include "CondFormats/DataRecord/interface/HeavyIonRPRcd.h"
#include "CondFormats/DataRecord/interface/HeavyIonRcd.h"
#include "CondFormats/HIObjects/interface/CentralityTable.h"

#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefVector.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "RecoHI/HiEvtPlaneAlgos/interface/HiEvtPlaneFlatten.h"
#include "RecoHI/HiEvtPlaneAlgos/interface/LoadEPDB.h"

using namespace std;
using namespace hi;

//
// class decleration
//

namespace hi {
  class GenPlane {
  public:
    GenPlane(string name,double etaminval1,double etamaxval1,double etaminval2,double etamaxval2,int orderval){
      epname=name;
      etamin1=etaminval1;
      etamax1=etamaxval1;
      etamin2=etaminval2;
      etamax2=etamaxval2;
      sumsin=0;
      sumcos=0;
      sumsinNoWgt=0;
      sumcosNoWgt=0;
      
      mult = 0;
      order = (double) orderval;
    }
    ~GenPlane(){;}
    void addParticle(double w, double PtOrEt, double s, double c, double eta) {
      if((eta>=etamin1 && eta<etamax1) || 
	 (etamin2!= etamax2 && eta>=etamin2 && eta<etamax2 )) {
	sumsin+=w*s;
	sumcos+=w*c;
	sumsinNoWgt+=s;
	sumcosNoWgt+=c;
	
	sumw+=fabs(w);
	sumw2+=w*w;
	sumPtOrEt+=PtOrEt;
	sumPtOrEt2+=PtOrEt*PtOrEt;
	++mult;
      }
    }
    
    double getAngle(double &ang, double &sv, double &cv, double &svNoWgt, double &cvNoWgt,  double &w, double &w2, double &PtOrEt, double &PtOrEt2, uint &epmult){
      ang = -10;
      sv = 0;
      cv = 0;
      sv = sumsin;
      cv = sumcos;
      svNoWgt = sumsinNoWgt;
      cvNoWgt = sumcosNoWgt;
      w = sumw;
      w2 = sumw2;
      PtOrEt = sumPtOrEt;
      PtOrEt2 = sumPtOrEt2;
      epmult = mult;
      double q = sv*sv+cv*cv;
      if(q>0) ang = atan2(sv,cv)/order;
      return ang;
    }
    void reset() {
      sumsin=0;
      sumcos=0;
      sumsinNoWgt = 0;
      sumcosNoWgt = 0;
      sumw = 0;
      sumw2 = 0;
      mult = 0;
      sumPtOrEt = 0;
      sumPtOrEt2 = 0;
    }
  private:
    string epname;
    double etamin1;
    double etamax1;
    
    double etamin2;
    double etamax2;
    double sumsin;
    double sumcos;
    double sumsinNoWgt;
    double sumcosNoWgt;
    uint mult;
    double sumw;
    double sumw2;
    double sumPtOrEt;
    double sumPtOrEt2;
    double order;
  };
}

class EvtPlaneProducer : public edm::stream::EDProducer<> {
public:
  explicit EvtPlaneProducer(const edm::ParameterSet&);
  ~EvtPlaneProducer() override;
  
private:
  GenPlane *rp[NumEPNames];
  
  void produce(edm::Event&, const edm::EventSetup&) override;
  
  // ----------member data ---------------------------
  
  std::string centralityVariable_;
  std::string centralityLabel_;
  std::string centralityMC_;
  
  edm::InputTag centralityBinTag_;
  edm::EDGetTokenT<int> centralityBinToken;
  
  
  edm::InputTag vertexTag_;
  edm::EDGetTokenT<std::vector<reco::Vertex>> vertexToken;
  edm::Handle<std::vector<reco::Vertex>> vertex_;
  
  edm::InputTag caloTag_;
  edm::EDGetTokenT<CaloTowerCollection> caloToken;
  edm::Handle<CaloTowerCollection> caloCollection_;
  
  edm::InputTag castorTag_;
  edm::EDGetTokenT<std::vector<reco::CastorTower>> castorToken;
  edm::Handle<std::vector<reco::CastorTower>> castorCollection_;
  
  edm::InputTag trackTag_;
  edm::EDGetTokenT<reco::TrackCollection> trackToken;
  edm::InputTag losttrackTag_;
  edm::EDGetTokenT<reco::TrackCollection> losttrackToken;
  edm::Handle<reco::TrackCollection> trackCollection_;
  string strack;
  
  edm::EDGetTokenT<edm::View<pat::PackedCandidate>> packedToken;
  //  edm::Handle< pat::PackedCandidateCollection > packedCollection_;
  
  edm::EDGetTokenT<edm::View<pat::PackedCandidate>> lostToken;
  //  edm::Handle< pat::PackedCandidateCollection > lostCollection_;
  
  edm::ESWatcher<HeavyIonRcd> hiWatcher;
  edm::ESWatcher<HeavyIonRPRcd> hirpWatcher;
  
  edm::InputTag chi2MapLabel_;
  edm::EDGetTokenT<edm::ValueMap<float>> chi2Map_;
  edm::InputTag chi2MapLostLabel_;
  edm::EDGetTokenT<edm::ValueMap<float>> chi2MapLost_;

  std::vector< float > trkNormChi2;

  bool loadDB_;
  double minet_;
  double maxet_;
  double minpt_;
  double maxpt_;
  double minvtx_;
  double maxvtx_;
  int flatnvtxbins_;
  double flatminvtx_;
  double flatdelvtx_;
  double dzdzerror_;
  double d0d0error_;
  double pterror_;
  double chi2perlayer_;
  double dzerr_;
  double dzdzerror_pix_;
  double chi2_;
  int FlatOrder_;
  int NumFlatBins_;
  double nCentBins_;
  double caloCentRef_;
  double caloCentRefWidth_;
  int CentBinCompression_;
  HiEvtPlaneFlatten * flat[NumEPNames];
  
  struct TrackStructure {
    double eta;
    double phi;
    double et;
    double pt;
    int charge;
    int pdgid;
    int hits;
    int algos;
    double dz;
    double dxy;
    double dzError;
    double dxyError;
    double ptError;
    bool highPurity;
    double dzSig;
    double dxySig;
    double normalizedChi2;
    double chi2;
  } track;
  
  bool GoodHF(TrackStructure track){
    if(track.pdgid!=1 || track.pdgid!= 2) return false;
    if(fabs(track.eta)<3 || fabs(track.eta)>5) return false;
    return true;
  }
  void FillHF(TrackStructure track, double vz, int bin){
    double minet = minet_;
    double maxet = maxet_;
    for(int i = 0; i<NumEPNames; i++) {
      if(minet_<0) minet = minTransverse[i];
      if(maxet_<0) maxet = maxTransverse[i];
      if(track.et<minet) continue;
      if(track.et>maxet) continue;
      if(EPDet[i]==HF) {
	double w = track.et;
	if(loadDB_) w = track.et*flat[i]->getEtScale(vz,bin);
	if(EPOrder[i]==1 ) {
	  if(MomConsWeight[i][0]=='y' && loadDB_ ) {
	    w = flat[i]->getW(track.et, vz, bin);
	  }
	  if(track.eta<0 ) w=-w;
	}
	rp[i]->addParticle(w,track.et,sin(EPOrder[i]*track.phi),cos(EPOrder[i]*track.phi),track.eta);
      }
    }
  };
  
  
  bool GoodCastor(TrackStructure track){
    return true;
  }
  void FillCastor(TrackStructure track, double vz, int bin){
    double minet = minet_;
    double maxet = maxet_;
    for(int i = 0; i<NumEPNames; i++) {
      if(EPDet[i]==Castor) {
	if(minet_<0) minet = minTransverse[i];
	if(maxet_<0) maxet = maxTransverse[i];
	if(track.et<minet) continue;
	if(track.et>maxet) continue;
	double w = track.et;
	if(EPOrder[i]==1 ) {
	  if(MomConsWeight[i][0]=='y' && loadDB_ ) {
	    w = flat[i]->getW(track.et, vz, bin);
	  }
	  if(track.eta<0 ) w=-w;
	}
	rp[i]->addParticle(w,track.et,sin(EPOrder[i]*track.phi),cos(EPOrder[i]*track.phi),track.eta);
      }
    }
  }
  
  bool GoodTrack(TrackStructure track){
    bool isPixel = false;
    //std::cout<<track.charge<<"\t"<<track.algos<<"\t"<<track.highPurity<<"\t"<<track.hits<<"\t"<<track.chi2<<"\t"<<track.dzSig<<"\t"<<track.dxySig<<"\t"<<track.ptError<<"\t"<<track.pt<<std::endl;
    if ( track.charge == 0) return false;
    
    // determine if the track is a pixel track
    if ( track.hits < 7 ) isPixel = true;
    //    if(
    //   track.algos != 4 and
    //   track.algos != 5 and
    //   track.algos != 6 and
    //   track.algos != 7 ) return false;
  
  // cuts for pixel tracks
  if( isPixel ){
    if ( track.dzSig > dzerr_ ) return  false;
    if ( track.normalizedChi2 > chi2_ ) return false;
  }
  // cuts for full tracks
  if ( ! isPixel) {
    //if( !track.highPurity ) return false;
    if(track.hits < 11 ) return false;
    if(track.chi2 > chi2perlayer_) return false;
    if (track.dzSig > dzdzerror_ ) return false;
    if ( track.dxySig > d0d0error_ ) return false;
    if ( track.ptError/track.pt > pterror_ ) return false;
    
  }
  return true;
}
  void FillTracker(TrackStructure track, double vz, int bin){
    double minpt = minpt_;
    double maxpt = maxpt_;
    for(int i = 0; i<NumEPNames; i++) {
      if(minpt_<0) minpt = minTransverse[i];
      if(maxpt_<0) maxpt = maxTransverse[i];
      if(track.pt<minpt) continue;
      if(track.pt>maxpt) continue;
      if(EPDet[i]==Tracker) {
	double w = track.pt;
	if(w>2.5) w=2.0;   //v2 starts decreasing above ~2.5 GeV/c
	if(EPOrder[i]==1) {
	  if(MomConsWeight[i][0]=='y' && loadDB_) {
	    w = flat[i]->getW(track.pt, vz, bin);
	  }
	  if(track.eta<0) w=-w;
	}
	rp[i]->addParticle(w,track.pt,sin(EPOrder[i]*track.phi),cos(EPOrder[i]*track.phi),track.eta);
      }
    }
  };
  


};

EvtPlaneProducer::EvtPlaneProducer(const edm::ParameterSet& iConfig):
  centralityVariable_ ( iConfig.getParameter<std::string>("centralityVariable") ),
  centralityBinTag_ ( iConfig.getParameter<edm::InputTag>("centralityBinTag") ),
  vertexTag_  ( iConfig.getParameter<edm::InputTag>("vertexTag") ),
  caloTag_ ( iConfig.getParameter<edm::InputTag>("caloTag") ),
  castorTag_ ( iConfig.getParameter<edm::InputTag>("castorTag") ),
  trackTag_ ( iConfig.getParameter<edm::InputTag>("trackTag") ),
  losttrackTag_ ( iConfig.getParameter<edm::InputTag>("lostTag") ),
  loadDB_ ( iConfig.getParameter<bool>("loadDB") ),
  minet_ ( iConfig.getParameter<double>("minet") ),
  maxet_ ( iConfig.getParameter<double>("maxet") ),
  minpt_ ( iConfig.getParameter<double>("minpt") ),
  maxpt_ ( iConfig.getParameter<double>("maxpt") ),
  minvtx_ ( iConfig.getParameter<double>("minvtx") ),
  maxvtx_ ( iConfig.getParameter<double>("maxvtx") ),
  flatnvtxbins_ ( iConfig.getParameter<int>("flatnvtxbins") ),
  flatminvtx_ ( iConfig.getParameter<double>("flatminvtx") ),
  flatdelvtx_ ( iConfig.getParameter<double>("flatdelvtx") ),
  dzdzerror_ (iConfig.getParameter<double>("dzdzerror_")),
  d0d0error_ ( iConfig.getParameter<double>("d0d0error_")),
  pterror_ ( iConfig.getParameter<double>("pterror_")),
  chi2perlayer_  (iConfig.getParameter<double>("chi2perlayer_")),
  dzerr_ ( iConfig.getParameter<double>("dzerr") ),
  dzdzerror_pix_ ( iConfig.getParameter<double>("dzdzerror_pix_")) ,
  chi2_  ( iConfig.getParameter<double>("chi2") ),
  FlatOrder_ ( iConfig.getParameter<int>("FlatOrder") ),
  NumFlatBins_ ( iConfig.getParameter<int>("NumFlatBins") ),
  caloCentRef_ ( iConfig.getParameter<double>("caloCentRef") ),
  caloCentRefWidth_ ( iConfig.getParameter<double>("caloCentRefWidth") ),
  CentBinCompression_ ( iConfig.getParameter<int>("CentBinCompression") )
{

  nCentBins_ = 200.;

  if(iConfig.exists("nonDefaultGlauberModel")){
    centralityMC_ = iConfig.getParameter<std::string>("nonDefaultGlauberModel");
  }
  centralityLabel_ = centralityVariable_+centralityMC_;

  centralityBinToken = consumes<int>(centralityBinTag_);

  vertexToken = consumes<std::vector<reco::Vertex>>(vertexTag_);

  chi2MapLabel_ = iConfig.getParameter<edm::InputTag>("chi2Map");
  chi2Map_ = consumes<edm::ValueMap<float>>(chi2MapLabel_);
  chi2MapLostLabel_ = iConfig.getParameter<edm::InputTag>("chi2MapLost");
  chi2MapLost_ = consumes<edm::ValueMap<float>>(chi2MapLostLabel_);


  strack = trackTag_.label();
  if(strack.find("packedPFCandidates")!=std::string::npos) {
    packedToken = consumes<edm::View<pat::PackedCandidate>>(trackTag_);
    lostToken = consumes<edm::View<pat::PackedCandidate>>(losttrackTag_);
  } else {
    caloToken = consumes<CaloTowerCollection>(caloTag_); 
    castorToken = consumes<std::vector<reco::CastorTower>>(castorTag_);
    trackToken = consumes<reco::TrackCollection>(trackTag_);
  }

  produces<reco::EvtPlaneCollection>();
  for(int i = 0; i<NumEPNames; i++ ) {
    rp[i] = new GenPlane(EPNames[i],EPEtaMin1[i],EPEtaMax1[i],EPEtaMin2[i],EPEtaMax2[i],EPOrder[i]);
  }
  for(int i = 0; i<NumEPNames; i++) {
    flat[i] = new HiEvtPlaneFlatten();
    flat[i]->init(FlatOrder_,NumFlatBins_,flatnvtxbins_,flatminvtx_,flatdelvtx_,EPNames[i],EPOrder[i]);
  }

}


EvtPlaneProducer::~EvtPlaneProducer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  for(int i = 0; i<NumEPNames; i++) {
    delete flat[i];
  }

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
EvtPlaneProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;

  if( loadDB_ && (hiWatcher.check(iSetup) || hirpWatcher.check(iSetup)) ) {
    //
    //Get Size of Centrality Table
    //
    edm::ESHandle<CentralityTable> centDB_;
    iSetup.get<HeavyIonRcd>().get(centralityLabel_,centDB_);
    nCentBins_ = centDB_->m_table.size();
    for(int i = 0; i<NumEPNames; i++) {
      if(caloCentRef_>0) {
	int minbin = (caloCentRef_-caloCentRefWidth_/2.)*nCentBins_/100.;
	int maxbin = (caloCentRef_+caloCentRefWidth_/2.)*nCentBins_/100.;
	minbin/=CentBinCompression_;
	maxbin/=CentBinCompression_;
	if(minbin>0 && maxbin>=minbin) {
	  if(EPDet[i]==HF || EPDet[i]==Castor) flat[i]->setCaloCentRefBins(minbin,maxbin);
	}
      }
    }

    //
    //Get flattening parameter file.  
    //
    if ( loadDB_ ) {
	edm::ESHandle<RPFlatParams> flatparmsDB_;
	iSetup.get<HeavyIonRPRcd>().get(flatparmsDB_);
	LoadEPDB db(flatparmsDB_,flat);
	if(!db.IsSuccess()) {
	  loadDB_ = kFALSE;
	}
    }

  } //rp record change

  //
  //Get Centrality
  //
  int bin = 0;
  if(loadDB_) {
    edm::Handle<int> cbin_;
    iEvent.getByToken(centralityBinToken, cbin_);
    int cbin = *cbin_;
    bin = cbin/CentBinCompression_;
  }

  //vtx collection
  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByToken(vertexToken,vertices);
  
  //best vertex
  double bestvz=-999.9, bestvx=-999.9, bestvy=-999.9;
  double bestvzError=-999.9, bestvxError=-999.9, bestvyError=-999.9;
  const reco::Vertex & vtx = (*vertices)[0];
  bestvz = vtx.z(); bestvx = vtx.x(); bestvy = vtx.y();
  bestvzError = vtx.zError(); bestvxError = vtx.xError(); bestvyError = vtx.yError();
  math::XYZPoint bestvtx(bestvx,bestvy,bestvz);
  
  
  //
  for(int i = 0; i<NumEPNames; i++) rp[i]->reset();
  if(bestvz < minvtx_ or bestvz > maxvtx_) return;
  //edm::Handle<edm::ValueMap<float>> chi2Map;
  edm::Handle<edm::View<pat::PackedCandidate>> cands;

  if(strack.find("packedPFCandidates")!=std::string::npos) {
    //iEvent.getByToken(packedToken, packedCollection_);
    iEvent.getByToken(packedToken, cands);
    //iEvent.getByToken(chi2Map_, chi2Map);
    for(unsigned int i = 0, n=cands->size(); i<n; ++i){
      track = {};
      const pat::PackedCandidate &pf = (*cands)[i];
      track.eta            = pf.eta();
      track.phi            = pf.phi();
      track.et             = pf.et();
      track.charge         = pf.charge();
      track.pdgid          = pf.pdgId();
      if(fabs(track.eta)<3.0) {
	if(!pf.hasTrackDetails()) continue;
	const reco::Track trk  = pf.pseudoTrack();
	track.pt             = trk.pt();
	track.ptError        = trk.ptError();
	track.hits           = trk.numberOfValidHits();
	track.algos           = trk.algo();
	track.dz             = trk.dz(bestvtx);
	track.dxy            = trk.dxy(bestvtx);
	track.dzError        = sqrt(pow(trk.dzError(),2) + pow(bestvzError,2));
	track.dxyError       = sqrt(pow(trk.dxyError(),2)+bestvxError*bestvyError);
	track.highPurity     = pf.trackHighPurity();
	track.dzSig          = track.dz/track.dzError;
	track.dxySig         = track.dxy/track.dxyError;
	//const reco::HitPattern& hit_pattern = trk.hitPattern();
	//	track.chi2 = (*chi2Map)[cands->ptrAt(i)]/hit_pattern.trackerLayersWithMeasurement();
      }     
      if(GoodHF(track)) {
	FillHF(track,bestvz,bin);
      } else if (GoodTrack(track)) {
	FillTracker(track,bestvz,bin);
      }	    
    }    

    //iEvent.getByToken(lostToken, packedCollection_);
    iEvent.getByToken(lostToken, cands);
    //iEvent.getByToken(chi2MapLost_, chi2Map);
    for(unsigned int i = 0, n=cands->size(); i<n; ++i){
      const pat::PackedCandidate &pf = (*cands)[i];
      track = {};
      track.eta            = pf.eta();
      track.phi            = pf.phi();
      track.et             = pf.et();
      track.charge         = pf.charge();
      track.pdgid          = pf.pdgId();
      if(fabs(track.eta)<3.0) {
	if(!pf.hasTrackDetails()) continue;
	const reco::Track trk  = pf.pseudoTrack();
	track.pt             = trk.pt();
	track.ptError        = trk.ptError();
	track.hits           = trk.numberOfValidHits();
	track.algos           = trk.algo();
	track.dz             = trk.dz(bestvtx);
	track.dxy            = trk.dxy(bestvtx);
	track.dzError        = sqrt(pow(trk.dzError(),2) + pow(bestvzError,2));
	track.dxyError       = sqrt(pow(trk.dxyError(),2)+bestvxError*bestvyError);
	track.highPurity     = pf.trackHighPurity();
	track.dzSig          = track.dz/track.dzError;
	track.dxySig         = track.dxy/track.dxyError;
	//const reco::HitPattern& hit_pattern = trk.hitPattern();
	//track.chi2 = (*chi2Map)[cands->ptrAt(i)]/hit_pattern.trackerLayersWithMeasurement();
      }     
      if(GoodHF(track)) {
	FillHF(track,bestvz,bin);
      } else if (GoodTrack(track)) {
	FillTracker(track,bestvz,bin);
      }	    
    }    
    
  } else {
    
    //calorimetry part        
    iEvent.getByToken(caloToken,caloCollection_);
    if(caloCollection_.isValid()){
      for (CaloTowerCollection::const_iterator j = caloCollection_->begin();j !=caloCollection_->end(); j++) {
	track.eta          = j->eta();
	track.phi          = j->phi();
	track.et     = j->emEt() + j->hadEt();
	if(GoodHF(track)) FillHF(track,bestvz,bin);
      }
    }
    
    //Castor part    
    iEvent.getByToken(castorToken,castorCollection_);    
    if(castorCollection_.isValid()){
      for (std::vector<reco::CastorTower>::const_iterator j = castorCollection_->begin();j !=castorCollection_->end(); j++) {
       	track.eta        = j->eta();
       	track.phi        = j->phi();
       	track.et         = j->et();
	if(GoodCastor(track)) FillCastor(track,bestvz,bin);
      }
      
    }
    //Tracking part
    iEvent.getByToken(trackToken, trackCollection_);
    if(trackCollection_.isValid()){
      for(reco::TrackCollection::const_iterator j = trackCollection_->begin(); j != trackCollection_->end(); j++){
	track.eta       = j->eta();
	track.phi       = j->phi();
	track.pt        = j->pt();
	track.charge    = j->charge();
	track.hits      = j->numberOfValidHits();
	track.algos      = j->algo();
	track.dz        = j->dz(bestvtx);
	track.dxy       = -1.*j->dxy(bestvtx);
	track.dzError   = sqrt(pow(j->dzError(),2) + pow(bestvzError,2));
	track.dxyError  = sqrt(pow(j->d0Error(),2) + bestvxError*bestvyError);
	track.highPurity= j->quality(reco::TrackBase::highPurity);
	track.dzSig     = track.dz/track.dzError;
	track.dxySig    = track.dxy/track.dxyError;
	track.normalizedChi2 = j->normalizedChi2();
	track.chi2 = track.normalizedChi2/j->hitPattern().trackerLayersWithMeasurement();
	
	if(GoodTrack(track)) FillTracker(track,bestvz,bin);
      }
    }
  }
  
  auto evtplaneOutput = std::make_unique<EvtPlaneCollection>();
  
  double ang=-10;
  double sv = 0;
  double cv = 0;
  double svNoWgt = 0;
  double cvNoWgt = 0;
  
  double wv = 0;
  double wv2 = 0;
  double pe = 0;
  double pe2 = 0;
  uint epmult = 0;
  
  for(int i = 0; i<NumEPNames; i++) {
    rp[i]->getAngle(ang,sv,cv,svNoWgt, cvNoWgt, wv,wv2,pe,pe2,epmult);
    evtplaneOutput->push_back( EvtPlane(i,0,ang,sv,cv,wv,wv2,pe,pe2,epmult) );
    evtplaneOutput->back().addLevel(3, 0., svNoWgt, cvNoWgt);
  }
  
  iEvent.put(std::move(evtplaneOutput));
}

//define this as a plug-in
DEFINE_FWK_MODULE(EvtPlaneProducer);