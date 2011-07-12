
#include <exception>
#include <vector>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TChain.h"
#include "TObject.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TTree.h"
#include "TF1.h"
#include "TGraphAsymmErrors.h"
#include "TPaveText.h"
#include "tdrstyle.C"

 class stSignal;
 namespace edm {class TriggerResults; class TriggerResultsByName; class InputTag;}
 namespace reco { class Vertex; class Track; class GenParticle;}
 namespace susybsm {class HSCParticle;}
 namespace fwlite  { class ChainEvent;}
 namespace trigger {class TriggerEvent;}


#if !defined(__CINT__) && !defined(__MAKECINT__)
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"


#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "AnalysisDataFormats/SUSYBSMObjects/interface/HSCParticle.h"
#include "FWCore/Common/interface/TriggerResultsByName.h"

#include "DataFormats/TrackerRecHit2D/interface/SiStripRecHit2D.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripMatchedRecHit2D.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHit.h"
#include "DataFormats/TrackerRecHit2D/interface/ProjectedSiStripRecHit2D.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripRecHit1D.h"

#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"


 using namespace fwlite;
 using namespace reco;
 using namespace edm;
 using namespace std;
 using namespace trigger;

#include "../../ICHEP_Analysis/Analysis_Samples.h"
#include "../../ICHEP_Analysis/Analysis_PlotFunction.h"


#endif

std::vector<stSignal> signals;
vector<string> JetMetSD_triggers;
vector<string> MuSD_triggers;
vector<string> All_triggers;
map<string,bool> All_mask;

class stPlot{
   public:
   TH1D* Histo;
   TH1D* HistoInc;
   TH1D* BetaCount;
   TH1D* BetaTotal;
   TH1D* BetaMuon;
   TH1D* BetaJet;

   stPlot(string SignalName){
      int numberofbins=JetMetSD_triggers.size()+MuSD_triggers.size()+1;
      Histo    = new TH1D((SignalName + "Abs").c_str(),(SignalName + "Abs").c_str(),numberofbins,0,numberofbins);
      HistoInc = new TH1D((SignalName + "Inc").c_str(),(SignalName + "Inc").c_str(),numberofbins,0,numberofbins);

      for(unsigned int i=0;i<MuSD_triggers.size();i++)    { Histo->GetXaxis()->SetBinLabel(i+1,MuSD_triggers[i].c_str());   }
      for(unsigned int i=0;i<JetMetSD_triggers.size();i++){ Histo->GetXaxis()->SetBinLabel(MuSD_triggers.size()+1+i,JetMetSD_triggers[i].c_str());   }
//      Histo->GetXaxis()->SetBinLabel(numberofbins-2,"Mu Paths");
//      Histo->GetXaxis()->SetBinLabel(numberofbins-1,"JetMET Paths");
      Histo->GetXaxis()->SetBinLabel(numberofbins,"Total");

      for(unsigned int i=0;i<MuSD_triggers.size();i++)    { HistoInc->GetXaxis()->SetBinLabel(i+1,MuSD_triggers[i].c_str());   }
      for(unsigned int i=0;i<JetMetSD_triggers.size();i++){ HistoInc->GetXaxis()->SetBinLabel(MuSD_triggers.size()+1+i,JetMetSD_triggers[i].c_str());   }
//      HistoInc->GetXaxis()->SetBinLabel(numberofbins-2,"Mu Paths");
//      HistoInc->GetXaxis()->SetBinLabel(numberofbins-1,"JetMET Paths");
      HistoInc->GetXaxis()->SetBinLabel(numberofbins,"Total");

      BetaCount    = new TH1D((SignalName + "BetaMuCount").c_str() ,(SignalName + "BetaCount").c_str()   ,20,0,1);   BetaCount  ->Sumw2();
      BetaTotal    = new TH1D((SignalName + "BetaTotal"  ).c_str() ,(SignalName + "BetaTotal").c_str()   ,20,0,1);   BetaTotal  ->Sumw2();
      BetaMuon     = new TH1D((SignalName + "BetaMuon"   ).c_str() ,(SignalName + "BetaMuon" ).c_str()   ,20,0,1);   BetaMuon   ->Sumw2();
      BetaJet      = new TH1D((SignalName + "BetaJet"    ).c_str() ,(SignalName + "BetaJet"  ).c_str()   ,20,0,1);   BetaJet    ->Sumw2();
   }

};


