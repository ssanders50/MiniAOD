void CentCompare_AOD_MiniAOD(){
  TFile * faod = new TFile("../CheckEP/check_TestAOD.root","read");
  TFile * fmini = new TFile("../CheckEP/check_MiniAOD.root","read");
  TH1D * hcentAOD = (TH1D *) faod->Get("checkflattening/centbins");
  TH1D * hcentMini = (TH1D *) fmini->Get("checkflattening/centbins");
  TCanvas * c = new TCanvas("centCheck","centCheck",1200,1000);
  c->cd();
  hcentMini->SetLineColor(kBlue);
  hcentMini->SetLineWidth(2);
  hcentMini->SetXTitle("Centrality Bin");
  hcentMini->SetYTitle("Counts");
  hcentAOD->SetLineColor(kRed);
  hcentMini->Draw();
  hcentAOD->Draw("same");
  TLegend * leg = new TLegend(.3,.6,.7,.8);
  leg->SetTextFont(43);
  leg->SetTextSize(28);
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  leg->AddEntry(hcentMini,"MiniAOD","lp");
  leg->AddEntry(hcentAOD,"AOD","lp");
  leg->Draw();
  cout<<"Yield difference: "<<hcentMini->Integral(1,hcentMini->GetNbinsX()) - hcentAOD->Integral(1,hcentAOD->GetNbinsX())<<endl;

}
