#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#include <string.h>


//Stitching weights for Z->tautau events
TString ztt_stitchingweight()
{
    TString  highmass = "((genbosonmass >= 150.0 && (npartons == 0 || npartons >= 5))*3.95423374e-5) + ((genbosonmass >= 150.0 && npartons == 1)*1.27486147e-5) + ((genbosonmass >= 150.0 && npartons == 2)*1.3012785e-5) + ((genbosonmass >= 150.0 && npartons == 3)*1.33802133e-5) + ((genbosonmass >= 150.0 && npartons == 4)*1.09698723e-5)+";
    TString mediummass = "((genbosonmass >= 50.0 && genbosonmass < 150.0 && (npartons == 0 || npartons >= 5))*3.95423374e-5) + ((genbosonmass >= 50.0 && genbosonmass < 150.0 && npartons == 1)*1.27486147e-5) + ((genbosonmass >= 50.0 && genbosonmass < 150.0 && npartons == 2)*1.3012785e-5) + ((genbosonmass >= 50.0 && genbosonmass < 150.0 && npartons == 3)*1.33802133e-5) + ((genbosonmass >= 50.0 && genbosonmass < 150.0 && npartons == 4)*1.09698723e-5)+";
    TString lowmass = "((genbosonmass < 50.0)*numberGeneratedEventsWeight*crossSectionPerEventWeight)";
    TString normalization = "/(numberGeneratedEventsWeight*crossSectionPerEventWeight*sampleStitchingWeight)";
    return "("+highmass+mediummass+lowmass+")"+normalization;
}

//Stitching weights for Z->ll events
TString zll_stitchingweight()
{
    TString mediummass = "((genbosonmass >= 50.0 && (npartons == 0 || npartons >= 5))*3.95423374e-5) + ((genbosonmass >= 50.0 && npartons == 1)*1.27486147e-5) + ((genbosonmass >= 50.0 && npartons == 2)*1.3012785e-5) + ((genbosonmass >= 50.0 && npartons == 3)*1.33802133e-5) + ((genbosonmass >= 50.0 && npartons == 4)*1.09698723e-5)+";
    TString lowmass = "((genbosonmass < 50.0)*numberGeneratedEventsWeight*crossSectionPerEventWeight)";
    TString normalization = "/(numberGeneratedEventsWeight*crossSectionPerEventWeight*sampleStitchingWeight)";
    return "("+mediummass+lowmass+")"+normalization;
}

//Stitching weights for WJet Samples
TString wj_stitchingweight()
{
    return "(((npartons == 0 || npartons >= 5)*7.09390278348407e-4) + ((npartons == 1)*1.90063898596475e-4) + ((npartons == 2)*5.8529964471165e-5) + ((npartons == 3)*1.9206444928444e-5) + ((npartons == 4)*1.923548021385e-5))/(numberGeneratedEventsWeight*crossSectionPerEventWeight*sampleStitchingWeight)";
}

//Gen matching for muons being prompt muons
TString zll_genmatchMM()
{
    return "(gen_match_1 < 3 || gen_match_2 < 3)";
}

//Gen matching for muons coming from taus
TString ztt_genmatchMM()
{
    return "(gen_match_1 > 3 && gen_match_2 > 3)";
}

void SaveInputPlot(TString histName, TH1D *histData, TH1D *histDY, TString saveDir, int projIndex)
{

    histData->SetLineColor(2);
    histData->SetMarkerColor(2);
    histData->SetMarkerStyle(20);
    histData->SetMarkerSize(0.8);
    //hist1->GetXaxis()->SetRangeUser(xminA,xmaxA);
    histDY->SetLineColor(4);
    histDY->SetMarkerColor(4);
    histDY->SetMarkerStyle(21);
    histDY->SetMarkerSize(0.8);

    //Normalize Plots
    histData->Scale(1/histData->GetSumOfWeights());
    histDY->Scale(1/histDY->GetSumOfWeights());

    /*
    //Bin output
    for (int i = 0 ; i < 100; i++)
    {
        cout << "Bin: " << i << " - DY   - "  << histDY->GetBinContent(i) << endl;
        cout << "Bin: " << i << " - Data - "  << histData->GetBinContent(i) << endl;
    }
    */


    TString xtit[2] = {"U_{1} [GeV]","U_{2} [GeV]"};
    TCanvas * canvControl = new TCanvas("canvControl","",700,700);
    histData->GetXaxis()->SetTitle(xtit[projIndex]);
    histData->GetXaxis()->SetTitleOffset(1.1);
    histData->GetYaxis()->SetTitle("Events");
    histData->GetYaxis()->SetTitleOffset(2);
    histData->Draw("e1");
    histDY->Draw("e1same");

    canvControl->SetGridx();
    canvControl->SetGridy();
    canvControl->SetLogy(true);
    canvControl->Update();
    TLegend * leg = new TLegend(0.67,0.72,0.95,0.92);
    leg->SetFillColor(0);
    leg->SetTextSize(0.04);
    TString jetLeg("    N_{jets} = 0 ");
    if (histName.Contains("NJet1"))
        jetLeg = "    N_{jets} = 1 ";
    if (histName.Contains("NJetGe2"))
        jetLeg = "    N_{jets} > 1 ";
    TString ptLeg("[0,10] GeV");
    if (histName.Contains("Pt10to20"))
        ptLeg = "[10,20] GeV";
    if (histName.Contains("Pt20to30"))
        ptLeg = "[20,30] GeV";
    if (histName.Contains("Pt30to50"))
        ptLeg = "[30,50] GeV";
    if (histName.Contains("PtGt50"))
        ptLeg = "> 50 GeV";
    TString header = jetLeg + ptLeg;
    TH1D * dummy = new TH1D("dummy","",1,0,1);
    dummy->SetLineColor(0);
    leg->SetHeader(jetLeg);
    leg->AddEntry(dummy,ptLeg,"l");
    leg->AddEntry(histData,"Data","lp");
    leg->AddEntry(histDY,"DY","lp");
    leg->Draw();
    canvControl->Print(saveDir + histName + "_Input.png");
    cout << "DY Entries: " << histDY->GetEntries() << endl;
    cout << "Data Entries: " << histData->GetEntries() << endl;

}