void TriggerStudy_Core(string SignalName, FILE* pFile, stPlot* plot);
double FastestHSCP(const fwlite::ChainEvent& ev);
bool IncreasedTreshold(const trigger::TriggerEvent& trEv, const edm::InputTag& InputPath, double NewThreshold, int NObjectAboveThreshold, bool averageThreshold=false);
void layout(vector<stPlot*>& plots, vector<string>& sigs, string name);
int JobIdToIndex(string JobId);


 

void TriggerStudy()
{
   system("mkdir pictures");

   setTDRStyle();
   gStyle->SetPadTopMargin   (0.06);
   gStyle->SetPadBottomMargin(0.10);
   gStyle->SetPadRightMargin (0.18);
   gStyle->SetPadLeftMargin  (0.14);
   gStyle->SetTitleSize(0.04, "XYZ");
   gStyle->SetTitleXOffset(1.1);
   gStyle->SetTitleYOffset(1.35);
   gStyle->SetPalette(1);
   gStyle->SetNdivisions(505,"X");

//   std::vector<stSignal> signals;
   GetSignalDefinition(signals);


   ///////////////////////////////////////////////////////
   JetMetSD_triggers.push_back("HLT_PFMHT150_v2");
//   JetMetSD_triggers.push_back("HLT_MET100_v1");

   MuSD_triggers.push_back("HLT_Mu24_v1");
   MuSD_triggers.push_back("HLT_DoubleMu7_v1");

   All_triggers.clear();
   for(unsigned int i=0;i<MuSD_triggers.size();i++)All_triggers.push_back(MuSD_triggers[i]);
   for(unsigned int i=0;i<JetMetSD_triggers.size();i++)All_triggers.push_back(JetMetSD_triggers[i]);
   for(unsigned int i=0;i<All_triggers.size();i++)All_mask[All_triggers[i]] = true;
   ///////////////////////////////////////////////////////
   FILE* pFile = fopen("Results.txt","w");

   stPlot** plots = new stPlot*[signals.size()];  
   for(unsigned int i=0;i<signals.size();i++){
      plots[i] = new stPlot(signals[i].Name);
      TriggerStudy_Core(signals[i].Name, pFile, plots[i] );
   }

   int Id;                              vector<stPlot*> objs;        vector<string> leg;

                                        objs.clear();                leg.clear();
   Id = JobIdToIndex("Gluino300");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("Gluino500");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("Gluino900");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   layout(objs, leg, "summary_Gluino");

                                        objs.clear();                leg.clear();
   Id = JobIdToIndex("Gluino300N");     objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("Gluino500N");     objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("Gluino900N");     objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   layout(objs, leg, "summary_GluinoN");

                                        objs.clear();                leg.clear();
   Id = JobIdToIndex("Stop200");        objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("Stop500");        objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("Stop800");        objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   layout(objs, leg, "summary_Stop");

                                        objs.clear();                leg.clear();
   Id = JobIdToIndex("Stop200N");       objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("Stop500N");       objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("Stop800N");       objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   layout(objs, leg, "summary_StopN");

                                        objs.clear();                leg.clear();
   Id = JobIdToIndex("GMStau156");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("GMStau247");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("GMStau308");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   layout(objs, leg, "summary_GMStau");

/*                                        objs.clear();                leg.clear();
   Id = JobIdToIndex("PPStau156");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("PPStau247");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("PPStau308");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   layout(objs, leg, "summary_PPStau");

                                        objs.clear();                leg.clear();
   Id = JobIdToIndex("DCStau121");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("DCStau242");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("DCStau302");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   layout(objs, leg, "summary_DCStau");
*/

/*
   int Id;                              vector<stPlot*> objs;        vector<string> leg;

                                        objs.clear();                leg.clear();
   Id = JobIdToIndex("Gluino300");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("Gluino500");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("Gluino800");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("Gluino900");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("Gluino1000");     objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   layout(objs, leg, "summary_Gluino");



                                        objs.clear();                leg.clear();
   Id = JobIdToIndex("Gluino600");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
                                        objs.push_back(plotsG600Z2);leg.push_back("Gluino600 Z2");
   Id = JobIdToIndex("Stop300");        objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   Id = JobIdToIndex("GMStau126");      objs.push_back(plots[Id]);   leg.push_back(signals[Id].Name);
   layout(objs, leg, "summary_Mixed");
*/

   fflush(pFile);
   fclose(pFile);

}

