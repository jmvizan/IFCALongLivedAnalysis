//=======================================================================================================================================================================================================================// 
//                                                                                                                                                                                                                       // 
//$$$$$$\ $$$$$$$$\  $$$$$$\   $$$$$$\                      $$\                                    $$\       $$\                            $$\  $$$$$$\                      $$\                     $$                 //
//\_$$  _|$$  _____|$$  __$$\ $$  __$$\                     $$ |                                   $$ |      \__|                           $$ |$$  __$$\                     $$ |                    \__|               //
//  $$ |  $$ |      $$ /  \__|$$ /  $$ |                    $$ |      $$$$$$\  $$$$$$$\   $$$$$$\  $$ |      $$\ $$\    $$\  $$$$$$\   $$$$$$$ |$$ /  $$ |$$$$$$$\   $$$$$$\  $$ |$$\   $$\  $$$$$$$\ $$\  $$$$$$$       //
//  $$ |  $$$$$\    $$ |      $$$$$$$$ |      $$$$$$\       $$ |     $$  __$$\ $$  __$$\ $$  __$$\ $$ |      $$ |\$$\  $$  |$$  __$$\ $$  __$$ |$$$$$$$$ |$$  __$$\  \____$$\ $$ |$$ |  $$ |$$  _____|$$ |$$  _____|     //
//  $$ |  $$  __|   $$ |      $$  __$$ |      \______|      $$ |     $$ /  $$ |$$ |  $$ |$$ /  $$ |$$ |      $$ | \$$\$$  / $$$$$$$$ |$$ /  $$ |$$  __$$ |$$ |  $$ | $$$$$$$ |$$ |$$ |  $$ |\$$$$$$\  $$ |\$$$$$$        // 
//  $$ |  $$ |      $$ |  $$\ $$ |  $$ |                    $$ |     $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |      $$ |  \$$$  /  $$   ____|$$ |  $$ |$$ |  $$ |$$ |  $$ |$$  __$$ |$$ |$$ |  $$ | \____$$\ $$ | \____$$       //
//$$$$$$\ $$ |      \$$$$$$  |$$ |  $$ |                    $$$$$$$$\\$$$$$$  |$$ |  $$ |\$$$$$$$ |$$$$$$$$\ $$ |   \$  /   \$$$$$$$\ \$$$$$$$ |$$ |  $$ |$$ |  $$ |\$$$$$$$ |$$ |\$$$$$$$ |$$$$$$$  |$$ |$$$$$$$  |     //
//\______|\__|       \______/ \__|  \__|                    \________|\______/ \__|  \__| \____$$ |\________|\__|    \_/     \_______| \_______|\__|  \__|\__|  \__| \_______|\__| \____$$ |\_______/ \__|\_______/      //
//                                                                                       $$\   $$ |                                                                               $$\   $$ |                             // 
//                                                                                       \$$$$$$  |                                                                               \$$$$$$  |                             //
//=======================================================================================================================================================================================================================//
//                                                                                                                                                                                                                       //
// Authors of the code: Celia Fernandez Madrazo                                                                                                                                                                          //
//                      Pablo Martinez Ruiz Del Arbol                                                                                                                                                                    //
//                                                                                                                                                                                                                       //
//=======================================================================================================================================================================================================================//
//                                                                                                                                                                                                                       //
// Description: Main analyzer                                                                                                                                                                                            //
//                                                                                                                                                                                                                       //
//=======================================================================================================================================================================================================================//



#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/IsolatedTrack.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/PFIsolation.h"


//#include "DataFormats/MuonReco/interface/MuonFwd.h" 

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "TLorentzVector.h"
#include "TTree.h"
#include "TFile.h"


//=======================================================================================================================================================================================================================//


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// FUNCTIONS ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

bool goodPhoton(const pat::Photon & photon)
{

    // Return true if the photon fulfills with the analysis requirements and false instead

    if (fabs(photon.eta()) > 1.4442 && fabs(photon.eta()) < 1.566) { return false; } // narrow EB region to be defined
    if (photon.hadronicOverEm() > 0.05) { return false; }
    if (photon.isEE() && photon.full5x5_sigmaIetaIeta() > 0.034) { return false; }
    if (photon.isEB() && photon.full5x5_sigmaIetaIeta() > 0.012) { return false; }

    return true;

}

