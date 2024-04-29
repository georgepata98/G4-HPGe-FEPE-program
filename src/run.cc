#include "run.hh"

MyRunAction::MyRunAction()
{
  G4RunManager::GetRunManager()->SetPrintProgress(1);  //set printing event number per each event

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);

  //create histograms and ntuples for each sensitive detector
  for(G4int i=0; i<num; i++)
  {
    analysisManager->CreateH1(("Eabs"+std::to_string(i+1)).c_str(), ("Edep in Ge crystal "+std::to_string(i+1)).c_str(), nbins, e_min*keV, e_max*keV);
  }

  analysisManager->CreateNtuple("HPGe", "Edep in Ge crystal");
  for(G4int i=0; i<num; i++)
  {
    analysisManager->CreateNtupleDColumn(("Eabs"+std::to_string(i+1)).c_str());
  }
  analysisManager->FinishNtuple();
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
  auto analysisManager = G4AnalysisManager::Instance();

  //create output file after the run
  G4String fileName = "output.root";
  analysisManager->OpenFile(fileName);
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
  auto analysisManager = G4AnalysisManager::Instance();
  
  //save histograms and ntuples
  analysisManager->Write();
  analysisManager->CloseFile();
}