void TriggerStudy_Core(string SignalName, FILE* pFile, stPlot* plot)
{
   vector<string> fileNames;
   GetInputFiles(fileNames,SignalName);
   fwlite::ChainEvent ev(fileNames);

   unsigned int Total       = 0;
   unsigned int SDJetMET    = 0;
   unsigned int SDMu        = 0;
   unsigned int SDBoth      = 0;
   unsigned int SDJetMETInc = 0;
   unsigned int SDMuInc     = 0;
   unsigned int TrJetMET    = 0;
   unsigned int TrMu        = 0;
   unsigned int TrBoth      = 0;

   int MaxPrint = 0;
   printf("Progressing Bar              :0%%       20%%       40%%       60%%       80%%       100%%\n");
   printf("Looping on %10s        :", SignalName.c_str());
   int TreeStep = ev.size()/50;if(TreeStep==0)TreeStep=1;
   for(Long64_t e=0;e<ev.size();e++){
      if(e%TreeStep==0){printf(".");fflush(stdout);}
      ev.to(e);

      edm::TriggerResultsByName tr = ev.triggerResultsByName("HLT");
      if(!tr.isValid())continue;
      //for(unsigned int i=0;i<tr.size();i++){
      //   printf("Path %3i %50s --> %1i\n",i, tr.triggerName(i).c_str(),tr.accept(i));
      //}fflush(stdout);

      fwlite::Handle< trigger::TriggerEvent > trEvHandle;
      trEvHandle.getByLabel(ev,"hltTriggerSummaryAOD");
      trigger::TriggerEvent trEv = *trEvHandle;

      //for(unsigned int i=0;i<trEvHandle->sizeFilters();i++){
      //   if(strncmp(trEvHandle->filterTag(i).label().c_str(),"hltL1",5)==0)continue;
      //   printf("%i - %s\n",i,trEvHandle->filterTag(i).label().c_str());
      //}


      bool JetMetSD    = false;
      bool MuSD        = false;
      bool JetMetSDInc = false;
      bool MuSDInc     = false;
      bool JetMetTr    = false;
      bool MuTr        = false;


      unsigned int TrIndex_Unknown     = tr.size();

      bool AlreadyAccepted = false;

      for(unsigned int i=0;i<All_triggers.size();i++){
         vector<string>::iterator whereMuSD     = find(MuSD_triggers    .begin(), MuSD_triggers    .end(),All_triggers[i].c_str() );
         vector<string>::iterator whereJetMetSD = find(JetMetSD_triggers.begin(), JetMetSD_triggers.end(),All_triggers[i].c_str() );
  
 
         bool Accept = false;
         bool Accept2 = false;

           if(All_triggers[i]=="HLT_PFMHT150_v2"){
               if(TrIndex_Unknown != tr.triggerIndex("HLT_PFMHT150_v2")){
                   if(e<MaxPrint)printf("HLT_PFMHT150_v2\n");
                   Accept = tr.accept(tr.triggerIndex("HLT_PFMHT150_v2"));
                }else{
                   if(e<MaxPrint)printf("HLT_PFMHT150_v1\n");
                   Accept = tr.accept(tr.triggerIndex("HLT_PFMHT150_v1"));
                }
		//Accept2 = Accept;
                Accept2 = IncreasedTreshold(trEv, InputTag("hltPFMHT150Filter","","HLT"),160 , 1, false);

            }else{
               Accept = tr.accept(All_triggers[i].c_str());
	       Accept2 = Accept;
            }

         if(Accept                    ){plot->Histo   ->Fill(All_triggers[i].c_str(),1);}       
         if(Accept && !AlreadyAccepted){plot->HistoInc->Fill(All_triggers[i].c_str(),1);}

         if     (whereJetMetSD!=JetMetSD_triggers.end()){ JetMetSD |= Accept; if(!AlreadyAccepted)JetMetSDInc |= Accept;}
         else if(whereMuSD    !=MuSD_triggers.end())    { MuSD     |= Accept; if(!AlreadyAccepted)MuSDInc     |= Accept;}

         if     (whereJetMetSD!=JetMetSD_triggers.end()){ JetMetTr |= Accept2; }
         else if(whereMuSD    !=MuSD_triggers.end())    { MuTr     |= Accept2; }


         AlreadyAccepted |= Accept;
      }
      fflush(stdout);

//      JetMetTr = JetMetSD & ((rand()%100)<90);
//      MuTr     = MuSD     & ((rand()%100)<90);  

      Total++;
      if(JetMetSD)SDJetMET++;
      if(MuSD)SDMu++;
      if(JetMetSDInc)SDJetMETInc++;
      if(MuSDInc)SDMuInc++;
      if(JetMetSD||MuSD)SDBoth++;
      if(JetMetTr)TrJetMET++;
      if(MuTr)TrMu++;
      if(JetMetTr||MuTr)TrBoth++;

      double Beta = 1.0;
      if(SignalName!="Data")Beta = FastestHSCP(ev);
      plot->BetaCount->Fill(Beta);
      if(MuSD||JetMetSD)plot->BetaTotal->Fill(Beta);
      if(MuSD)plot->BetaMuon->Fill(Beta);
      if(JetMetSD)plot->BetaJet->Fill(Beta);

   }printf("\n");

//   fprintf(pFile,  "%15s --> JetMET = %5.2f%% (was %5.2f%%) Mu = %5.2f%% (was %5.2f%%) JetMET||Mu = %5.2f%% (%5.2f%%)\n",SignalName.c_str(), (100.0*TrJetMET)/Total, (100.0*SDJetMET)/Total, (100.0*TrMu)/Total, (100.0*SDMu)/Total, (100.0*TrBoth)/Total, (100.0*SDBoth)/Total);
//   fprintf(stdout, "%15s --> JetMET = %5.2f%% (was %5.2f%%) Mu = %5.2f%% (was %5.2f%%) JetMET||Mu = %5.2f%% (%5.2f%%)\n",SignalName.c_str(), (100.0*TrJetMET)/Total, (100.0*SDJetMET)/Total, (100.0*TrMu)/Total, (100.0*SDMu)/Total, (100.0*TrBoth)/Total, (100.0*SDBoth)/Total);


   fprintf(pFile,  "%15s --> MET = %5.2f%% (modified %5.2f%%) Mu = %5.2f%% (modified %5.2f%%) JetMET||Mu = %5.2f%% (%5.2f%%)\n",SignalName.c_str(), (100.0*SDJetMET)/Total, (100.0*TrJetMET)/Total, (100.0*SDMu)/Total, (100.0*TrMu)/Total, (100.0*SDBoth)/Total, (100.0*TrBoth)/Total);
   fprintf(stdout, "%15s --> MET = %5.2f%% (modified %5.2f%%) Mu = %5.2f%% (modified %5.2f%%) JetMET||Mu = %5.2f%% (%5.2f%%)\n",SignalName.c_str(), (100.0*SDJetMET)/Total, (100.0*TrJetMET)/Total, (100.0*SDMu)/Total, (100.0*TrMu)/Total, (100.0*SDBoth)/Total, (100.0*TrBoth)/Total);



//   printf("Total %i \n",Total);
//   plot->Histo->Fill("JetMET Paths",SDJetMET);
//   plot->Histo->Fill("Mu Paths",SDMu);
   plot->Histo->Fill("Total",SDBoth);
   plot->Histo->SetStats(0)  ;
   plot->Histo->LabelsOption("v");
   plot->Histo->Scale(100./Total);


//   plot->HistoInc->Fill("JetMET Paths",SDJetMETInc);
//   plot->HistoInc->Fill("Mu Paths",SDMuInc);
   plot->HistoInc->Fill("Total",SDBoth);
   plot->HistoInc->SetStats(0)  ;
   plot->HistoInc->LabelsOption("v");
   plot->HistoInc->Scale(100./Total);


   plot->BetaTotal->Divide(plot->BetaCount);
   plot->BetaMuon ->Divide(plot->BetaCount);
   plot->BetaJet  ->Divide(plot->BetaCount);

   plot->BetaTotal->Scale(100.0);
   plot->BetaMuon ->Scale(100.0);
   plot->BetaJet  ->Scale(100.0);

   TH1** Histos = new TH1*[10];
   std::vector<string> legend;
   TCanvas* c1;
   
   c1 = new TCanvas("c1","c1,",600,600);          legend.clear();
   Histos[0] = (TH1*)plot->BetaMuon;                    legend.push_back("Muon");
   Histos[1] = (TH1*)plot->BetaTotal;                   legend.push_back("Overall");
   DrawSuperposedHistos((TH1**)Histos, legend, "HIST E1",  "#beta of the fastest HSCP", "Trigger Efficiency (%)", 0,1, 0,100);
   DrawLegend((TObject**)Histos,legend,"Trigger:","LP",0.35, 0.93, 0.18, 0.04);
   c1->Modified();
   DrawPreliminary(-1);
   SaveCanvas(c1,"pictures/",SignalName);
   delete c1;
}

