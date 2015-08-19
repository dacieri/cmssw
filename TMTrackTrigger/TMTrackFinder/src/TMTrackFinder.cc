


#include "TMTrackTrigger/TMTrackFinder/interface/TMTrackFinder.h"



TMTrackFinder::TMTrackFinder(const edm::ParameterSet& iConfig)
{

  conf_ = iConfig;
  hough_print_ = iConfig.getParameter<bool>("HoughPrint");
  debug_ = iConfig.getParameter<bool>("Debug");
  pt_cut_ = iConfig.getParameter<double>("StubMinPt");
  eta_cut_ = iConfig.getParameter<double>("StubEtaRange");

  eta_regions_ = iConfig.getParameter<std::vector<double> >("EtaRegions");
  zError_ = iConfig.getParameter<double>("BeamErrorZ");

  beta_range_ = iConfig.getParameter<double>("BetaRange");
  hough_pt_ = iConfig.getParameter<double>("MinHoughPt");
  hough_bins_x_ = iConfig.getParameter<int>("HoughBinsX");
  hough_bins_y_ = iConfig.getParameter<int>("HoughBinsY");
  sample_type_ = iConfig.getParameter<int>("SampleType");
  pt_low_ = iConfig.getParameter<double>("PtLow");
  pt_high_ = iConfig.getParameter<double>("PtHigh");

  
}



TMTrackFinder::~TMTrackFinder()
{

}



void TMTrackFinder::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{




  iSetup.get<StackedTrackerGeometryRecord>().get(StackedGeometryHandle);
  theStackedGeometry_ = StackedGeometryHandle.product();

  // tracking particles
  iEvent.getByLabel("mix", "MergedTrackTruth", TrackingParticleHandle_);
  
  // all clusters (> width 4)
  iEvent.getByLabel("TTClustersFromPixelDigis", "ClusterInclusive", TTClusterInclusiveHandle_);
  
  // cluster MC truth
  iEvent.getByLabel("TTClusterAssociatorFromPixelDigis", "ClusterAccepted", MCTruthTTClusterHandle_);
  
  // all stubs (passing bandwidth constraints)
  iEvent.getByLabel("TTStubsFromPixelDigis", "StubAccepted", TTStubHandle_);
  
  // stub MC truth
  iEvent.getByLabel("TTStubAssociatorFromPixelDigis", "StubAccepted", MCTruthTTStubHandle_);


  if(sample_type_==0){
  // RECO Muons
  iEvent.getByLabel("muons",RecoMuons_);

  //GEN Muons
  iEvent.getByLabel("genParticles",GenMuons_);
  }
  if(sample_type_==1){
 // RECO Muons
  iEvent.getByLabel("gsfElectrons",RecoElectrons_);

  //GEN Muons
  iEvent.getByLabel("selectElectrons",GenElectrons_);
  }




  TMTrackFinderAlgorithm trackfinder(TTStubHandle_,MCTruthTTStubHandle_,theStackedGeometry_,conf_, fs);


  TMTrackFinderAlgorithm::SegmentCells accepted_cells = trackfinder.getAcceptedCells();
  TMTrackFinderAlgorithm::SegmentCells filtered_cells = trackfinder.getFilteredCells();


  
  // -------------- total efficiencies per event -------------------

  TPs numTP;

  find_tracking_particles(filtered_cells,numTP);
  
  efficiency(numTP);
  if(sample_type_==0){
    std::cout << "Analyzing Muons" <<std::endl;
    reconstruction0(RecoMuons_);
    generation(GenMuons_);
  }

  if(sample_type_==1){
    reconstruction1(RecoElectrons_);
    generation(GenElectrons_);
  }


  // ---------------- trigger tower rates --------------------------


  for ( int eta_region=0; eta_region<5; eta_region++ ) {

    for ( int beta_segment=0; beta_segment<64; beta_segment++ ) {


      double beta = beta_segment * 0.1 - 3.2;

      TMTrackFinderAlgorithm::Segment segment(eta_region,beta);




      TMTrackFinderAlgorithm::SegmentCells::iterator acc_cells = accepted_cells.find(segment);

      if ( acc_cells!=accepted_cells.end() ) {

	h_acc_cells[eta_region]->Fill(acc_cells->second.size());
	
	TMTrackFinderAlgorithm::Cells::iterator cell = acc_cells->second.begin();
	for ( ; cell!=acc_cells->second.end(); cell++) {
	  h_stubs_acc_cells[eta_region]->Fill(cell->size());
	}
    
      } else {

	h_acc_cells[eta_region]->Fill(0);

      }


      TMTrackFinderAlgorithm::SegmentCells::iterator filt_cells = filtered_cells.find(segment);

      if ( filt_cells!=filtered_cells.end() ) {

	h_filt_cells[eta_region]->Fill(filt_cells->second.size());
	
	TMTrackFinderAlgorithm::Cells::iterator cell = filt_cells->second.begin();
	for ( ; cell!=filt_cells->second.end(); cell++) {
	  h_stubs_filt_cells[eta_region]->Fill(cell->size());
	}
    
      } else {

	h_filt_cells[eta_region]->Fill(0);

      }


    }
  }
      

}



