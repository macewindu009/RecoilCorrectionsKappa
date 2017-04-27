#include "HttStyles.cc"
#include "helperFunctions.cc"
#include "HtoH.h"
#include "FitRecoilMva.C"
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#include <string.h> 

//#include <map>


void PFRecoilCorrectorRoot(TString baseString = "recoilZ",
                         TString Suffix = ""
                         ) {

    //File directory to the merged KappaInputFolder.
    std::string fileDir = "/storage/jbod/nzaeh/NAFPF1204NoCorr/merged/";
    cout << "Input Directory: " << fileDir << endl;
    //cout << ztt_stitchingweight() << endl;
    //
    SetStyle();
    gStyle->SetOptStat(0000);
    gStyle->SetOptFit(0000);


    TFile * fileOutput = new TFile(baseString+Suffix+".root","recreate");
    fileOutput->cd("");
    //List of all Data input. List all Datasets nicks and add their corresponding cross section.
    std::vector<TString> Data = {
        "SingleMuon_Run2016B_23Sep2016v3_13TeV_MINIAOD",
        "SingleMuon_Run2016C_23Sep2016v1_13TeV_MINIAOD",
        "SingleMuon_Run2016D_23Sep2016v1_13TeV_MINIAOD",
        "SingleMuon_Run2016E_23Sep2016v1_13TeV_MINIAOD",
        "SingleMuon_Run2016F_23Sep2016v1_13TeV_MINIAOD",
        "SingleMuon_Run2016G_23Sep2016v1_13TeV_MINIAOD",
        "SingleMuon_Run2016H_PromptRecov2_13TeV_MINIAOD",
        "SingleMuon_Run2016H_PromptRecov3_13TeV_MINIAOD"
    };

    //List of all background samples. List all Datasets nicks and add their corresponding cross section.
    std::vector<TString> Bkg = {
            "VVTo2L2Nu_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_amcatnlo-pythia8",
            "VVTo2L2Nu_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_amcatnlo-pythia8_ext1",
            "WWTo1L1Nu2Q_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_amcatnlo-pythia8",
            "WZTo1L1Nu2Q_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_amcatnlo-pythia8",
            "WZTo1L3Nu_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_amcatnlo-pythia8",
            "WZTo2L2Q_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_amcatnlo-pythia8",
            "ZZTo2L2Q_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_amcatnlo-pythia8",
            "ZZTo4L_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_amcatnlo-pythia8_ext1",
            "STt-channelantitop4finclusiveDecays_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_powheg-pythia8",
            "STt-channeltop4finclusiveDecays_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_powheg-pythia8",
            "STtWantitop5finclusiveDecays_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_powheg-pythia8_ext1",
            "STtWtop5finclusiveDecays_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_powheg-pythia8_ext1",
            "TT_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_powheg-pythia8",
/*
            "WWToLNuQQ_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_powheg",
            "WWToLNuQQ_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_powheg_ext1",
            "WZJToLLLNu_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_pythia8",
            "EWKWMinus2JetsWToLNuM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8",
            "EWKWMinus2JetsWToLNuM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8_ext1",
            "EWKWMinus2JetsWToLNuM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8_ext2",
            "EWKWPlus2JetsWToLNuM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8",
            "EWKWPlus2JetsWToLNuM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8_ext1",
            "EWKWPlus2JetsWToLNuM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8_ext2",
            "EWKZ2JetsZToLLM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8",
            "EWKZ2JetsZToLLM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8_ext1",
            "EWKZ2JetsZToLLM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8_ext2"
*/
    };

    //List of all background WJets stitched samples. List all Datasets nicks and add their corresponding cross section.
    std::vector<TString> BkgWJet = {
            "W1JetsToLNu_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8",
            "W2JetsToLNu_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8",
            "W2JetsToLNu_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8_ext1",
            "W3JetsToLNu_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8",
            "W3JetsToLNu_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8_ext1",
            "W4JetsToLNu_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8",
            "W4JetsToLNu_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8_ext1",
            "W4JetsToLNu_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8_ext2",
            "WJetsToLNu_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8",
            "WJetsToLNu_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8_ext2"
    };

    //List of all signal DY samples. List all Datasets nicks and add their corresponding cross section.
    std::vector<TString> DY = {
            "DY1JetsToLLM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8",
            "DY2JetsToLLM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8",
            "DY3JetsToLLM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8",
            "DY4JetsToLLM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8",
            "DYJetsToLLM10to50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8",
            "DYJetsToLLM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8_ext1",
            "DYJetsToLLM50_RunIISummer16MiniAODv2_PUMoriond17_13TeV_MINIAOD_madgraph-pythia8_ext2"
    };


    //Current Lumi section
    double lumi = 35870;

    //Channel to make evaluation on - mm_jecUncNom is default mumu-nominal channel
    TString channel = "mm_jecUncNom";

    //Tree in which the input is stored
    TString treeName = "ntuple";

    //VariableName in Kappa - Distinguish between parallel and perpendicular component
    TString proj[2] = {"pfrecoilPar+ptvis",
                             "pfrecoilPerp"};

    //Local reference
    TString projLabel[2] = {baseString+"Paral",
                  baseString+"Perp"};


    //Pt-Cuts - 0to10, 10to20, 20to30, 30to50, Greater50 GeV
    TString ptCut[5] = {"(ptvis > 0) * (ptvis <= 10)",
                        "(ptvis > 10) * (ptvis <= 20)",
                        "(ptvis > 20) * (ptvis <= 30)",
                        "(ptvis > 30) * (ptvis <= 50)",
                        "(ptvis > 50)"};
    //Local reference
    TString ptCutLabel[5] = {"Pt0to10",
                        "Pt10to20",
                        "Pt20to30",
                        "Pt30to50",
                        "PtGt50"};


    //Jet-Cuts - 0Jets, 1Jet, More than 2 Jets
    TString jetCut[3] = {"(njets == 0)",
                        "(njets == 1)",
                        "(njets > 1)"};
    //Local reference
    TString jetCutLabel[3] = {"NJet0",
                        "NJet1",
                        "NJetGe2"};


    //Histograms saving the label names, needed later in the official toolkit
    TH1D * projH = new  TH1D("projH","",2,-1,1);
    for (int i=0; i<2; ++i)
        projH->GetXaxis()->SetBinLabel(i+1,projLabel[i]);

    int nZPtBins = 5;
    float zPtBins[6] = {0,10,20,30,50,1000};
    TH1D * ZPtBinsH = new TH1D("ZPtBinsH","ZPtBinsH",nZPtBins,zPtBins);
    for (int iB=0; iB<nZPtBins; ++iB) 
        ZPtBinsH->GetXaxis()->SetBinLabel(iB+1,ptCutLabel[iB]);

    int nJetBins = 3;
    float jetBins[4] = {-0.5,0.5,1.5,2.5};
    TH1D * JetBinsH = new TH1D("nJetBinsH","nJetBinsH",nJetBins,jetBins);
    for (int iB=0; iB<nJetBins; ++iB)
        JetBinsH->GetXaxis()->SetBinLabel(iB+1,jetCutLabel[iB]);

    //zBinsH->Write("ZPtBinsH");
    //jetBinsH->Write("nJetBinsH");
    /*
    int projIndex = 0;
    int ptCutIndex = 0;
    int jetCutIndex = 0;
    */
    //Iterations over proj, ptCut and jetCut
    // Index which projection is currently used
    for(int projIndex = 0; projIndex < sizeof(proj)/sizeof(*proj); projIndex++)
        // Index which pt cut is currently applied
        for(int ptCutIndex = 0; ptCutIndex < sizeof(ptCut)/sizeof(*ptCut); ptCutIndex++)
            // Index which jet cut is currently applied
            for(int jetCutIndex = 0; jetCutIndex < sizeof(jetCut)/sizeof(*jetCut); jetCutIndex++)
            {
                //HistName to refer to
                TString histName = projLabel[projIndex]+"_"+jetCutLabel[jetCutIndex]+ptCutLabel[ptCutIndex]; 

                cout << endl;
                cout << endl;
                cout << "--------------------------------------------------------" << endl;
                cout << histName << endl;
                cout << "--------------------------------------------------------" << endl;
                cout << endl;
                cout << endl;

                //create hist to store data in. Naming after current projection, jetCut and ptCut. 100 Bins from -200 to 200 GeV 
                TH1D* histData = new TH1D(histName+"Data","",100,-200,200);

                cout << "Data Sample" << endl;
                //Iterate over each Data sample
                for(std::vector<TString>::iterator element = Data.begin(); element != Data.end(); element++)
                {
                    //fileName = <FileDir> + <Nickname>/<Nickname>.root
                    TString fileName = fileDir + *element + "/" + *element + ".root";
                    TFile * fileData   = new TFile(fileName);
                    if (!fileData->IsOpen())
                    {
                        cout << "File does not exist: " << fileName << endl;
                        return;
                    }
                    //Get Tree
                    TTree* tree = (TTree*)gDirectory->Get(channel + "/" + treeName);

                    //Draw Hist with defined Cuts on Pt and Jets and name it "histTemp". Same Binning as the histData histogram
                    tree->Draw(proj[projIndex] + ">>histTemp(100,-200,200)",ptCut[ptCutIndex]+"*"+jetCut[jetCutIndex]);
                    TH1D* histPart = (TH1D*)gDirectory->Get("histTemp");


                    //Add the temporary loaded File to the global histData with weight = 1
                    histData->Add(histData,histPart,1,1);

                    cout << "Sample: " << *element << " - Entries: " <<  histPart->GetSumOfWeights() <<  " - Whole " << histData->GetSumOfWeights() << endl;

                    //Delete temporary file
                    delete fileData;
                }






                cout << "Background Sample: " << endl;
                //Iterate over each Background sample and subtract it from the Data sample
                for(std::vector<TString>::iterator element = Bkg.begin(); element != Bkg.end(); element++)
                {
                    //fileName = <FileDir> + <Nickname>/<Nickname>.root
                    TString fileName = fileDir + *element + "/" + *element + ".root";
                    TFile * fileData   = new TFile(fileName);
                    if (!fileData->IsOpen())
                    {
                        cout << "File does not exist: " << fileName << endl;
                        return;
                    }

                    //Get Tree
                    TTree* tree = (TTree*)gDirectory->Get(channel + "/" + treeName);

                    //Draw Hist with defined Cuts on Pt and Jets and name it "histTemp". Same Binning as the histData histogram. Multiply events by their weight
                    tree->Draw(proj[projIndex] + ">>histTemp(100,-200,200)",ptCut[ptCutIndex]+"*"+jetCut[jetCutIndex]+"*weight");
                    TH1D* histPart = (TH1D*)gDirectory->Get("histTemp");

                    //Subtract the temporary loaded File from the global histData multiplied with the lumi section

                    histData->Add(histData,histPart,1,-lumi);
                    //histData->Add(histData,-histData,1,-lumi);

                    cout << "Sample: " << *element << " - Entries(weighted): " <<  histPart->GetSumOfWeights()*lumi <<  " - Whole " << histData->GetSumOfWeights() << endl;

                    //Delete temporary file
                    delete fileData;

                }


                cout << "Background WJet Samples: " << endl;
                //Iterate over each stitched Background WJet sample and subtract it from the Data sample
                for(std::vector<TString>::iterator element = BkgWJet.begin(); element != BkgWJet.end(); element++)
                {
                    //fileName = <FileDir> + <Nickname>/<Nickname>.root
                    TString fileName = fileDir + *element + "/" + *element + ".root";
                    TFile * fileData   = new TFile(fileName);
                    if (!fileData->IsOpen())
                    {
                        cout << "File does not exist: " << fileName << endl;
                        return;
                    }

                    //Get Tree
                    TTree* tree = (TTree*)gDirectory->Get(channel + "/" + treeName);

                    //Draw Hist with defined Cuts on Pt and Jets and name it "histTemp". Same Binning as the histData histogram. Multiply events by their weight
                    tree->Draw(proj[projIndex] + ">>histTemp(100,-200,200)",ptCut[ptCutIndex]+"*"+jetCut[jetCutIndex]+"*weight*" + wj_stitchingweight());
                    TH1D* histPart = (TH1D*)gDirectory->Get("histTemp");

                    //Subtract the temporary loaded File from the global histData multiplied with the lumi section
                    histData->Add(histData,histPart,1,-lumi);

                    cout << "Sample: " << *element << " - Entries(weighted): " <<  histPart->GetSumOfWeights()*lumi <<  " - Whole " << histData->GetSumOfWeights() << endl;

                    //Delete temporary file
                    delete fileData;

                }

                //create hist to store DY in. Naming after current projection, jetCut and ptCut. 100 Bins from -200 to 200 GeV 
                TH1D* histDY = new TH1D(histName+"DY","",100,-200,200);
                
                cout << "DY Sample: " << endl;
                //Iterate over each DY sample and add it up
                for(std::vector<TString>::iterator element = DY.begin(); element != DY.end(); element++)
                {
                    //fileName = <FileDir> + <Nickname>/<Nickname>.root
                    TString fileName = fileDir + *element + "/" + *element + ".root";
                    TFile * fileData   = new TFile(fileName);
                    if (!fileData->IsOpen())
                    {
                        cout << "File does not exist: " << fileName << endl;
                        return;
                    }

                    //Get Tree
                    TTree* tree = (TTree*)gDirectory->Get(channel + "/" + treeName);

                    //Draw Hist with defined Cuts on Pt and Jets and name it "histTempSig". Same Binning as the histDY histogram. Multiply events by their weight
                    //Also apply stitching on DY Samples and gen matching on mumu.
                    tree->Draw(proj[projIndex] + ">>histTempSig(100,-200,200)",ptCut[ptCutIndex] + "*" + jetCut[jetCutIndex] + "*weight*" + zll_genmatchMM() + "*" + zll_stitchingweight());
                    TH1D* histPartSig = (TH1D*)gDirectory->Get("histTempSig");

                    //Add the temporary loaded File to the global histDY multiplied with the lumi section
                    //histDY->Add(histDY,histPartSig,1,lumi);
                    histDY->Add(histDY,histPartSig,1,lumi);


                    //Background events from mumu coming from taus.
                    //Draw Hist with defined Cuts on Pt and Jets and name it "histTempBkg". Same Binning as the histDY histogram. Multiply events by their weight
                    //Also apply stitching on DY Samples and gen matching on tautau
                    tree->Draw(proj[projIndex] + ">>histTempBkg(100,-200,200)",ptCut[ptCutIndex] + "*" + jetCut[jetCutIndex] + "*weight*" + ztt_genmatchMM() + "*" + ztt_stitchingweight());
                    TH1D* histPartBkg = (TH1D*)gDirectory->Get("histTempBkg");


                    //Subtract the temporary loaded Bkg Data from the global histData multiplied with the lumi section
                    histData->Add(histData,histPartBkg,1,-lumi);

                    cout << "Sample Sig: " << *element << " - Entries(weighted): " <<  histPartSig->GetSumOfWeights()*lumi <<  " - Whole " << histDY->GetSumOfWeights() << endl;
                    cout << "Sample Bkg: " << *element << " - Entries(weighted): " <<  histPartBkg->GetSumOfWeights()*lumi <<  " - Whole " << histData->GetSumOfWeights() << endl;

                    //Delete temporary file
                    delete fileData;

                }
                cout << "DY Sample Events: " << histDY->GetEntries() << endl;
                cout << "Data Sample Events: " << histData->GetEntries() << endl;
                cout << "DY Sample Weights: " << histDY->GetSumOfWeights() << endl;
                cout << "Data Sample Weights: " << histData->GetSumOfWeights() << endl;

                //Create directory to save the Fitting results in
                TString makeDir = "mkdir " + baseString + Suffix;
                system(makeDir.Data());

                //Create additional directory to check for input in the channels
                makeDir = "mkdir " + baseString + Suffix + "/FitInput/";
                TString saveDir = baseString + Suffix + "/FitInput/";
                system(makeDir.Data());


                SaveInputPlot(histName, histData, histDY, saveDir, projIndex);

                bool fit = true;
                bool rebin = false;
                bool logY = false;
                int model = 2;
                TString xtit[2] = {"U_{1} [GeV]","U_{2} [GeV]"};
                if (projIndex==1) model = 3;
                //	int model = 3;
                FitRecoil(fileOutput,
                      baseString,
                      Suffix,
                      histData,
                      histDY,
                      histName,
                      -100,
                      100,
                      xtit[projIndex],
                      "Events",
                      -160,
                      160,
                      model,
                      rebin,
                      fit,
                      logY);

                delete histDY;
                delete histData;

            }
    fileOutput->Write();
    fileOutput->Close();

}



