#include "physics.hh"

MyPhysicsList::MyPhysicsList()
:G4VModularPhysicsList(),
fEm(nullptr)
{
  SetVerboseLevel(0);
  G4EmParameters::Instance();

  fEm = new G4EmLivermorePhysics(0);
  //fEm = new G4EmPenelopePhysics(0);
  //fEm = new G4EmStandardPhysicsOption_4(0);
  
  RegisterPhysics(fEm);
}

MyPhysicsList::~MyPhysicsList()
{}

//Nu este nevoie de ConstructEM() si ConstructProcess() in G4VModularPhysicsList()

void MyPhysicsList::SetCuts()
{
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(250*eV, 1*GeV);
}