void TMTrackFinder::beginJob()
{

  
  stop = 0; 

  lessthanten =0;

  h_acc_cells0 = fs->make<TH1D>("h_acc_cells0","", 200,0,200);
  h_acc_cells.push_back(h_acc_cells0);
  h_acc_cells1 = fs->make<TH1D>("h_acc_cells1","", 200,0,200);
  h_acc_cells.push_back(h_acc_cells1);
  h_acc_cells2 = fs->make<TH1D>("h_acc_cells2","", 200,0,200);
  h_acc_cells.push_back(h_acc_cells2);
  h_acc_cells3 = fs->make<TH1D>("h_acc_cells3","", 200,0,200);
  h_acc_cells.push_back(h_acc_cells3);
  h_acc_cells4 = fs->make<TH1D>("h_acc_cells4","", 200,0,200);
  h_acc_cells.push_back(h_acc_cells4);

  h_stubs_acc_cells0 = fs->make<TH1D>("h_stubs_acc_cells0","", 30,0,30);
  h_stubs_acc_cells.push_back(h_stubs_acc_cells0);
  h_stubs_acc_cells1 = fs->make<TH1D>("h_stubs_acc_cells1","", 30,0,30);
  h_stubs_acc_cells.push_back(h_stubs_acc_cells1);
  h_stubs_acc_cells2 = fs->make<TH1D>("h_stubs_acc_cells2","", 30,0,30);
  h_stubs_acc_cells.push_back(h_stubs_acc_cells2);
  h_stubs_acc_cells3 = fs->make<TH1D>("h_stubs_acc_cells3","", 30,0,30);
  h_stubs_acc_cells.push_back(h_stubs_acc_cells3);
  h_stubs_acc_cells4 = fs->make<TH1D>("h_stubs_acc_cells4","", 30,0,30);
  h_stubs_acc_cells.push_back(h_stubs_acc_cells4);

  h_filt_cells0 = fs->make<TH1D>("h_filt_cells0","", 200,0,200);
  h_filt_cells.push_back(h_filt_cells0);
  h_filt_cells1 = fs->make<TH1D>("h_filt_cells1","", 200,0,200);
  h_filt_cells.push_back(h_filt_cells1);
  h_filt_cells2 = fs->make<TH1D>("h_filt_cells2","", 200,0,200);
  h_filt_cells.push_back(h_filt_cells2);
  h_filt_cells3 = fs->make<TH1D>("h_filt_cells3","", 200,0,200);
  h_filt_cells.push_back(h_filt_cells3);
  h_filt_cells4 = fs->make<TH1D>("h_filt_cells4","", 200,0,200);
  h_filt_cells.push_back(h_filt_cells4);

  h_stubs_filt_cells0 = fs->make<TH1D>("h_stubs_filt_cells0","", 30,0,30);
  h_stubs_filt_cells.push_back(h_stubs_filt_cells0);
  h_stubs_filt_cells1 = fs->make<TH1D>("h_stubs_filt_cells1","", 30,0,30);
  h_stubs_filt_cells.push_back(h_stubs_filt_cells1);
  h_stubs_filt_cells2 = fs->make<TH1D>("h_stubs_filt_cells2","", 30,0,30);
  h_stubs_filt_cells.push_back(h_stubs_filt_cells2);
  h_stubs_filt_cells3 = fs->make<TH1D>("h_stubs_filt_cells3","", 30,0,30);
  h_stubs_filt_cells.push_back(h_stubs_filt_cells3);
  h_stubs_filt_cells4 = fs->make<TH1D>("h_stubs_filt_cells4","", 30,0,30);
  h_stubs_filt_cells.push_back(h_stubs_filt_cells4);

  h_cells_pt = fs->make<TH1D>("h_cells_pt","", 500,pt_low_,pt_high_);
  h_tracks_pt = fs->make<TH1D>("h_tracks_pt","", 500,pt_low_,pt_high_);

  h_reco_pt = fs->make<TH1D>("h_reco_pt","", 500,pt_low_,pt_high_);
  h_gen_pt = fs->make<TH1D>("h_gen_pt","", 500,pt_low_,pt_high_);
  h_eff0_pt = fs->make<TH1D>("h_eff0_pt","Efficiency Stubs/RECO", 500,5,1000);
  h_eff1_pt = fs->make<TH1D>("h_eff1_pt","Efficiency Stubs/GEN", 500,5,1000);



  h_cells_etaphi = fs->make<TH2D>("h_cells_etaphi","", 160,-3.2,3.2, 175,-3.5,3.5);
  h_tracks_etaphi = fs->make<TH2D>("h_tracks_etaphi","", 160,-3.2,3.2, 175,-3.5,3.5);
  h_eff0 = fs->make<TH2D>("h_eff0","Efficiency Stubs/RECO", 160,-3.2,3.2, 175,-3.5,3.5);
  h_eff1 = fs->make<TH2D>("h_eff1","Efficiency Stubs/Matched Stubs", 160,-3.2,3.2, 175,-3.5,3.5);
  h_eff2 = fs->make<TH2D>("h_eff2","Efficiency RECO/Gen", 160,-3.2,3.2, 175,-3.5,3.5);
  h_stubs_good = fs->make<TH1D>("h_stubs_good","", 15,0,15);
  h_stubs_bad = fs->make<TH1D>("h_stubs_bad","", 15,0,15);
  h_cells_fake = fs->make<TH1D>("h_cells_fake","", 300,0,300);
  h_cells_duplicate = fs->make<TH1D>("h_cells_duplicate","", 300,0,300);
  h_cells_eta = fs->make<TH1D>("h_cells_eta","", 160,-3.2,3.2);
  h_tracks_eta = fs->make<TH1D>("h_tracks_eta","", 160,-3.2,3.2);
  h_eff0_eta = fs->make<TH1D>("h_eff0_eta","Efficiency Stubs/RECO", 160,-3.2,3.2);
  h_eff0_phi = fs->make<TH1D>("h_eff0_phi","Efficiency Stubs/RECO", 175,-3.5,3.5);  
  h_eff1_eta = fs->make<TH1D>("h_eff1_eta","Efficiency Stubs/Matched Stubs", 160,-3.2,3.2);
  h_eff1_phi = fs->make<TH1D>("h_eff1_phi","Efficiency Stubs/Matched Stubs", 175,-3.5,3.5);  
  h_eff2_eta = fs->make<TH1D>("h_eff2_eta","Efficiency RECO/Gen", 160,-3.2,3.2);
  h_eff2_phi = fs->make<TH1D>("h_eff2_phi","Efficiency RECO/Gen", 175,-3.5,3.5);  

  h_cells_phi = fs->make<TH1D>("h_cells_phi","", 175,-3.5,3.5);  
  h_tracks_phi = fs->make<TH1D>("h_tracks_phi","", 175,-3.5,3.5); 
  h_reco_eta = fs->make<TH1D>("h_reco_eta","", 160,-3.2,3.2);
  h_reco_etaphi = fs->make<TH2D>("h_reco_etaphi","", 160,-3.2,3.2, 175,-3.5,3.5);  
  h_reco_phi = fs->make<TH1D>("h_reco_phi","", 175,-3.5,3.5); 
  h_gen_eta = fs->make<TH1D>("h_gen_eta","", 160,-3.2,3.2);
  h_gen_etaphi = fs->make<TH2D>("h_gen_etaphi","", 160,-3.2,3.2, 175,-3.5,3.5);  
  h_gen_phi = fs->make<TH1D>("h_gen_phi","", 175,-3.5,3.5); 
  h_goodstubs =  fs->make<TH1D>("h_goodstubs","", 15,0,15);

  h_barcode = fs->make<TH1D>("h_barcode","", 20,0,20);
  stubs3d = fs->make<TH3D>("h_stubs3d","",300,-150.,150.,300,-150.,150.,600,-300.,300.);
  stub_zr_10= fs->make<TH2D>("stub_zr_10","", 6000,-300.,300, 1200,0,120);
  stub_zr_11= fs->make<TH2D>("stub_zr_11","", 6000,-300.,300, 1200,0,120);
  stub_zr_12= fs->make<TH2D>("stub_zr_12","", 6000,-300.,300, 1200,0,120);
  stub_zr_13= fs->make<TH2D>("stub_zr_13","", 6000,-300.,300, 1200,0,120);
  stub_zr_14= fs->make<TH2D>("stub_zr_14","", 6000,-300.,300, 1200,0,120);
  h_overlap =  fs->make<TH1D>("h_overlap","", 15,0,15);
  h_dupstubs =  fs->make<TH1D>("h_dupstubs","", 15,0,15);
 }