bool goodTrack(const pat::IsolatedTrack & track)
{

    // Fill
    return true;

}



/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// DATA DEFINITION //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////// BRANCHES /////////////////////////////////////


//-> ISOTRACK SELECTION
const Int_t nIsoTrackMax = 500;
Int_t nIsoTrack;
// Primitive:
Float_t IsoTrackSel_pt[nIsoTrackMax];
Float_t IsoTrackSel_eta[nIsoTrackMax];
Float_t IsoTrackSel_phi[nIsoTrackMax];
Float_t IsoTrackSel_dxy[nIsoTrackMax];
Float_t IsoTrackSel_dxyError[nIsoTrackMax];
Float_t IsoTrackSel_dz[nIsoTrackMax];
Float_t IsoTrackSel_dzError[nIsoTrackMax];
Float_t IsoTrackSel_pfIsolationDR03[nIsoTrackMax];
Float_t IsoTrackSel_miniPFIsolation[nIsoTrackMax];
Int_t IsoTrackSel_isHighPurityTrack[nIsoTrackMax];
Int_t IsoTrackSel_numberOfValidTrackerHits[nIsoTrackMax];
Int_t IsoTrackSel_numberOfValidPixelHits[nIsoTrackMax];
// Derived:
Float_t IsoTrackSel_dxySignificance[nIsoTrackMax];


//-> PHOTON SELECTION
const Int_t nPhotonMax = 100;
Int_t nPhoton;
// Primitive:
Float_t PhotonSel_et[nPhotonMax];
Float_t PhotonSel_eta[nPhotonMax];
Float_t PhotonSel_phi[nPhotonMax];
Float_t PhotonSel_hadronicOverEm[nPhotonMax];
Float_t PhotonSel_full5x5_sigmaIetaIeta[nPhotonMax];
Int_t PhotonSel_isEB[nPhotonMax];
Int_t PhotonSel_isEE[nPhotonMax];


//-> ELECTRON CANDIDATE SELECTION
const Int_t nElectronCandidateMax = 100;
Int_t nElectronCandidate;
Float_t ElectronCandidate_pt[nElectronCandidateMax];
Float_t ElectronCandidate_eta[nElectronCandidateMax];
Float_t ElectronCandidate_phi[nElectronCandidateMax];
Int_t ElectronCandidate_photonIdx[nElectronCandidateMax];
Int_t ElectronCandidate_isotrackIdx[nElectronCandidateMax];

//-> MUON SELECTION
const Int_t nMuonMax = 100;
Int_t nMuon;
Float_t MuonSel_pt[nMuonMax];
Float_t MuonSel_eta[nMuonMax];




/////////////////////////////////////// OUTPUT //////////////////////////////////////

TFile *file_out;
TTree *tree_out;


//=======================================================================================================================================================================================================================//
class LongLivedAnalysis : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit LongLivedAnalysis(const edm::ParameterSet&);
      ~LongLivedAnalysis();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      std::string output_filename;
      edm::ParameterSet parameters;
      edm::EDGetTokenT<edm::View<pat::Muon> >  theMuonCollection;   
      edm::EDGetTokenT<edm::View<pat::Photon> > thePhotonCollection;
      edm::EDGetTokenT<edm::View<pat::IsolatedTrack> >  theIsoTrackCollection;
      edm::EDGetTokenT<edm::View<reco::Vertex> > thePrimaryVertexCollection;

};
//=======================================================================================================================================================================================================================//




//=======================================================================================================================================================================================================================//
LongLivedAnalysis::LongLivedAnalysis(const edm::ParameterSet& iConfig)
{
   usesResource("TFileService");
   
   parameters = iConfig;
   theMuonCollection = consumes<edm::View<pat::Muon> >  (parameters.getParameter<edm::InputTag>("MuonCollection"));
   thePhotonCollection = consumes<edm::View<pat::Photon> > (parameters.getParameter<edm::InputTag>("PhotonCollection"));
   theIsoTrackCollection = consumes<edm::View<pat::IsolatedTrack> >  (parameters.getParameter<edm::InputTag>("IsoTrackCollection"));
   thePrimaryVertexCollection = consumes<edm::View<reco::Vertex> >  (parameters.getParameter<edm::InputTag>("PrimaryVertexCollection"));

 
}
//=======================================================================================================================================================================================================================//




