/*
source ~/Desktop/setupRoot5.25.sh
rootcint -f dict.cpp -c LinkDef.h
c++ -o testReader `root-config --cflags --glibs` -lGenVector testReader.cpp dict.cpp treeReader.cc
*/

#include "treeReader.h"

int main (int argc, char ** argv)
{
  TFile f (argv[1]) ;
  TTree * tr = (TTree*) f.Get (argv[2]) ;

  treeReader reader (tr) ;

  //PG loop over the events
  for (int iEvent = 0 ; iEvent < tr->GetEntries () ; ++iEvent)
    {
      reader.GetEntry (iEvent) ;
      std::vector<float>* mcT2_charge= reader.GetFloat("mcT2_charge");
    } //PG loop over the events
  return 0 ;
}