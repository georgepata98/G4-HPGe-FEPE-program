#include "event.hh"

MyEventAction::MyEventAction()
{
  G4RunManager::GetRunManager()->SetPrintProgress(0);

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(0);
}

MyEventAction::~MyEventAction()
{}

G4THitsMap<G4double>* MyEventAction::GetHitsCollection(G4int hcID, const G4Event *event) const
{
  auto hitsCollection = static_cast<G4THitsMap<G4double>*>(event->GetHCofThisEvent()->GetHC(hcID));

  if(!hitsCollection) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()", "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

G4double MyEventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
  G4double sumValue=0;
  for(auto it:*hitsMap->GetMap()) 
  {
    sumValue+=*(it.second);
  }
  return sumValue;
}

void MyEventAction::BeginOfEventAction(const G4Event*)
{}

void MyEventAction::EndOfEventAction(const G4Event* event)
{
  G4int fAbsoEdepHCID[num];

  for(G4int i=0; i<num; i++)
  {
    fAbsoEdepHCID[i]=-1;
  }

  for(G4int i=0; i<num; i++)
  {
    fAbsoEdepHCID[i] = G4SDManager::GetSDMpointer()->GetCollectionID(("absDetector"+std::to_string(i)+"/"+"Edep"+std::to_string(i)).c_str());  //MultiFunctionalDetector[i] name / PrimitiveScorer[i] name
  }

  //suma G4double incarcata in array-ul absoEdep[] din G4THitsMap a sistemului fAbsoEdepHCID[]={absDetector[], Edep[]} din intregul event
  G4double absoEdep[num];
  for(G4int i=0; i<num; i++)
  {
    absoEdep[i] = GetSum(GetHitsCollection(fAbsoEdepHCID[i], event));
  }

  auto analysisManager = G4AnalysisManager::Instance();
  for(G4int i=0; i<num; i++)
  {
    analysisManager->FillH1(i, absoEdep[i]);
  }

  for(G4int i=0; i<num; i++)
  {
    analysisManager->FillNtupleDColumn(i, absoEdep[i]);
  }
  analysisManager->AddNtupleRow();
}