//=======================================================================================================================================================================================================================//
LongLivedAnalysis::~LongLivedAnalysis()
{

}
//=======================================================================================================================================================================================================================//



//=======================================================================================================================================================================================================================//
void LongLivedAnalysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   /////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////// MAIN CODE /////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////



   //////////////////////////////// GET THE COLLECTIONS ////////////////////////////////
   edm::Handle<edm::View<pat::Muon> > muons;
   edm::Handle<edm::View<pat::Photon> > photons;
   edm::Handle<edm::View<pat::IsolatedTrack> > isotracks;
   edm::Handle<edm::View<reco::Vertex> > primaryvertices;

   iEvent.getByToken(theMuonCollection, muons);
   iEvent.getByToken(thePhotonCollection, photons);
   iEvent.getByToken(theIsoTrackCollection, isotracks);
   iEvent.getByToken(thePrimaryVertexCollection, primaryvertices);



   ////////////////////////////// PRIMARY VERTEX FEATURES //////////////////////////////

   //Int_t nPV = primaryvertices->size();
   //const reco::Vertex &pv = (*primaryvertices)[0];

   //const std::vector<reco::Track> &tk =  pv.refittedTracks();


   ///////////////////////////////// ISOTRACK FEATURES /////////////////////////////////

   std::vector<int> iT; // track indexes
//   nIsoTrack = isotracks->size();

   for (size_t i = 0; i < isotracks->size(); i++){

       const pat::IsolatedTrack & isotrack = (*isotracks)[i];
       if (goodTrack(isotrack)){ iT.push_back(i); }

   }



   // Loop over the isotracks
   for (size_t i = 0; i < iT.size(); ++i){

       
       const pat::IsolatedTrack & isotrack = (*isotracks)[iT.at(i)];

       // Basic features:
       IsoTrackSel_pt[i] = isotrack.pt();
       IsoTrackSel_eta[i] = isotrack.eta();
       IsoTrackSel_phi[i] = isotrack.phi();
       
       // Isolation info:
       
       const pat::PFIsolation &pfiso = isotrack.pfIsolationDR03();
       const pat::PFIsolation &minipfiso = isotrack.miniPFIsolation();

       IsoTrackSel_pfIsolationDR03[i] = pfiso.chargedHadronIso() + pfiso.neutralHadronIso() + pfiso.photonIso() + pfiso.puChargedHadronIso();
       IsoTrackSel_miniPFIsolation[i] = minipfiso.chargedHadronIso() + minipfiso.neutralHadronIso() + minipfiso.photonIso() + minipfiso.puChargedHadronIso();


       // Quality info:
       IsoTrackSel_isHighPurityTrack[i] = isotrack.isHighPurityTrack();

       // Impact parameter info:
       IsoTrackSel_dxy[i] = isotrack.dxy();
       IsoTrackSel_dxyError[i] = isotrack.dxyError();
       IsoTrackSel_dz[i] = isotrack.dz();
       IsoTrackSel_dzError[i] = isotrack.dzError();
       IsoTrackSel_dxySignificance[i] = fabs(isotrack.dxy())/isotrack.dxyError();

       // Hit info:
       //
       const reco::HitPattern &hits = isotrack.hitPattern();

       IsoTrackSel_numberOfValidTrackerHits[i] = hits.numberOfValidTrackerHits();
       IsoTrackSel_numberOfValidPixelHits[i] = hits.numberOfValidPixelHits();

   }


   ////////////////////////////////// PHOTON FEATURES //////////////////////////////////
   
   std::vector<int> iP; // photon indexes


   // Select good photons
   for (size_t i = 0; i < photons->size(); ++i){
       
       const pat::Photon & photon = (*photons)[i];

       if (goodPhoton(photon)) 
       { 
           iP.push_back(i); 
       }

   }

   // Sort good lepton indexes by pt
   std::sort( std::begin(iP), std::end(iP), [&](int i1, int i2){ return photons->at(i1).et() < photons->at(i2).et(); });


   nPhoton = iP.size();
   // Loop over the good photons
   for (size_t i = 0; i < iP.size(); ++i){

       const pat::Photon & photon = (*photons)[iP.at(i)];

       PhotonSel_et[i] = photon.et();
       PhotonSel_eta[i] = photon.eta();
       PhotonSel_phi[i] = photon.phi();
       PhotonSel_hadronicOverEm[i] = photon.hadronicOverEm();
       PhotonSel_full5x5_sigmaIetaIeta[i] = photon.full5x5_sigmaIetaIeta();
       PhotonSel_isEB[i] = photon.isEB();
       PhotonSel_isEE[i] = photon.isEE();


   }



   /////////////////////////////////// MUON FEATURES ///////////////////////////////////

   nMuon = muons->size();

   // Loop over the muons
   for (size_t i = 0; i < muons->size(); ++i){

       const pat::Muon & muon = (*muons)[i];

       MuonSel_pt[i] = muon.pt();
       MuonSel_eta[i] = muon.eta(); 
   }



   ///////////////////////////////// ELECTRON CANDIDATES ///////////////////////////////

   int e = 0;

   for (size_t i = 0; i < iT.size(); ++i){

       const pat::IsolatedTrack & isotrack = (*isotracks)[iT.at(i)];
       std::cout << "track" << "\t" << i << std::endl;
       for (size_t j = 0; j < iP.size(); ++j){

           std::cout << "cluster" << "\t" << j << std::endl;

           const pat::Photon & photon = (*photons)[iP.at(j)];
           float deltaPhi = fabs(photon.phi() - isotrack.phi());
           float deltaEta = fabs(photon.eta() - isotrack.eta());
           float deltaR = sqrt(deltaPhi*deltaPhi + deltaEta*deltaEta);

           if (deltaR < 0.1){

               ElectronCandidate_pt[e] = photon.et();
               ElectronCandidate_phi[e] = isotrack.phi();
               ElectronCandidate_eta[e] = isotrack.eta();
               ElectronCandidate_photonIdx[e] = j;
               std::cout << "photonIdx" << "\t" << ElectronCandidate_photonIdx[e] << std::endl;
               ElectronCandidate_isotrackIdx[e] = i;
               e++;

           }           

           std::cout << "e" << "\t" << e << std::endl;

       }

   }
 
   nElectronCandidate = e;



   /////////////////////////////////// FILL THE TREE ///////////////////////////////////
   tree_out->Fill();

}
//=======================================================================================================================================================================================================================//




