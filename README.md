RO:
--------------------------------------------------------------------------------
1. Numarul de detectori 'G4int num' trebuie introdus in urmatoarele fisiere header (.hh): construction.hh, run.hh, event.hh.

2. Numarul de bini 'G4int nbins', binul de energie minima 'G4double e_min' si respectiv binul de energia maxima 'G4double e_max' (in keV) pentru histogramele din fisierul de output trebuie date in fisierul run.hh.

3. In fisierul gps.mac se pot modifica parametrii sursei gamma si numarul total de evenimente (numarul de particule primare generate intr-un run).

4. In fisierul vis.mac se controleaza setarile de vizualizare ale volumelor simulate.

5. Analizarea datelor se face in ROOT executand programele histogram.C sau ntuple.C din folderul /build, sau din ROOT TBrowser.
--------------------------------------------------------------------------------




EN:
--------------------------------------------------------------------------------
1. Number of simulated detectors 'G4int num' must be entered in the following header files (.hh): construction.hh, run.hh, event.hh.

2. Number of bins 'G4int nbins', lowest energy bin 'G4double e_min' and highest energy bin 'G4double e_max' (in keV) for the output histograms must be entered in the run.hh file.

3. Gamma source parameters and the total number of events in one run can be modified in the gps.mac file.

4. Visualization settings for the simulated volumes can be modified in the vis.mac file.

5. Simulation data can be analyzed using the ROOT framework by executing the C++ files histogram.C or ntuple.C from /build directory, or simply by using ROOT TBrowser.
--------------------------------------------------------------------------------
