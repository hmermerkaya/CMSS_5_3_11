#include "TFile.h"
#include "TClonesArray.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TMath.h"
//#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include <vector>

#include "TRandom.h"
#include "TStopwatch.h"
#include "TLeafObject.h"
#include "TSystem.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TBranch.h"
#include "TBranchElement.h"

#include <map>
#include <vector>
#include <string>

/*
source ~/Desktop/setupRoot5.25.sh
rootcint -f dict.cpp -c -p Math/LorentzVector.h LinkDef.h
c++ -o listBranches `root-config --cflags --glibs` -lGenVector listBranches.cpp dict.cpp 

*/

/*

mancano i vector 3D, manca altro?
*/

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


int main (int argc, char ** argv)
{
  TFile f (argv[1]) ;
  TTree * tr = (TTree*) f.Get (argv[2]) ;

std::cerr << "argv[1] = " << argv[1] << std::endl;
std::cerr << "argv[2] = " << argv[2] << std::endl;

  TObjArray * br_list = tr->GetListOfBranches () ;
  TIter br_it (br_list) ;
  TBranch * iBranch ; 

  TObjArray * leaves = tr->GetListOfLeaves () ;
  Int_t nleaves = leaves ? leaves->GetEntriesFast () : 0 ;
  
  std::cout << " \n---- ---- ---- ---- ---- ---- ---- ---- \n" ;
  //PG loop over leaves
  for (int l = 0 ; l < nleaves ; ++l) 
     {
	   TLeaf * leaf = (TLeaf*) leaves->UncheckedAt (l) ;
       TLeafObject * leafobj = (TLeafObject*) leaf ;
       std::cout << "LE | "
                 << leafobj->GetTypeName() << "\t" << leafobj->GetName() << std::endl ;
	} //PG loop over leaves

  std::cout << " \n---- ---- ---- ---- ---- ---- ---- ---- \n" ;
  //PG loop over branches
  while ((iBranch = (TBranch *) br_it.Next ())) 
    {
      TBranchElement* bre = (TBranchElement*) iBranch ;
      std::cout << bre->GetName () 
                << "\t" << bre->GetClassName () 
                << "\n" ;      
    } //PG loop over branches
  std::cout << " ---- ---- ---- ---- ---- ---- ---- ---- \n" ;


  return 0 ;

}
  