//=======================================================================================================================================================================================================================//
void LongLivedAnalysis::beginJob()
{

    // Output file definition
    output_filename = parameters.getParameter<std::string>("nameOfOutput");
    file_out = new TFile(output_filename.c_str(), "RECREATE");
    file_out->cd();
    
    // Output Tree definition
    tree_out = new TTree("Events", "Events");


    ///////////////////////////////// ISOTRACK BRANCHES /////////////////////////////////
    
    tree_out->Branch("nIsoTrack", &nIsoTrack, "nIsoTrack/I");
    tree_out->Branch("IsoTrackSel_pt", IsoTrackSel_pt, "IsoTrackSel_pt[nIsoTrack]/F");
    tree_out->Branch("IsoTrackSel_eta", IsoTrackSel_eta, "IsoTrackSel_eta[nIsoTrack]/F");
    tree_out->Branch("IsoTrackSel_phi", IsoTrackSel_phi, "IsoTrackSel_phi[nIsoTrack]/F");
    tree_out->Branch("IsoTrackSel_dxy", IsoTrackSel_dxy, "IsoTrackSel_dxy[nIsoTrack]/F");
    tree_out->Branch("IsoTrackSel_dxyError", IsoTrackSel_dxyError, "IsoTrackSel_dxyError[nIsoTrack]/F");
    tree_out->Branch("IsoTrackSel_dz", IsoTrackSel_dz, "IsoTrackSel_dz[nIsoTrack]/F");
    tree_out->Branch("IsoTrackSel_dzError", IsoTrackSel_dzError, "IsoTrackSel_dzError[nIsoTrack]/F");
    tree_out->Branch("IsoTrackSel_dxySignificance", IsoTrackSel_dxySignificance, "IsoTrackSel_dxySignificance[nIsoTrack]/F");
    tree_out->Branch("IsoTrackSel_pfIsolationDR03", IsoTrackSel_pfIsolationDR03, "IsoTrackSel_pfIsolationDR03[nIsoTrack]/F");
    tree_out->Branch("IsoTrackSel_miniPFIsolation", IsoTrackSel_miniPFIsolation, "IsoTrackSel_miniPFIsolation[nIsoTrack]/F");
    tree_out->Branch("IsoTrackSel_isHighPurityTrack", IsoTrackSel_isHighPurityTrack, "IsoTrackSel_isHighPurityTrack[nIsoTrack]/I");
    tree_out->Branch("IsoTrackSel_numberOfValidTrackerHits", IsoTrackSel_numberOfValidTrackerHits, "IsoTrackSel_numberOfValidTrackerHits[nIsoTrack]/I");
    tree_out->Branch("IsoTrackSel_numberOfValidPixelHits", IsoTrackSel_numberOfValidPixelHits, "IsoTrackSel_numberOfValidPixelHits[nIsoTrack]/I");

    
    ////////////////////////////////// PHOTON BRANCHES //////////////////////////////////

    tree_out->Branch("nPhoton", &nPhoton, "nPhoton/I");
    tree_out->Branch("PhotonSel_et", PhotonSel_et, "PhotonSel_et[nPhoton]/F");
    tree_out->Branch("PhotonSel_eta", PhotonSel_eta, "PhotonSel_eta[nPhoton]/F");
    tree_out->Branch("PhotonSel_phi", PhotonSel_phi, "PhotonSel_phi[nPhoton]/F");
    tree_out->Branch("PhotonSel_hadronicOverEm", PhotonSel_hadronicOverEm, "PhotonSel_hadronicOverEm[nPhoton]/F");
    tree_out->Branch("PhotonSel_full5x5_sigmaIetaIeta", PhotonSel_full5x5_sigmaIetaIeta, "PhotonSel_full5x5_sigmaIetaIeta[nPhoton]/F");
    tree_out->Branch("PhotonSel_isEB", PhotonSel_isEB, "PhotonSel_isEB[nPhoton]/I");
    tree_out->Branch("PhotonSel_isEE", PhotonSel_isEE, "PhotonSel_isEE[nPhoton]/I");

    /////////////////////////////////// MUON BRANCHES ///////////////////////////////////

    tree_out->Branch("nMuon", &nMuon, "nMuon/I");
    tree_out->Branch("MuonSel_pt", MuonSel_pt, "MuonSel_pt[nMuon]/F");
    tree_out->Branch("MuonSel_eta", MuonSel_eta, "MuonSel_pt[nMuon]/F");


    //////////////////////////// ELECTRON CANDIDATE BRANCHES ////////////////////////////
    tree_out->Branch("nElectronCandidate", &nElectronCandidate, "nElectronCandidate/I");
    tree_out->Branch("ElectronCandidate_pt", ElectronCandidate_pt, "ElectronCandidate[nElectronCandidate]/F");
    tree_out->Branch("ElectronCandidate_eta", ElectronCandidate_eta, "ElectronCandidate[nElectronCandidate]/F");    
    tree_out->Branch("ElectronCandidate_phi", ElectronCandidate_phi, "ElectronCandidate[nElectronCandidate]/F");
    tree_out->Branch("ElectronCandidate_photonIdx", ElectronCandidate_photonIdx, "ElectronCandidate_photonIdx[nElectronCandidate]/I");
    tree_out->Branch("ElectronCandidate_isotrackIdx", ElectronCandidate_isotrackIdx, "ElectronCandidate_isotrackIdx[nElectronCandidate]/I");




}
//=======================================================================================================================================================================================================================//




//=======================================================================================================================================================================================================================//
void LongLivedAnalysis::endJob() 
{

    tree_out->Write();
    file_out->Close();

}
//=======================================================================================================================================================================================================================//




//=======================================================================================================================================================================================================================//
void LongLivedAnalysis::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//=======================================================================================================================================================================================================================//





DEFINE_FWK_MODULE(LongLivedAnalysis);