void TMTrackFinder::endJob() 
{

  /*  
  h_eff0->Divide(h_cells_etaphi,h_reco_etaphi,1,1);
  h_eff0_eta->Sumw2();
  h_eff0_phi->Sumw2();
  h_eff0_eta->Divide(h_cells_eta,h_reco_eta,1,1);
  h_eff0_phi->Divide(h_cells_phi,h_reco_phi,1,1);


  // Uncomment here to fit the eta efficiency distribution
/*
  TF1 *fa = new TF1("fa","[0]",-2.2,2.2);
  fa->SetParameter(0,.95);
  h_eff0_eta->Fit("fa","RSF");
  TFitResultPtr res_eta = h_eff0_eta->Fit("fa","RSF");
  Double_t eff_eta = res_eta->Value(0);
  Double_t deff_eta = res_eta->ParError(0);
  std::cout << "efficiency 1 in eta = "<< eff_eta <<" +/- "<< deff_eta << std::endl;

  TF1 *fb = new TF1("fb","[0]",-3.14,3.14);
  fb->SetParameter(0,.95);
  h_eff0_phi->Fit("fb","RSF");
  TFitResultPtr res_phi = h_eff0_phi->Fit("fb","RSF");
  Double_t eff_phi = res_phi->Value(0);
  Double_t deff_phi = res_phi->ParError(0);
  std::cout << "efficiency 1 in phi = "<< eff_phi <<" +/- "<< deff_phi << std::endl;

  fa->SetParameter(0,.95);
  h_eff1_eta->Fit("fa","RSF");
  TFitResultPtr res1_eta = h_eff1_eta->Fit("fa","RSF");
  Double_t eff1_eta = res1_eta->Value(0);
  Double_t deff1_eta = res1_eta->ParError(0);
  std::cout << "efficiency 2 in eta = "<< eff1_eta <<" +/- "<< deff1_eta << std::endl;

  fb->SetParameter(0,.95);
  h_eff1_phi->Fit("fb","RSF");
  TFitResultPtr res1_phi = h_eff1_phi->Fit("fb","RSF");
  Double_t eff1_phi = res1_phi->Value(0);
  Double_t deff1_phi = res1_phi->ParError(0);
  std::cout << "efficiency 2 in phi = "<< eff1_phi <<" +/- "<< deff1_phi << std::endl;

  h_eff1->Divide(h_cells_etaphi,h_tracks_etaphi,1,1);
  h_eff1_eta->Divide(h_cells_eta,h_tracks_eta,1,1);
  h_eff1_phi->Divide(h_cells_phi,h_tracks_phi,1,1);
  h_eff2->Divide(h_reco_etaphi,h_gen_etaphi,1,1);
  h_eff2_eta->Divide(h_reco_eta,h_gen_eta,1,1);
  h_eff2_phi->Divide(h_reco_phi,h_gen_phi,1,1);
  h_eff0_pt->Divide(h_cells_pt,h_reco_pt,1,1);
  h_eff1_pt->Divide(h_cells_pt,h_gen_pt,1,1);
*/
}






