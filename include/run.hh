#ifndef RUN_HH
#define RUN_HH

#include "G4SystemOfUnits.hh"
#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

class MyRunAction : public G4UserRunAction
{
public:
  MyRunAction();
  ~MyRunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);

private:
  G4int nbins=145;  //number of bins
  //Bin range
  G4double e_min=0;  //min energy bin, in [keV]
  G4double e_max=525;  //max energy bin, in [keV]

  G4int num=1;  //enter the number of detectors here
};

#endif
