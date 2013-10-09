#ifndef PUDumper_h
#define PUDumper_h

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "TH1F.h"






class PUDumper : public edm::EDAnalyzer
{
  
 public:
  
  //! ctor
  explicit PUDumper(const edm::ParameterSet&);
  
  //! dtor 
  ~PUDumper();
  
  
  
 private:
  
  //! the actual analyze method 
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  
  
  
 private:
  
  edm::InputTag MCPileupTag_;
  bool mcFlag_;
  
  TH1F* h_nPUtrue;
  TH1F* h_nPUit;
  TH1F* h_nPUoot_early;
  TH1F* h_nPUoot_late;
  
};

#endif