void layout(vector<stPlot*>& plots, vector<string>& sigs, string name){
   unsigned int NPath   = 0+4;

   std::vector<string> legend;
   TObject** Histos1 = new TObject*[plots.size()];


   TLine* line1 = new TLine(plots[0]->Histo->GetBinLowEdge(NPath), 0, plots[0]->Histo->GetBinLowEdge(NPath), 100);
   line1->SetLineWidth(2); line1->SetLineStyle(1);
//   TLine* line2 = new TLine(plots[0]->Histo->GetBinLowEdge(NPath+3), 0, plots[0]->Histo->GetBinLowEdge(NPath+3), 100);
//   line2->SetLineWidth(2); line2->SetLineStyle(1);

   TCanvas* c1 = new TCanvas("MyC","Histo",600,600);
   legend.clear();
   c1->SetGrid();
   c1->SetBottomMargin(0.3);

   for(unsigned int i=0;i<plots.size();i++){
      Histos1[i]=plots[i]->Histo; legend.push_back(sigs[i]);
   }
//   DrawSuperposedHistos((TH1**)Histos1, legend, "E1",  "", "Efficiency (%)", 0,0, 0,100);  
   if(name=="summary_Gluino")DrawSuperposedHistos((TH1**)Histos1, legend, "E1",  "", "Efficiency (%)", 0,0, 0,30);
   else                      DrawSuperposedHistos((TH1**)Histos1, legend, "E1",  "", "Efficiency (%)", 0,0, 0,100);
   DrawLegend(Histos1,legend,"","P", 0.98, 0.90, 0.13, 0.07);
   DrawPreliminary(-1);

   for(unsigned int i=0;i<plots.size();i++){
      plots[i]->Histo->GetYaxis()->SetTitleOffset(1.55);
      plots[i]->Histo->SetMarkerSize(0.8);
   }
   line1->Draw();
//   line2->Draw();
   SaveCanvas(c1,"pictures/",name);
   delete c1;

   c1 = new TCanvas("MyC","Histo",600,600);
   legend.clear();
   c1->SetGrid();
   c1->SetBottomMargin(0.3);

   for(unsigned int i=0;i<plots.size();i++){
      Histos1[i]=plots[i]->HistoInc; legend.push_back(sigs[i]);
   }
   if(name=="summary_Gluino")DrawSuperposedHistos((TH1**)Histos1, legend, "E1",  "", "Incremental Efficiency (%)", 0,0, 0,30);
   else                      DrawSuperposedHistos((TH1**)Histos1, legend, "E1",  "", "Incremental Efficiency (%)", 0,0, 0,100);
   DrawLegend(Histos1,legend,"","P", 0.98, 0.90, 0.13, 0.07);
   DrawPreliminary(-1);

   for(unsigned int i=0;i<plots.size();i++){
      plots[i]->HistoInc->GetYaxis()->SetTitleOffset(1.55);
      plots[i]->HistoInc->SetMarkerSize(0.8);
   }

   line1->Draw();
//   line2->Draw();
   SaveCanvas(c1,"pictures/",name + "_inc");
   delete c1;
}


