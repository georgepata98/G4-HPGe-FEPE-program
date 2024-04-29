{
  TFile file("output.root");
  TCanvas *c1 = new TCanvas("c1", "MyCanvas", 800, 600);
  
  Int_t num, det;
  cout << "Enter the number of detectors in the simulation: "; cin >> num;
  cout << "Choose the detector whose output you want to plot (1,2,...): "; cin >> det;



  if(file.IsZombie()) {
    cout << "Error: Unable to open file 'output.root'!" << endl;
    return 1;
  }

  vector<TH1D*> histArray;
  for(Int_t i=0; i<num; i++)
  {
    TH1D *hist = dynamic_cast<TH1D*>(file.Get(("Eabs"+std::to_string(i+1)).c_str()));
    if(!hist) {
      cout << "Error: Histogram Eabs" << std::to_string(i+1) << " not found!" << endl;
      return 1;
    }
    histArray.push_back(hist);  //filling histArray[] with each detector's histogram
  }


  //histogram plotting
  if(det>0 && det<=num) 
  {
    Double_t lowBinUpper=histArray[det-1]->GetBinLowEdge(2);  //energia superioara a primului bin
    Double_t lowBinLower=histArray[det-1]->GetBinLowEdge(1);  //energia inferioara a primului bin
    Double_t bin_width=lowBinUpper-lowBinLower;  //largimea unui bin
    Double_t emin, emax, binError, sum=0;
    Int_t binStart, binStop;

    cout << endl << "Number of bins: " << histArray[det-1]->GetNbinsX() << endl;
    cout << "Bin width: " << bin_width*1000 << " (keV)" << endl;
    cout << endl;
    cout << "Energy interval you want to integrate, in (keV): " << endl;
    cout << "E_min = "; cin >> emin;
    cout << "E_max = "; cin >> emax;
    cout << endl;

    binStart=emin/(1000*bin_width)+1;
    binStop=emax/(1000*bin_width)+1;

    for(Int_t i=1; i<=histArray[det-1]->GetNbinsX(); i++)  //parcurgere de la binul 1 la numarul total de bini
    {
      if(i>=binStart && i<=binStop) {
        binError=histArray[det-1]->GetBinError(i);
        sum+=binError*binError;
      }
      else continue;
    }
    sum=TMath::Sqrt(sum);

    cout << "Area = " << histArray[det-1]->Integral(binStart, binStop) << " +/- " << sum << "  (counts)" << endl;
    cout << "Absolute efficiency for your energy range: " << (histArray[det-1]->Integral(binStart, binStop))/(histArray[det-1]->GetEntries()) << " +/- " << sum/(histArray[det-1]->GetEntries()) << endl;
    cout << endl;

    histArray[det-1]->GetXaxis()->SetTitle("Energy  (MeV)");
    histArray[det-1]->GetYaxis()->SetTitle("Counts");
    histArray[det-1]->GetXaxis()->SetRangeUser(lowBinLower+bin_width, bin_width*histArray[det-1]->GetNbinsX());
    histArray[det-1]->Draw();
    c1->Draw();
  }
  else {
    cout << "Error: Invalid detector number!" << endl;
    return 1;
  }
}
