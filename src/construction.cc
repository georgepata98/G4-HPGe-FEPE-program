#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
  return DefineVolumes();
}

G4VPhysicalVolume *MyDetectorConstruction::DefineVolumes()
{
  //declaration----------
  G4double distance[num], angle[num], zangle[num];
  G4double r_min, r_max, hz, dx, dy, dz;
  G4double crystal_diameter[num], crystal_length[num], hole_diameter[num], hole_depth[num], crystaltolowintholder_distance[num], full_length[num], fronttoendcap_distance[num], window_thickness[num], endcap_thickness[num], window_diameter[num], lowintholder_thickness[num];
  G4double foil_thickness[num], shield_thickness[num];  //any other structural volumes

  G4Tubs *solidTube1[num], *solidTube2[num], *solidWindow[num], *solidAirlayer[num], *solidCrystalFrontlayer[num], *solidIntHolder1[num], *solidIntHolder2[num], *solidIntHolder3[num], *solidIntHolder4[num], *solidSupport1[num], *solidSupport2[num], *solidTube18[num], *solidTube19[num], *solidTube20[num], *solidTubeX[num], *solidDetector[num];
  G4SubtractionSolid *solidCrystal[num];
  G4LogicalVolume *logicTube1[num], *logicTube2[num], *logicWindow[num], *logicAirlayer[num], *logicCrystalFrontlayer[num], *logicIntHolder1[num], *logicIntHolder2[num], *logicIntHolder3[num], *logicIntHolder4[num], *logicSupport1[num], *logicSupport2[num], *logicTube18[num], *logicTube19[num], *logicTube20[num], *logicCrystal[num], *logicDetector[num];
  G4VPhysicalVolume *physTube1[num], *physTube2[num], *physWindow[num], *physAirlayer[num], *physCrystalFrontlayer[num], *physIntHolder1[num], *physIntHolder2[num], *physIntHolder3[num], *physIntHolder4[num], *physSupport1[num], *physSupport2[num], *physTube18[num], *physTube19[num], *physTube20[num], *physCrystal[num], *physDetector[num];

  G4String answer;
  G4cout << "Exista materiale de ecranare a fondului pe/langa detectori? (da/nu)" << G4endl; G4cin >> answer;
  if(answer=="nu" || answer=="no" || answer=="n") boolDetectorShielding=false;
  else if(answer=="da" || answer=="yes" || answer=="y") boolDetectorShielding=true;

  G4cout << "Introduceti manual dimensiunile geometrice cerute de simulare? (da/nu)" << G4endl;
  G4cout << "(initial se introduc manual pt. a umple fisierul de input cu datele respective)" << G4endl; G4cin >> answer;
  if(answer=="da" || answer=="yes" || answer=="y") boolManualInput=true;
  else if(answer=="nu" || answer=="no" || answer=="n") boolManualInput=false;

  std::fstream file;



  //materials----------
  G4NistManager *nist = G4NistManager::Instance();

  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material *GeMat = nist->FindOrBuildMaterial("G4_Ge");
  G4Material *AlMat = nist->FindOrBuildMaterial("G4_Al");
  G4Material *BeMat = nist->FindOrBuildMaterial("G4_Be");
  G4Material *PbMat = nist->FindOrBuildMaterial("G4_Pb");
  G4Material *CuMat = nist->FindOrBuildMaterial("G4_Cu");
  G4Material *CMat = nist->FindOrBuildMaterial("G4_C");
  G4Material *voidMat = new G4Material("void", 1., 1.008*g/mole, 1e-25*g/cm3, kStateGas, 2.73*kelvin, 3e-18*pascal);



  //user-input----------
  if(boolManualInput) file.open("o_input.txt", std::ios::out);  //write data to o_input.txt file
  if(boolManualInput)
  {
    G4cout << G4endl << "*****Geometria experimentala*****" << G4endl;

    for(G4int i=0; i<num; i++)
    {
      if(i==0) {
        G4cout << ">> Introduceti distantele sursa-fata detector, in [cm]: " << G4endl; 
      }
      G4cout << "det." << i+1 << ": " << G4endl; G4cin >> distance[i];
      file << distance[i] << G4endl;
    }

    for(G4int i=0; i<num; i++)
    {
      if(i==0) {
        G4cout << ">> Introduceti unghiurile la care sunt detectorii, in [grade] " << G4endl;
        G4cout << ">> (in sensul acelor de ceas, ora 12 fiind directia de propagare a fasciculului): " << G4endl;
      }
      G4cout << "det." << i+1 << ": " <<  G4endl; G4cin >> angle[i];
      file << angle[i] << G4endl;
    }

    for(G4int i=0; i<num; i++)
    {
      if(i==0) {
        G4cout << ">> Introduceti unghiurile fata de planul orizontal (ZY) la care sunt pusi detectorii, in [grade] " << G4endl;
        G4cout << "(se dau valori pozitive daca detectorii sunt deasupra planului orizontal al fasciculului si negative in caz contrar):" << G4endl;
      }
      G4cout << "det." << i+1 << ": " << G4endl; G4cin >> zangle[i];
      file << zangle[i] << G4endl;
    }

    G4cout << G4endl << "*****Geometria detectorilor*****" << G4endl;

    for(G4int i=0; i<num; i++)
    {
      if(i==0) {
        G4cout << ">> Ge Crystal Diameter, in [mm]: " << G4endl;
      }
      G4cout << "det." << i+1 << ": " << G4endl; G4cin >> crystal_diameter[i];
      file << crystal_diameter[i] << G4endl;
    }

    for(G4int i=0; i<num; i++)
    {
      if(i==0) {
        G4cout << ">> Ge Crystal Length, in [mm]: " << G4endl;
      }
      G4cout << "det." << i+1 << ": " << G4endl; G4cin >> crystal_length[i];
      file << crystal_length[i] << G4endl;
    }

    for(G4int i=0; i<num; i++)
    {
      if(i==0) {
        G4cout << ">> Core Hole Diameter, in [mm]: " << G4endl;
      }
      G4cout << "det." << i+1 << ": " << G4endl; G4cin >> hole_diameter[i];
      file << hole_diameter[i] << G4endl;
    }

    for(G4int i=0; i<num; i++)
    {
      if(i==0) {
        G4cout << ">> Core Hole Depth, in [mm]: " << G4endl;
      }
      G4cout << "det." << i+1 << ": " << G4endl; G4cin >> hole_depth[i];
      file << hole_depth[i] << G4endl;
    }

    for(G4int i=0; i<num; i++)
    {
      if(i==0) {
        G4cout << ">> Lower part of the crystal to lower part of the internal holder distance, in [mm] " << G4endl;
        G4cout << ">> (este distanta dintre partea de jos a cristalului si partea de jos a suportului interior, notat cu x pe poza): " << G4endl;
      }
      G4cout << "det." << i+1 << ": " << G4endl; G4cin >> crystaltolowintholder_distance[i];
      file << crystaltolowintholder_distance[i] << G4endl;
    }

    for(G4int i=0; i<num; i++)
    {
      if(i==0) {
        G4cout << ">> Full length of the detector tube, in [mm]: " << G4endl;
      }
      G4cout << "det." << i+1 << ": " << G4endl; G4cin >> full_length[i];
      file << full_length[i] << G4endl;
    }

    for(G4int i=0; i<num; i++)
    {
      if(i==0) {
        G4cout << ">> Ge front to inside of endcap distance, in [mm] " << G4endl;
        G4cout << ">> (este grosimea spatiului cu vid dintre suportul extern si cel intern al tubului detector): " << G4endl;
      }
      G4cout << "det." << i+1 << ": " << G4endl; G4cin >> fronttoendcap_distance[i];
      file << fronttoendcap_distance[i] << G4endl;
    }

    for(G4int i=0; i<num; i++)
    {
      if(i==0) {
        G4cout << ">> Cryostat Window thickness, in [mm]: " << G4endl;
      }
      G4cout << "det." << i+1 << ": " << G4endl; G4cin >> window_thickness[i];
      file << window_thickness[i] << G4endl;
    }

    for(G4int i=0; i<num; i++)
    {
      if(i==0) {
        G4cout << ">> Endcap thickness, in [mm] " << G4endl;
        G4cout << ">> (este grosimea suportului extern al tubului detector): " << G4endl;
      }
      G4cout << "det." << i+1 << ": " << G4endl; G4cin >> endcap_thickness[i];
      file << endcap_thickness[i] << G4endl;
    }

    for(G4int i=0; i<num; i++)
    {
      if(i==0) {
        G4cout << ">> Cryostat Window Diameter, in [mm]: " << G4endl;
      }
      G4cout << "det." << i+1 << ": " << G4endl; G4cin >> window_diameter[i];
      file << window_diameter[i] << G4endl;
    }

    for(G4int i=0; i<num; i++)
    {
      if(i==0) {
        G4cout << ">> Lower part of the internal holder thickness, in [mm] " << G4endl;
        G4cout << ">> (este grosimea partii de jos a suportului interior, notata cu delta mic pe poza): " << G4endl;
      }
      G4cout << "det." << i+1 << ": " << G4endl; G4cin >> lowintholder_thickness[i];
      file << lowintholder_thickness[i] << G4endl;
    }

    if(boolDetectorShielding) {
      G4cout << G4endl << "*****Geometria celorlalte materiale din experiment*****" << G4endl;

      for(G4int i=0; i<num; i++)
      {
        if(i==0) {
          G4cout << ">> Introduceti grosimile foitelor de Pb puse in jurul detectorilor, in [mm]: " << G4endl;
        }
        G4cout << "det." << i+1 << ": " << G4endl; G4cin >> foil_thickness[i];
        file << foil_thickness[i] << G4endl;
      }

      for(G4int i=0; i<num; i++)
      {
        if(i==0) {
          G4cout << ">> Introduceti grosimile placutelor de Pb puse in fata detectorilor, in [mm]: " << G4endl;
        }
        G4cout << "det." << i+1 << ": " << G4endl; G4cin >> shield_thickness[i];
        file << shield_thickness[i] << G4endl;
      }
    }
  }
  if(boolManualInput) file.close();


  if(!boolManualInput) file.open("o_input.txt", std::ios::in);  //extract data from o_input.txt file
  if(!boolManualInput) 
  {
    G4String line;
    for(G4int i=0; i<num; i++)
    {
      getline(file, line);  //reads one line from file
      std::istringstream iss(line);
      iss >> distance[i];
    }
    for(G4int i=0; i<num; i++)
    {
      getline(file, line);
      std::istringstream iss(line);
      iss >> angle[i];
    }
    for(G4int i=0; i<num; i++)
    {
      getline(file, line);
      std::istringstream iss(line);
      iss >> zangle[i];
    }
    for(G4int i=0; i<num; i++)
    {
      getline(file, line);
      std::istringstream iss(line);
      iss >> crystal_diameter[i];
    }
    for(G4int i=0; i<num; i++)
    {
      getline(file, line);
      std::istringstream iss(line);
      iss >> crystal_length[i];
    }
    for(G4int i=0; i<num; i++)
    {
      getline(file, line);
      std::istringstream iss(line);
      iss >> hole_diameter[i];
    }
    for(G4int i=0; i<num; i++)
    {
      getline(file, line);
      std::istringstream iss(line);
      iss >> hole_depth[i];
    }
    for(G4int i=0; i<num; i++)
    {
      getline(file, line);
      std::istringstream iss(line);
      iss >> crystaltolowintholder_distance[i];
    }
    for(G4int i=0; i<num; i++)
    {
      getline(file, line);
      std::istringstream iss(line);
      iss >> full_length[i];
    }
    for(G4int i=0; i<num; i++)
    {
      getline(file, line);
      std::istringstream iss(line);
      iss >> fronttoendcap_distance[i];
    }
    for(G4int i=0; i<num; i++)
    {
      getline(file, line);
      std::istringstream iss(line);
      iss >> window_thickness[i];
    }
    for(G4int i=0; i<num; i++)
    {
      getline(file, line);
      std::istringstream iss(line);
      iss >> endcap_thickness[i];
    }
    for(G4int i=0; i<num; i++)
    {
      getline(file, line);
      std::istringstream iss(line);
      iss >> window_diameter[i];
    }
    for(G4int i=0; i<num; i++)
    {
      getline(file, line);
      std::istringstream iss(line);
      iss >> lowintholder_thickness[i];
    }

    if(boolDetectorShielding) {
      for(G4int i=0; i<num; i++)
      {
        getline(file, line);
        std::istringstream iss(line);
        iss >> foil_thickness[i];
      }
      for(G4int i=0; i<num; i++)
      {
        getline(file, line);
        std::istringstream iss(line);
        iss >> shield_thickness[i];
      }
    }
  }
  if(!boolManualInput) file.close();





  //world----------
  G4Box *solidWorld = new G4Box("solidWorld", .5*m, .5*m, .5*m);
  G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicWorld, "physWorld", 0, false, 0, true);

  
  //detectors----------
  for(G4int i=0; i<num; i++)
  {
    r_min=0.*mm;
    r_max=(window_diameter[i]/2)*mm;
    hz=(window_thickness[i]/2)*mm;
    solidWindow[i] = new G4Tubs(("solidWindow"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicWindow[i] = new G4LogicalVolume(solidWindow[i], BeMat, ("logicWindow"+std::to_string(i)).c_str());

    r_min=(window_diameter[i]/2)*mm;
    r_max=(crystal_diameter[i]/2+.8+fronttoendcap_distance[i]+endcap_thickness[i])*mm;
    hz=(endcap_thickness[i]/2)*mm;
    solidTube1[i] = new G4Tubs(("solidTube1"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicTube1[i] = new G4LogicalVolume(solidTube1[i], AlMat, ("logicTube1"+std::to_string(i)).c_str());

    r_min=(crystal_diameter[i]/2+.8+fronttoendcap_distance[i])*mm;
    r_max=(crystal_diameter[i]/2+.8+fronttoendcap_distance[i]+endcap_thickness[i])*mm;
    hz=(full_length[i]-endcap_thickness[i])/2*mm;
    solidTube2[i] = new G4Tubs(("solidTube2"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicTube2[i] = new G4LogicalVolume(solidTube2[i], AlMat, ("logicTube2"+std::to_string(i)).c_str());

    r_min=0.*mm;
    r_max=(window_diameter[i]/2)*mm;
    hz=(endcap_thickness[i]-window_thickness[i])/4*mm;
    solidAirlayer[i] = new G4Tubs(("solidAirlayer"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicAirlayer[i] = new G4LogicalVolume(solidAirlayer[i], worldMat, ("logicAirlayer"+std::to_string(i)).c_str());

    r_min=0.*mm;
    r_max=(crystal_diameter[i]/2)*mm;
    hz=(1.3/2)*mm;
    solidCrystalFrontlayer[i] = new G4Tubs(("solidCrystalFrontlayer"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicCrystalFrontlayer[i] = new G4LogicalVolume(solidCrystalFrontlayer[i], AlMat, ("logicCrystalFrontlayer"+std::to_string(i)).c_str());

    r_min=(crystal_diameter[i]/2)*mm;
    r_max=(crystal_diameter[i]/2+.8)*mm;
    hz=(1.3+crystal_length[i]+crystaltolowintholder_distance[i])/2*mm;
    solidIntHolder1[i] = new G4Tubs(("solidIntHolder1"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicIntHolder1[i] = new G4LogicalVolume(solidIntHolder1[i], AlMat, ("logicIntHolder1"+std::to_string(i)).c_str());

    r_min=10.*mm;
    r_max=(crystal_diameter[i]/2+.8)*mm;
    hz=(3/2)*mm;
    solidIntHolder2[i] = new G4Tubs(("solidIntHolder2"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicIntHolder2[i] = new G4LogicalVolume(solidIntHolder2[i], AlMat, ("logicIntHolder2"+std::to_string(i)).c_str());

    r_min=10.*mm;
    r_max=12.5*mm;
    hz=(full_length[i]-endcap_thickness[i]-fronttoendcap_distance[i]-1.3-crystal_length[i]-crystaltolowintholder_distance[i]-3.-lowintholder_thickness[i])/2*mm;
    solidIntHolder3[i] = new G4Tubs(("solidIntHolder3"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicIntHolder3[i] = new G4LogicalVolume(solidIntHolder3[i], AlMat, ("logicIntHolder3"+std::to_string(i)).c_str());

    r_min=0.*mm;
    r_max=12.5*mm;
    hz=(lowintholder_thickness[i]/2)*mm;
    solidIntHolder4[i] = new G4Tubs(("solidIntHolder4"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicIntHolder4[i] = new G4LogicalVolume(solidIntHolder4[i], AlMat, ("logicIntHolder4"+std::to_string(i)).c_str());

    r_min=(crystal_diameter[i]/2+.8)*mm;
    r_max=(crystal_diameter[i]/2+2.7)*mm;
    hz=(8.6/2)*mm;
    solidSupport1[i] = new G4Tubs(("solidSupport1"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicSupport1[i] = new G4LogicalVolume(solidSupport1[i], AlMat, ("logicSupport1"+std::to_string(i)).c_str());

    r_min=(crystal_diameter[i]/2+.8)*mm;
    r_max=(crystal_diameter[i]/2+2.7)*mm;
    hz=(8.6/2)*mm;
    solidSupport2[i] = new G4Tubs(("solidSupport2"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicSupport2[i] = new G4LogicalVolume(solidSupport2[i], AlMat, ("logicSupport2"+std::to_string(i)).c_str());

    r_min=0.*mm;
    r_max=(hole_diameter[i]/2)*mm;
    hz=(hole_depth[i]/2)*mm;
    solidTube18[i] = new G4Tubs(("solidTube18"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicTube18[i] = new G4LogicalVolume(solidTube18[i], AlMat, ("logicTube18"+std::to_string(i)).c_str());

    r_min=0.*mm;
    r_max=(crystal_diameter[i]/2)*mm;
    hz=(crystaltolowintholder_distance[i]/2)*mm;
    solidTube19[i] = new G4Tubs(("solidTube19"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicTube19[i] = new G4LogicalVolume(solidTube19[i], AlMat, ("logicTube19"+std::to_string(i)).c_str());

    r_min=0.*mm;
    r_max=10.*mm;
    hz=(full_length[i]-endcap_thickness[i]-fronttoendcap_distance[i]-1.3-crystal_length[i]-crystaltolowintholder_distance[i]-lowintholder_thickness[i])/2*mm;
    solidTube20[i] = new G4Tubs(("solidTube20"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicTube20[i] = new G4LogicalVolume(solidTube20[i], AlMat, ("logicTube20"+std::to_string(i)).c_str());

    r_min=0.*mm;
    r_max=(crystal_diameter[i]/2)*mm;
    hz=(crystal_length[i]/2)*mm;
    solidTubeX[i] = new G4Tubs(("solidTubeX"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);

    solidCrystal[i] = new G4SubtractionSolid(("solidCrystal"+std::to_string(i)).c_str(), solidTubeX[i], solidTube18[i], 0, G4ThreeVector(0, 0, (-crystal_length[i]/2+hole_depth[i]/2)*mm));  //solidTubeX - solidTube18
    logicCrystal[i] = new G4LogicalVolume(solidCrystal[i], GeMat, ("logicCrystal"+std::to_string(i)).c_str());

    r_min=0.*mm;
    r_max=(crystal_diameter[i]/2+.8+fronttoendcap_distance[i]+endcap_thickness[i])*mm;
    hz=(full_length[i])/2*mm;
    solidDetector[i] = new G4Tubs(("solidDetector"+std::to_string(i)).c_str(), r_min, r_max, hz, 0*deg, 360*deg);
    logicDetector[i] = new G4LogicalVolume(solidDetector[i], voidMat, ("logicDetector"+std::to_string(i)).c_str());  //detector tube mother volume



    //detectors positioning in mothers----------
    physDetector[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicDetector[i], ("physDetector"+std::to_string(i)).c_str(), logicWorld, false, 0, true);
    physTube1[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (full_length[i]/2-endcap_thickness[i]/2)*mm), logicTube1[i], ("physTube1"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
    physTube2[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (-full_length[i]/2+(full_length[i]-endcap_thickness[i])/2)*mm), logicTube2[i], ("physTube2"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
    physWindow[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (full_length[i]/2-endcap_thickness[i]/2)*mm), logicWindow[i], ("physWindow"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
    physAirlayer[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (full_length[i]/2-(endcap_thickness[i]-window_thickness[i])/4)*mm), logicAirlayer[i], ("physAirlayer"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
    physCrystalFrontlayer[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (full_length[i]/2-endcap_thickness[i]-fronttoendcap_distance[i]-1.3/2)*mm), logicCrystalFrontlayer[i], ("physCrystalFrontlayer"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
    physIntHolder1[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (full_length[i]/2-endcap_thickness[i]-fronttoendcap_distance[i]-(1.3+crystal_length[i]+crystaltolowintholder_distance[i])/2)*mm), logicIntHolder1[i], ("physIntHolder1"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
    physIntHolder2[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (full_length[i]/2-endcap_thickness[i]-fronttoendcap_distance[i]-1.3-crystal_length[i]-crystaltolowintholder_distance[i]-3/2)*mm), logicIntHolder2[i], ("physIntHolder2"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
    physIntHolder3[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (-full_length[i]/2+lowintholder_thickness[i]+(full_length[i]-endcap_thickness[i]-fronttoendcap_distance[i]-1.3-crystal_length[i]-crystaltolowintholder_distance[i]-3.-lowintholder_thickness[i])/2)*mm), logicIntHolder3[i], ("physIntHolder3"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
    physIntHolder4[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (-full_length[i]/2+lowintholder_thickness[i]/2)*mm), logicIntHolder4[i], ("physIntHolder4"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
    physSupport1[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (full_length[i]/2-endcap_thickness[i]-fronttoendcap_distance[i]-14.-8.6/2)*mm), logicSupport1[i], ("physSupport1"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
    physSupport2[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (full_length[i]/2-endcap_thickness[i]-fronttoendcap_distance[i]-51.-8.6/2)*mm), logicSupport2[i], ("physSupport2"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
    physTube18[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (full_length[i]/2-endcap_thickness[i]-fronttoendcap_distance[i]-1.3-(crystal_length[i]-hole_depth[i])-hole_depth[i]/2)*mm), logicTube18[i], ("physTube18"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
    physTube19[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (full_length[i]/2-endcap_thickness[i]-fronttoendcap_distance[i]-1.3-crystal_length[i]-crystaltolowintholder_distance[i]/2)*mm), logicTube19[i], ("physTube19"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
    physTube20[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (-full_length[i]/2+lowintholder_thickness[i]+(full_length[i]-endcap_thickness[i]-fronttoendcap_distance[i]-1.3-crystal_length[i]-crystaltolowintholder_distance[i]-lowintholder_thickness[i])/2)*mm), logicTube20[i], ("physTube20"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
    physCrystal[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, (full_length[i]/2-endcap_thickness[i]-fronttoendcap_distance[i]-1.3-crystal_length[i]/2)*mm), logicCrystal[i], ("physCrystal"+std::to_string(i)).c_str(), logicDetector[i], false, 0, true);
  }


  //reaction chamber (RC) volumes and positioning----------
  G4Tubs *solidRCHolder11 = new G4Tubs("solidRCHolder11", 59*mm, 72.5*mm, 4.4*mm, 0*deg, 360*deg);  //perete suport superior RC
  G4LogicalVolume *logicRCHolder11 = new G4LogicalVolume(solidRCHolder11, AlMat, "logicRCHolder11");
  G4Tubs *solidRCHolder12 = new G4Tubs("solidRCHolder12", 0.*mm, 59*mm, 4.4*mm, 0*deg, 360*deg);
  G4LogicalVolume *logicRCHolder12 = new G4LogicalVolume(solidRCHolder12, voidMat, "logicRCHolder12");

  G4Tubs *solidRCTube11 = new G4Tubs("solidRCTube11", 59*mm, 62.5*mm, 39.5*mm, 0*deg, 360*deg);  //perete teava RC
  G4LogicalVolume *logicRCTube11 = new G4LogicalVolume(solidRCTube11, AlMat, "logicRCTube11");
  G4Tubs *solidRCTube12 = new G4Tubs("solidRCTube12", 0.*mm, 59*mm, 39.5*mm, 0*deg, 360*deg);
  G4LogicalVolume *logicRCTube12 = new G4LogicalVolume(solidRCTube12, voidMat, "logicRCTube12");

  G4Tubs *solidRCHolder21 = new G4Tubs("solidRCHolder21", 59*mm, 72.5*mm, 4.4*mm, 0*deg, 360*deg);  //perete suport inferior RC
  G4LogicalVolume *logicRCHolder21 = new G4LogicalVolume(solidRCHolder21, AlMat, "logicRCHolder21");
  G4Tubs *solidRCHolder22 = new G4Tubs("solidRCHolder22", 0.*mm, 59*mm, 4.4*mm, 0*deg, 360*deg);
  G4LogicalVolume *logicRCHolder22 = new G4LogicalVolume(solidRCHolder22, voidMat, "logicRCHolder22");

  G4RotationMatrix *rotTubeY = new G4RotationMatrix();
  rotTubeY->rotateX(90.*deg);

  G4Sphere *solidRCSphere1 = new G4Sphere("solidRCSphere1", 59*mm, 62.5*mm, 0*deg, 180*deg, 0*deg, 180*deg);
  G4Sphere *solidRCSphere2 = new G4Sphere("solidRCSphere2", 0.*mm, 59*mm, 0*deg, 180*deg, 0*deg, 180*deg);
  G4Tubs *solidTubeY = new G4Tubs("solidTubeY", 0.*mm, 27*mm, 65.455*mm, 0*deg, 360*deg);
  G4SubtractionSolid *solidSubtractionRCSphere1 = new G4SubtractionSolid("solidSubtractionRCSphere1", solidRCSphere1, solidTubeY, rotTubeY, G4ThreeVector(0, 117.915*mm, 0));  //solidRCSphere1 - solidTubeY
  G4SubtractionSolid *solidSubtractionRCSphere2 = new G4SubtractionSolid("solidSubtractionRCSphere2", solidRCSphere2, solidTubeY, rotTubeY, G4ThreeVector(0, 117.915*mm, 0));  //solidRCSphere2 - solidTubeY
  G4LogicalVolume *logicSubtractionRCSphere1 = new G4LogicalVolume(solidSubtractionRCSphere1, AlMat, "logicSubtractionRCSphere1");
  G4LogicalVolume *logicSubtractionRCSphere2 = new G4LogicalVolume(solidSubtractionRCSphere2, voidMat, "logicSubtractionRCSphere2");

  G4Tubs *solidRCTube21 = new G4Tubs("solidRCTube21", 23.5*mm, 27*mm, 65.455*mm, 0*deg, 360*deg);  //perete teava fascicul
  G4LogicalVolume *logicRCTube21 = new G4LogicalVolume(solidRCTube21, AlMat, "logicRCTube21");
  G4Tubs *solidRCTube22 = new G4Tubs("solidRCTube22", 0.*mm, 23.5*mm, 65.455*mm, 0*deg, 360*deg);
  G4LogicalVolume *logicRCTube22 = new G4LogicalVolume(solidRCTube22, voidMat, "logicRCTube22");


  G4RotationMatrix *rotRCSphere = new G4RotationMatrix();
  rotRCSphere->rotateX(90.*deg);

  G4VPhysicalVolume *physRCHolder11 = new G4PVPlacement(0, G4ThreeVector(0, 0, 61.4*mm), logicRCHolder11, "physRCHolder11", logicWorld, false, 0, true);
  G4VPhysicalVolume *physRCHolder12 = new G4PVPlacement(0, G4ThreeVector(0, 0, 61.4*mm), logicRCHolder12, "physRCHolder12", logicWorld, false, 0, true);
  G4VPhysicalVolume *physRCTube11 = new G4PVPlacement(0, G4ThreeVector(0, 0, 17.5*mm), logicRCTube11, "physRCTube11", logicWorld, false, 0, true);
  G4VPhysicalVolume *physRCTube12 = new G4PVPlacement(0, G4ThreeVector(0, 0, 17.5*mm), logicRCTube12, "physRCTube12", logicWorld, false, 0, true);
  G4VPhysicalVolume *physRCHolder21 = new G4PVPlacement(0, G4ThreeVector(0, 0, -26.4*mm), logicRCHolder21, "physRCHolder21", logicWorld, false, 0, true);
  G4VPhysicalVolume *physRCHolder22 = new G4PVPlacement(0, G4ThreeVector(0, 0, -26.4*mm), logicRCHolder22, "physRCHolder22", logicWorld, false, 0, true);
  G4VPhysicalVolume *physSubtractionRCSphere1 = new G4PVPlacement(rotRCSphere, G4ThreeVector(0, 0, -30.8*mm), logicSubtractionRCSphere1, "physSubtractionRCSphere1", logicWorld, false, 0, true);
  G4VPhysicalVolume *physSubtractionRCSphere2 = new G4PVPlacement(rotRCSphere, G4ThreeVector(0, 0, -30.8*mm), logicSubtractionRCSphere2, "physSubtractionRCSphere2", logicWorld, false, 0, true);
  G4VPhysicalVolume *physRCTube21 = new G4PVPlacement(0, G4ThreeVector(0, 0, -148.715*mm), logicRCTube21, "physRCTube21", logicWorld, false, 0, true);
  G4VPhysicalVolume *physRCTube22 = new G4PVPlacement(0, G4ThreeVector(0, 0, -148.715*mm), logicRCTube22, "physRCTube22", logicWorld, false, 0, true);






  //translation operations----------
  for(G4int i=0; i<num; i++)
  {
    G4double ip;
    if(zangle[i]>=0.) ip=cos(zangle[i]*deg)*(10.*distance[i]+full_length[i]/2);
    else if(zangle[i]<0.) ip=cos(-zangle[i]*deg)*(10.*distance[i]+full_length[i]/2);

    if(angle[i]<=180.) {
      dy=sin((180.-angle[i])*deg)*ip;
      if(angle[i]<=90.) dz=cos(angle[i]*deg)*ip;
      if(angle[i]>90.) dz=-cos((180.-angle[i])*deg)*ip;
    }
    if(angle[i]>180.) {
      dy=-sin((angle[i]-180.)*deg)*ip;
      if(angle[i]<=270.) dz=-cos((angle[i]-180.)*deg)*ip;
      if(angle[i]>270.) dz=sin((angle[i]-270.)*deg)*ip;
    }
    if(zangle[i]>=0.) dx=sin(zangle[i]*deg)*(10.*distance[i]+full_length[i]/2);
    else if(zangle[i]<0.) dx=-sin(-zangle[i]*deg)*(10.*distance[i]+full_length[i]/2);
    
    G4ThreeVector translation(dx*mm, dy*mm, dz*mm);
    physDetector[i]->SetTranslation(translation);

    G4RotationMatrix *rot1 = new G4RotationMatrix();
    G4RotationMatrix *rot2 = new G4RotationMatrix();
    if(dx<0.) rot1->rotateY(zangle[i]*deg);
    if(dx>=0.) rot1->rotateY(zangle[i]*deg);
    if(dy>0.) rot2->rotateX((180.+angle[i])*deg);
    if(dy<=0.) rot2->rotateX((angle[i]-180.)*deg);

    G4RotationMatrix *combinedRotation = new G4RotationMatrix(*rot1 * *rot2);
    physDetector[i]->SetRotation(combinedRotation);
  }



  //visualization attributes----------
  for(G4int i=0; i<num; i++)
  {
    logicTube1[i]->SetVisAttributes(G4Colour::Green());
    logicTube2[i]->SetVisAttributes(G4Colour::Green());
    logicWindow[i]->SetVisAttributes(G4Colour::Red());
    logicAirlayer[i]->SetVisAttributes(G4Colour::White());
    logicCrystalFrontlayer[i]->SetVisAttributes(G4Colour::Yellow());
    logicIntHolder1[i]->SetVisAttributes(G4Colour::Green());
    logicIntHolder2[i]->SetVisAttributes(G4Colour::Green());
    logicIntHolder3[i]->SetVisAttributes(G4Colour::Green());
    logicIntHolder4[i]->SetVisAttributes(G4Colour::Green());
    logicSupport1[i]->SetVisAttributes(G4Colour::Green());
    logicSupport2[i]->SetVisAttributes(G4Colour::Green());
    logicTube18[i]->SetVisAttributes(G4Colour::Yellow());
    logicTube19[i]->SetVisAttributes(G4Colour::Yellow());
    logicTube20[i]->SetVisAttributes(G4Colour::Yellow());
    logicCrystal[i]->SetVisAttributes(G4Colour::Blue());
    logicDetector[i]->SetVisAttributes(G4Colour::White());
  }
  logicRCHolder11->SetVisAttributes(G4Colour::Blue());
  logicRCTube11->SetVisAttributes(G4Colour::Blue());
  logicRCHolder21->SetVisAttributes(G4Colour::Blue());
  logicSubtractionRCSphere1->SetVisAttributes(G4Colour::Blue());
  logicRCTube21->SetVisAttributes(G4Colour::Blue());

  return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  G4VPrimitiveScorer *primitive;
  //auto neutral = new G4SDNeutralFilter("neutralFilter");  //only neutral particles accepted

  G4MultiFunctionalDetector *absDetector[num];  //declaration of G4MultiFunctionalDetector
  
  for(G4int i=0; i<num; i++)
  {
    absDetector[i] = new G4MultiFunctionalDetector(("absDetector"+std::to_string(i)).c_str());
    G4SDManager::GetSDMpointer()->AddNewDetector(absDetector[i]);

    primitive = new G4PSEnergyDeposit(("Edep"+std::to_string(i)).c_str());
    //primitive->SetFilter(neutral);
    absDetector[i]->RegisterPrimitive(primitive);

    SetSensitiveDetector(("logicCrystal"+std::to_string(i)).c_str(), absDetector[i]);
  }
}