double FastestHSCP(const fwlite::ChainEvent& ev){
   fwlite::Handle< std::vector<reco::GenParticle> > genCollHandle;
   genCollHandle.getByLabel(ev, "genParticles");
   if(!genCollHandle.isValid()){printf("GenParticle Collection NotFound\n");return -1;}
   std::vector<reco::GenParticle> genColl = *genCollHandle;

   double MaxBeta=-1;
   for(unsigned int g=0;g<genColl.size();g++){
      if(genColl[g].pt()<5)continue;
      if(genColl[g].status()!=1)continue;
      int AbsPdg=abs(genColl[g].pdgId());
      if(AbsPdg<1000000)continue;    

      double beta=genColl[g].p()/genColl[g].energy();
      if(MaxBeta<beta)MaxBeta=beta;
   }
   return MaxBeta;
}



bool IncreasedTreshold(const trigger::TriggerEvent& trEv, const edm::InputTag& InputPath, double NewThreshold, int NObjectAboveThreshold, bool averageThreshold)
{
   unsigned int filterIndex = trEv.filterIndex(InputPath);
   //if(filterIndex<trEv.sizeFilters())printf("SELECTED INDEX =%i --> %s    XXX   %s\n",filterIndex,trEv.filterTag(filterIndex).label().c_str(), trEv.filterTag(filterIndex).process().c_str());
         
   if (filterIndex<trEv.sizeFilters()){
      const trigger::Vids& VIDS(trEv.filterIds(filterIndex));
      const trigger::Keys& KEYS(trEv.filterKeys(filterIndex));
      const size_type nI(VIDS.size());
      const size_type nK(KEYS.size());
      assert(nI==nK);
      const size_type n(max(nI,nK));
      const trigger::TriggerObjectCollection& TOC(trEv.getObjects());


      if(!averageThreshold){
         int NObjectAboveThresholdObserved = 0;
         for (size_type i=0; i!=n; ++i) {
            const TriggerObject& TO(TOC[KEYS[i]]);
            if(TO.pt()> NewThreshold) NObjectAboveThresholdObserved++;
   	    //cout << "   " << i << " " << VIDS[i] << "/" << KEYS[i] << ": "<< TO.id() << " " << TO.pt() << " " << TO.eta() << " " << TO.phi() << " " << TO.mass()<< endl;
         }          
         if(NObjectAboveThresholdObserved>=NObjectAboveThreshold)return true;

      }else{
         std::vector<double> ObjPt;

         for (size_type i=0; i!=n; ++i) {
            const TriggerObject& TO(TOC[KEYS[i]]);
            ObjPt.push_back(TO.pt());
            //cout << "   " << i << " " << VIDS[i] << "/" << KEYS[i] << ": "<< TO.id() << " " << TO.pt() << " " << TO.eta() << " " << TO.phi() << " " << TO.mass()<< endl;
         }  
         if((int)(ObjPt.size())<NObjectAboveThreshold)return false;
         std::sort(ObjPt.begin(), ObjPt.end());
         
         double Average = 0;
         for(int i=0; i<NObjectAboveThreshold;i++){
            Average+= ObjPt[ObjPt.size()-1-i];            
         }Average/=NObjectAboveThreshold;
	 //cout << "AVERAGE = " << Average << endl;
         
         if(Average>NewThreshold)return true;                  
      }
   }
   return false;
}


int JobIdToIndex(string JobId){
   for(unsigned int s=0;s<signals.size();s++){
      if(signals[s].Name==JobId)return s;
   }return -1;
}

