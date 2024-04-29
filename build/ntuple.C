{
  TFile file("output.root");
  TCanvas *c1 = new TCanvas("c1", "MyCanvas", 800, 600);
  TNtuple* ntuple = (TNtuple*)file.Get("HPGe");  //ntuple's name (run.cc file))

  Int_t num, det;
  cout << "Enter the number of detectors in the simulation: "; cin >> num;
  cout << "Choose the detector whose output you want to plot (1,2,...): "; cin >> det;



  if(file.IsZombie()) {
    cout << "Error: Unable to open file 'output.root'!" << endl;
    return 1;
  }


  if(det>0 && det<=num) 
  {
    ntuple->Draw(("Eabs"+std::to_string(det)).c_str());  //column's name (run.cc file)
    c1->Draw();
  }
  else {
    cout << "Error: Invalid detector number!" << endl;
    return 1;
  }
}