void TMTrackFinder::find_tracking_particles(TMTrackFinderAlgorithm::SegmentCells& segments, TPs& numTP)
{  

  int nfake = 0;
  int nduplicate = 0;
  int ntrue = 0;
  int ntotal = 0;
  int nstubs =0;
  int nsubevent =0; 
  Double_t X=0.,Y=0.,Z=0.,R=0.;

  TMTrackFinderAlgorithm::SegmentCells::iterator cells = segments.begin();

  for ( ; cells != segments.end(); cells++ ) {
    nsubevent++;
    TMTrackFinderAlgorithm::Cells::iterator cell = cells->second.begin();
    int nsubcell=0; 
    for ( ; cell!=cells->second.end(); cell++) {

      ntotal++;
      nsubcell++;
      std::map<TPptr,TMTrackFinderAlgorithm::Stubs> TPStubsMap;
      std::vector<TPs> accStubs;
      TPs theseTP; // TP's in this cell

      TMTrackFinderAlgorithm::Stubs::iterator itstub = cell->begin();
      
      for ( ; itstub!=cell->end(); itstub++) {
	

	TMTrackFinderAlgorithm::RefStub thisStub = itstub->ref;
	TMTrackFinderAlgorithm::extended_stub stub = *itstub;
	edm::Ref< edmNew::DetSetVector< TTCluster< Ref_PixelDigi_ > >, TTCluster< Ref_PixelDigi_ > > cluster0 = thisStub->getClusterRef(0);
	edm::Ref< edmNew::DetSetVector< TTCluster< Ref_PixelDigi_ > >, TTCluster< Ref_PixelDigi_ > > cluster1 = thisStub->getClusterRef(1);
	
	TPs TP0 = MCTruthTTClusterHandle_->findTrackingParticlePtrs(cluster0);
	TPs TP1 = MCTruthTTClusterHandle_->findTrackingParticlePtrs(cluster1);
	
	TPs thisTPstub; // TP's in this stub
	
	for ( unsigned int i=0; i<TP0.size(); i++ ) {
	  if (!TP0.at(i)) continue;
	  if ( std::find(thisTPstub.begin(), thisTPstub.end(), TP0.at(i)) == thisTPstub.end() ) thisTPstub.push_back(TP0.at(i));
	  if ( std::find(theseTP.begin(), theseTP.end(), TP0.at(i)) == theseTP.end() ) theseTP.push_back(TP0.at(i));
	  TPStubsMap[TP0.at(i)].push_back(stub);
	}
	for ( unsigned int i=0; i<TP1.size(); i++ ) {
	  if (!TP1.at(i)) continue;
	  if ( std::find(thisTPstub.begin(), thisTPstub.end(), TP1.at(i)) == thisTPstub.end() ) thisTPstub.push_back(TP1.at(i));
	  if ( std::find(theseTP.begin(), theseTP.end(), TP1.at(i)) == theseTP.end() ) theseTP.push_back(TP1.at(i));
	  TPStubsMap[TP1.at(i)].push_back(stub);
	}

	// list of unique TPs per stub for all stubs in cell
	accStubs.push_back(thisTPstub);
	
      }
      
      int goodstubs=0;
      bool anytracks=false;

      // list of unique TPs in entire cell
      for (unsigned int tp=0; tp<theseTP.size(); tp++) {
	TPptr thisTP = theseTP.at(tp);
	
	
	if (thisTP->pt()<hough_pt_) continue;
	int tpCnt=0;

	// counting # of stubs with TP = current TP
	for (unsigned int thistpvec=0; thistpvec<accStubs.size(); thistpvec++) {
	  bool found=false;
	  for (unsigned int thistp=0; thistp<accStubs.at(thistpvec).size(); thistp++) {
	    if(found) break;
	    if ( accStubs.at(thistpvec).at(thistp) == thisTP ) {
	      tpCnt++;
	      found=true;
	    }
	  }
	}

	// only care about 5 or more stubs for current TP
	if (tpCnt>=5) {
	  
	  std::vector<int> r_register(16,0);
	  for ( TMTrackFinderAlgorithm::Stubs::iterator it = TPStubsMap[thisTP].begin(); it!=TPStubsMap[thisTP].end(); it++) {
	    int rbin = int((it->r - 20.0) / 6.0);
	    r_register[rbin] = 1;
	  }
	  int rbins = std::accumulate(r_register.begin(),r_register.end(),0);
	  bool accept = ( rbins >= 5 ) ? true : false ;
	  
	  if (accept) {
	    
	    anytracks=true;
	    goodstubs = tpCnt;
        nstubs=1;
        int stubid=-1;
        for ( TMTrackFinderAlgorithm::Stubs::iterator it = TPStubsMap[thisTP].begin(); it!=TPStubsMap[thisTP].end(); it++) {
                if(stubid!= it->id){
                    stubid=it->id;
                    //std::cout << "Stubs #"<<it->barcode<<", id = "<< it->id<< ", rbin = " << int((it->r - 20.0) / 6.0)<<", barcode = "<< it->barcode <<", nstubs: "<<nstubs<<  std::endl;
                    nstubs++;
                 }

             }



        Int_t noverlap = -1, dupstubs = -1;
        int id = 0;
         uint32_t modId = 0;

        if(goodstubs>10 ){
        int num=-1;
        //std::cout << "Num. of goodstubs =  "<<goodstubs << std::endl;
             for ( TMTrackFinderAlgorithm::Stubs::iterator it = TPStubsMap[thisTP].begin(); it!=TPStubsMap[thisTP].end(); it++) {
                //std::cout << "Stubs #"<<num<<" position r = "<<it->r <<", z = " << it->z<<", id = "<< it->id<< ", rbin = " << int((it->r - 20.0) / 6.0)<<", barcode = "<< it->barcode << std::endl;
                //std::cout << "Stubs GlobalPoint"<<it->position.x()<< std::endl;
                
                if(num!=it->barcode){
                    num = it->barcode;
                    h_barcode->Fill(num);
                    
                    R= it->r;
                    Z= it->z;
                    //std::cout <<"Stub n. " << num << ", z = "<< it->z << ", R =  " << R <<", phi = "<< it->phi<<", id = "<< it->stub.getDetId().rawId()<<std::endl;
                    //std::cout << "Stubs Position " << it->position << ", id = " << it->id << std::endl;
                    stubs3d->Fill(X,Y,Z);
                    stub_zr_10->Fill(Z,R);
                    
                    if(goodstubs>11)
                        stub_zr_11->Fill(Z,R);
                    if(goodstubs>12)
                        stub_zr_12->Fill(Z,R);
                    if(goodstubs>13)
                        stub_zr_13->Fill(Z,R);
                    if(goodstubs>14)
                        stub_zr_14->Fill(Z,R);





                    stop++;
                

                if(id==it->id && modId!=it->stub.getDetId().rawId())
                	noverlap++;
                else
                	id=it->id;

                if(modId==it->stub.getDetId().rawId())
                	dupstubs++;
                else
                	modId=it->stub.getDetId().rawId();
                }      
            }
        }

     	//std::cout << "dupstubs =" << dupstubs << ", noverlap = " << noverlap;

     	h_dupstubs->Fill(dupstubs);
     	h_overlap->Fill(noverlap);




//        std::cout<<"More than 10 stubs: "<<stop <<", lessthanten = "<< lessthanten<<std::endl; 
        if ( std::find(numTP.begin(), numTP.end(), thisTP) == numTP.end() ) {
          numTP.push_back(thisTP);
          ntrue++;

          double eta = thisTP->eta();
              double phi = thisTP->phi();
              
              if(thisTP->pt()>3){
                 h_cells_etaphi->Fill(eta,phi);
                 h_cells_eta->Fill(eta);
                 h_cells_phi->Fill(phi);
              }
              
            }
            else nduplicate++;
          }
          
        }
          }
          if (!anytracks) nfake++;
          
          if (goodstubs) {
              h_goodstubs->Fill(nstubs);
              //std::cout<< "h_goodstubs Filled"<<std::endl;
              h_stubs_good->Fill(goodstubs);
              h_stubs_bad->Fill(cell->size()-goodstubs);
          }

        
          
          
        }
        
      }
      
      h_cells_fake->Fill(nfake);
      h_cells_duplicate->Fill(nduplicate);
      //  std::cout<<ntotal<<" "<<ntrue<<" "<<nfake<<" "<<nduplicate<<std::endl;
    }



    void TMTrackFinder::reconstruction0(const edm::Handle <std::vector<reco::Muon>>& Muons){
        for(std::vector<reco::Muon>::const_iterator itTrack = Muons->begin();
           itTrack != Muons->end();
           ++itTrack) {
              //  your code
              if(itTrack->pt()>3){
              h_reco_etaphi->Fill(itTrack->eta(),itTrack->phi());
              h_reco_eta->Fill(itTrack->eta());
              h_reco_phi->Fill(itTrack->phi());
              h_reco_pt->Fill(itTrack->pt());
        }
       }



    }


    void TMTrackFinder::reconstruction1(const edm::Handle <std::vector<reco::GsfElectron>>& Electrons){
        for(std::vector<reco::GsfElectron>::const_iterator itTrack = Electrons->begin();
           itTrack != Electrons->end();
           ++itTrack) {
              //  your code
              if(itTrack->pt()>3){
              h_reco_etaphi->Fill(itTrack->eta(),itTrack->phi());
              h_reco_eta->Fill(itTrack->eta());
              h_reco_phi->Fill(itTrack->phi());
            h_reco_pt->Fill(itTrack->pt());
        }
       }



    }





    void TMTrackFinder::generation(const edm::Handle <std::vector<reco::GenParticle>> &Gens){
        for(std::vector<reco::GenParticle>::const_iterator itTrack = Gens->begin();
           itTrack != Gens->end();
           ++itTrack) {
              //  your code
              if(itTrack->pt()>3){
              h_gen_etaphi->Fill(itTrack->eta(),itTrack->phi());
              h_gen_eta->Fill(itTrack->eta());
              h_gen_phi->Fill(itTrack->phi());
              h_gen_pt->Fill(itTrack->pt());
        }
       }



    }







    void TMTrackFinder::efficiency(TPs& numTP)
    {


      int eid = -10;
      int tid = -10;
      TPs denTP;

      int tpCnt = 0;
      for ( std::vector< TrackingParticle >::const_iterator iterTP = TrackingParticleHandle_->begin(); iterTP != TrackingParticleHandle_->end(); ++iterTP ) {
        
        TPptr tempTPPtr( TrackingParticleHandle_, tpCnt++ );

        if (tempTPPtr->pt()<hough_pt_) continue;

        std::vector<int> r_register(16,0);
        
        std::vector<SimTrack> g4tracks = tempTPPtr->g4Tracks();
        std::vector<SimTrack>::const_iterator iterST = g4tracks.begin();

        eid = tempTPPtr->eventId().event();

        for ( ; iterST != g4tracks.end(); iterST++) {
          
          tid = iterST->trackId();

          std::vector< edm::Ref< edmNew::DetSetVector< TTStub< Ref_PixelDigi_ > >, TTStub< Ref_PixelDigi_ > > > theseStubs = MCTruthTTStubHandle_->findTTStubRefs( tempTPPtr );
          for ( unsigned int js = 0; js < theseStubs.size(); js++ )
        {

          GlobalPoint pos = theStackedGeometry_->findGlobalPosition(&(*theseStubs.at(js)));

          if (pos.eta()<-2.55 || pos.eta()>2.55) continue;
          
          int rbin = int((pos.perp() - 20.0) / 6.0);
          r_register[rbin] = 1;

        }
        }

        int rbins = std::accumulate(r_register.begin(),r_register.end(),0);
        if (rbins>=5) {

          //if((eid==0)&&(tid<5)&&(tid>0)) {
        denTP.push_back(tempTPPtr);
        if(false)std::cout<<eid<<" "<<tid<<" "<<tempTPPtr->pt()<<std::endl;
        
        double eta = tempTPPtr->eta();
        double phi = tempTPPtr->phi();
        
      //  if(tempTPPtr->pt()>9.8 && tempTPPtr->pt()<10.2){
        h_tracks_etaphi->Fill(eta,phi);
        h_tracks_eta->Fill(eta);
        h_tracks_phi->Fill(phi);
        //    }
        }
          
      }
      


      for ( TPs::iterator iTP = denTP.begin(); iTP != denTP.end(); ++iTP ) {

        h_tracks_pt->Fill((*iTP)->pt());
        
        //if (std::find(numTP.begin(), numTP.end(), (*iTP)) == numTP.end()) {
        //std::cout<<"TP not found "<<(*iTP)->pt()<<std::endl;
        //}
        
      }
      
      for ( TPs::iterator iTP = numTP.begin(); iTP != numTP.end(); ++iTP ) {
        
        h_cells_pt->Fill((*iTP)->pt());
        
      } 

    }




    // ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
    void TMTrackFinder::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
      //The following says we do not know what parameters are allowed so do no validation
      // Please change this to state exactly what you do use, even if it is no parameters
      edm::ParameterSetDescription desc;
      desc.setUnknown();
      descriptions.addDefault(desc);
    }

    //define this as a plug-in
    DEFINE_FWK_MODULE(TMTrackFinder);
