void VtxCompare_AOD_MiniAOD(){
  TFile * faod = new TFile("../CheckEP/check_TestAOD.root","read");
  TFile * fmini = new TFile("../CheckEP/check_MiniAOD.root","read");
  TH1D * hvtxAOD = (TH1D *) faod->Get("checkflattening/vtx");
  TH1D * hvtxMini = (TH1D *) fmini->Get("checkflattening/vtx");
  TH1D * hvtxAOD20 = (TH1D *) faod->Get("checkflattening/vtx20");
  TH1D * hvtxMini20 = (TH1D *) fmini->Get("checkflattening/vtx20");
  TCanvas * c = new TCanvas("vtxCheck","vtxCheck",1300,1000);
  c->Divide(2);
  c->cd(1);
  gPad->SetLogy();
  hvtxMini->SetLineColor(kBlue);
  hvtxMini->SetLineWidth(2);
  hvtxMini->SetXTitle("Vertex (cm)");
  hvtxMini->SetYTitle("Counts");
  hvtxAOD->SetLineColor(kRed);
  hvtxMini->Draw();
  hvtxAOD->Draw("same");
  TLegend * leg = new TLegend(.25,.65,.45,.8);
  leg->SetTextFont(43);
  leg->SetTextSize(28);
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  leg->AddEntry(hvtxMini,"MiniAOD","lp");
  leg->AddEntry(hvtxAOD,"AOD","lp");
  leg->Draw();

  c->cd(2);
  gPad->SetLogy();
  hvtxMini20->SetLineColor(kBlue);
  hvtxMini20->SetLineWidth(2);
  hvtxMini20->SetXTitle("Vertex (cm)");
  hvtxMini20->SetYTitle("Counts");
  hvtxAOD20->SetLineColor(kRed);
  hvtxMini20->Draw();
  hvtxAOD20->Draw("same");

}
