# include <iostream>
# include <iterator>
# include <fstream>
# include <map>
# include <sstream> 
# include <string>
# include <utility>
# include <vector>

# include <CLHEP/Vector/ThreeVector.h>
# include <CLHEP/Vector/LorentzVector.h>

# include <TFile.h>
# include <TH1F.h>
# include <TH2F.h>
# include <TTree.h>

# include "InputData_DTNtuple.h"
# include "Common.h"


int str_len = 500;

int nWheel = 5;
int nStation = 4;
int nSector = 12;

double mu_pTcut = 0; // GeV
double mu_etaCut = 3;

double BMTF_pTcut = 25; // GeV
double BMTF_etaCut = 0.83;

double MB1_pTcut = 0; // GeV

int DTsegment_nHit_phiLocal_min = 4;
int DTsegment_phiLocal_max = 45; // degree

int HOTP_bits_SOI = 4;

int MB1_HO_deltaIphiCut = 0;

double muBMTF_deltaRcut = 0.4;
double muMB1_deltaRcut = 0.4;
double muMB1_deltaEtaCut = 1.5 * 2.0*M_PI/72.0;
double muMB1_deltaPhiCut = 1.5 * 2.0*M_PI/72.0;

std::vector <int> v_phiB;
std::vector <double> v_pT;



class OutputData
{
    public:
    
    //
    TH1F *h1_mu_pT;
    TH1F *h1_mu_eta;
    TH1F *h1_mu_phi;
    
    TH2F *h2_mu_eta_vs_phi;
    TH2F *h2_mu_pT_vs_eta;
    TH2F *h2_mu_pT_vs_phi;
    
    
    //
    TH1F *h1_BMTF_mu_deltaPt;
    
    TH1F *h1_BMTF_mu_deltaEta;
    TH1F *h1_BMTF_mu_deltaPhi;
    TH1F *h1_BMTF_mu_deltaR;
    
    TH1F *h1_BMTF_muMatched_pT;
    TH1F *h1_BMTF_muMatched_eta;
    TH1F *h1_BMTF_muMatched_phi;
    
    TH1F *h1_BMTF_muMatched_deltaEta;
    TH1F *h1_BMTF_muMatched_deltaPhi;
    
    TH2F *h2_BMTF_muMatched_eta_vs_phi;
    TH2F *h2_BMTF_muMatched_pT_vs_eta;
    TH2F *h2_BMTF_muMatched_pT_vs_phi;
    
    
    //
    TH1F *h1_BMTF_muNotMatched_pT;
    TH1F *h1_BMTF_muNotMatched_eta;
    TH1F *h1_BMTF_muNotMatched_phi;
    
    TH2F *h2_BMTF_muNotMatched_eta_vs_phi;
    TH2F *h2_BMTF_muNotMatched_pT_vs_eta;
    TH2F *h2_BMTF_muNotMatched_pT_vs_phi;
    
    
    //
    TH1F *h1_MB1_BMTF_deltaPhi;
    
    
    //
    TH1F *h1_MB1_isoType;
    
    
    //
    TH1F *h1_isoMB1HO_deltaIphi;
    
    TH1F *h1_isoMB1HO_mu_deltaPt;
    
    TH1F *h1_isoMB1HO_muMatched_pT;
    TH1F *h1_isoMB1HO_muMatched_eta;
    TH1F *h1_isoMB1HO_muMatched_phi;
    
    TH2F *h2_isoMB1HO_muMatched_eta_vs_phi;
    TH2F *h2_isoMB1HO_muMatched_pT_vs_eta;
    TH2F *h2_isoMB1HO_muMatched_pT_vs_phi;
    
    
    //
    TH1F *h1_isoMB1HO_muNotMatched_pT;
    TH1F *h1_isoMB1HO_muNotMatched_eta;
    TH1F *h1_isoMB1HO_muNotMatched_phi;
    
    TH2F *h2_isoMB1HO_muNotMatched_eta_vs_phi;
    TH2F *h2_isoMB1HO_muNotMatched_pT_vs_eta;
    TH2F *h2_isoMB1HO_muNotMatched_pT_vs_phi;
    
    
    //
    TH1F *h1_test1;
    TH1F *h1_test1a;
    
    TH1F *h1_test2;
    TH1F *h1_test2a;
    
    TH1F *h1_test3;
    TH1F *h1_test3a;
    
    
    OutputData()
    {
        char histName[str_len];
        char histTitle[str_len];
        
        double pT_min = 0;
        double pT_max = 1000;
        int nBin_pT = 200;
        
        double eta_min = -3;
        double eta_max = 3;
        int nBin_eta = 68;
        //int nBin_eta = 136;
        
        double phi_min = -M_PI;
        double phi_max = M_PI;
        int nBin_phi = 72;
        
        double deltaR_min = 0;
        double deltaR_max = 3;
        int nBin_deltaR = 60;
        
        //
        h1_mu_pT = new TH1F("mu_pT", "mu_pT", nBin_pT, pT_min, pT_max);
        h1_mu_eta = new TH1F("mu_eta", "mu_eta", nBin_eta, eta_min, eta_max);
        h1_mu_phi = new TH1F("mu_phi", "mu_phi", nBin_phi, phi_min, phi_max);
        
        h2_mu_eta_vs_phi = new TH2F("mu_eta_vs_phi", "mu_eta_vs_phi", nBin_phi, phi_min, phi_max, nBin_eta, eta_min, eta_max);
        h2_mu_pT_vs_eta = new TH2F("mu_pT_vs_eta", "mu_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_mu_pT_vs_phi = new TH2F("mu_pT_vs_phi", "mu_pT_vs_phi", nBin_phi, phi_min, phi_max, nBin_pT, pT_min, pT_max);
        
        
        //
        h1_BMTF_mu_deltaPt = new TH1F("BMTF_mu_deltaPt", "BMTF_mu_deltaPt", 200, -100, 100);
        
        h1_BMTF_mu_deltaEta = new TH1F("BMTF_mu_deltaEta", "BMTF_mu_deltaEta", 2*nBin_eta, eta_min, eta_max);
        h1_BMTF_mu_deltaPhi = new TH1F("BMTF_mu_deltaPhi", "BMTF_mu_deltaPhi", 2*nBin_phi, phi_min, phi_max);
        h1_BMTF_mu_deltaR = new TH1F("BMTF_mu_deltaR", "BMTF_mu_deltaR", nBin_deltaR, deltaR_min, deltaR_max);
        
        h1_BMTF_muMatched_pT = new TH1F("BMTF_muMatched_pT", "BMTF_muMatched_pT", nBin_pT, pT_min, pT_max);
        h1_BMTF_muMatched_eta = new TH1F("BMTF_muMatched_eta", "BMTF_muMatched_eta", nBin_eta, eta_min, eta_max);
        h1_BMTF_muMatched_phi = new TH1F("BMTF_muMatched_phi", "BMTF_muMatched_phi", nBin_phi, phi_min, phi_max);
        
        h1_BMTF_muMatched_deltaEta = new TH1F("BMTF_muMatched_deltaEta", "BMTF_muMatched_deltaEta", 2*nBin_eta, eta_min, eta_max);
        h1_BMTF_muMatched_deltaPhi = new TH1F("BMTF_muMatched_deltaPhi", "BMTF_muMatched_deltaPhi", 2*nBin_phi, phi_min, phi_max);
        
        h2_BMTF_muMatched_eta_vs_phi = new TH2F("BMTF_muMatched_eta_vs_phi", "BMTF_muMatched_eta_vs_phi", nBin_phi, phi_min, phi_max, nBin_eta, eta_min, eta_max);
        h2_BMTF_muMatched_pT_vs_eta = new TH2F("BMTF_muMatched_pT_vs_eta", "BMTF_muMatched_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_BMTF_muMatched_pT_vs_phi = new TH2F("BMTF_muMatched_pT_vs_phi", "BMTF_muMatched_pT_vs_phi", nBin_phi, phi_min, phi_max, nBin_pT, pT_min, pT_max);
        
        
        //
        h1_BMTF_muNotMatched_pT = new TH1F("BMTF_muNotMatched_pT", "BMTF_muNotMatched_pT", nBin_pT, pT_min, pT_max);
        h1_BMTF_muNotMatched_eta = new TH1F("BMTF_muNotMatched_eta", "BMTF_muNotMatched_eta", nBin_eta, eta_min, eta_max);
        h1_BMTF_muNotMatched_phi = new TH1F("BMTF_muNotMatched_phi", "BMTF_muNotMatched_phi", nBin_phi, phi_min, phi_max);
        
        h2_BMTF_muNotMatched_eta_vs_phi = new TH2F("BMTF_muNotMatched_eta_vs_phi", "BMTF_muNotMatched_eta_vs_phi", nBin_phi, phi_min, phi_max, nBin_eta, eta_min, eta_max);
        h2_BMTF_muNotMatched_pT_vs_eta = new TH2F("BMTF_muNotMatched_pT_vs_eta", "BMTF_muNotMatched_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_BMTF_muNotMatched_pT_vs_phi = new TH2F("BMTF_muNotMatched_pT_vs_phi", "BMTF_muNotMatched_pT_vs_phi", nBin_phi, phi_min, phi_max, nBin_pT, pT_min, pT_max);
        
        
        //
        h1_MB1_BMTF_deltaPhi = new TH1F("MB1_BMTF_deltaPhi", "MB1_BMTF_deltaPhi", 2*nBin_phi, phi_min, phi_max);
        
        
        //
        h1_MB1_isoType = new TH1F("MB1_isoType", "MB1_isoType", 5, -2, 3);
        
        //
        h1_isoMB1HO_deltaIphi = new TH1F("isoMB1HO_deltaIphi", "isoMB1HO_deltaIphi", 20, -10, 10);
        
        h1_isoMB1HO_mu_deltaPt = new TH1F("isoMB1HO_mu_deltaPt", "isoMB1HO_mu_deltaPt", 200, -100, 100);
        
        h1_isoMB1HO_muMatched_pT = new TH1F("isoMB1HO_muMatched_pT", "isoMB1HO_muMatched_pT", nBin_pT, pT_min, pT_max);
        h1_isoMB1HO_muMatched_eta = new TH1F("isoMB1HO_muMatched_eta", "isoMB1HO_muMatched_eta", nBin_eta, eta_min, eta_max);
        h1_isoMB1HO_muMatched_phi = new TH1F("isoMB1HO_muMatched_phi", "isoMB1HO_muMatched_phi", nBin_phi, phi_min, phi_max);
        
        h2_isoMB1HO_muMatched_eta_vs_phi = new TH2F("isoMB1HO_muMatched_eta_vs_phi", "isoMB1HO_muMatched_eta_vs_phi", nBin_phi, phi_min, phi_max, nBin_eta, eta_min, eta_max);
        h2_isoMB1HO_muMatched_pT_vs_eta = new TH2F("isoMB1HO_muMatched_pT_vs_eta", "isoMB1HO_muMatched_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_isoMB1HO_muMatched_pT_vs_phi = new TH2F("isoMB1HO_muMatched_pT_vs_phi", "isoMB1HO_muMatched_pT_vs_phi", nBin_phi, phi_min, phi_max, nBin_pT, pT_min, pT_max);
        
        
        //
        h1_isoMB1HO_muNotMatched_pT = new TH1F("isoMB1HO_muNotMatched_pT", "isoMB1HO_muNotMatched_pT", nBin_pT, pT_min, pT_max);
        h1_isoMB1HO_muNotMatched_eta = new TH1F("isoMB1HO_muNotMatched_eta", "isoMB1HO_muNotMatched_eta", nBin_eta, eta_min, eta_max);
        h1_isoMB1HO_muNotMatched_phi = new TH1F("isoMB1HO_muNotMatched_phi", "isoMB1HO_muNotMatched_phi", nBin_phi, phi_min, phi_max);
        
        h2_isoMB1HO_muNotMatched_eta_vs_phi = new TH2F("isoMB1HO_muNotMatched_eta_vs_phi", "isoMB1HO_muNotMatched_eta_vs_phi", nBin_phi, phi_min, phi_max, nBin_eta, eta_min, eta_max);
        h2_isoMB1HO_muNotMatched_pT_vs_eta = new TH2F("isoMB1HO_muNotMatched_pT_vs_eta", "isoMB1HO_muNotMatched_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_isoMB1HO_muNotMatched_pT_vs_phi = new TH2F("isoMB1HO_muNotMatched_pT_vs_phi", "isoMB1HO_muNotMatched_pT_vs_phi", nBin_phi, phi_min, phi_max, nBin_pT, pT_min, pT_max);
        
        
        //
        h1_test1 = new TH1F("test1", "test1", 50, 0, 50);
        h1_test1->SetLabelSize(0.025, "x");
        
        h1_test1a = new TH1F("test1a", "test1a", 50, 0, 50);
        h1_test1a->SetLabelSize(0.025, "x");
        
        //
        h1_test2 = new TH1F("test2", "test2", 120, 0, 120);
        h1_test2->SetLabelSize(0.02, "x");
        
        h1_test2a = new TH1F("test2a", "test2a", 180, 0, 180);
        h1_test2a->SetLabelSize(0.015, "x");
        
        for(int iEta = 0; iEta < 4; iEta++)
        {
            for(int iMask = 1; iMask < 16; iMask++)
            {
                std::string binLabel = "MB ";
                
                for(int iStation = 0; iStation < 4; iStation++)
                {
                    if(iMask & (1<<(iStation)))
                    {
                        binLabel += std::to_string(iStation+1);
                    }
                }
                
                h1_test2->GetXaxis()->SetBinLabel(iEta*25 + iMask+1, binLabel.c_str());
                h1_test2->GetXaxis()->SetBinLabel(iEta*25 + 1, "none");
                
                h1_test2a->GetXaxis()->SetBinLabel(iEta*2*20 + 0*20 + iMask+1, binLabel.c_str());
                h1_test2a->GetXaxis()->SetBinLabel(iEta*2*20 + 0*20 + 1, "none");
                
                h1_test2a->GetXaxis()->SetBinLabel(iEta*2*20 + 1*20 + iMask+1, binLabel.c_str());
                h1_test2a->GetXaxis()->SetBinLabel(iEta*2*20 + 1*20 + 1, "none");
            }
        }
        
        //
        h1_test3 = new TH1F("test3", "test3", 50, 0, 50);
        h1_test3->SetLabelSize(0.025, "x");
        
        h1_test3a = new TH1F("test3a", "test3a", 50, 0, 50);
        h1_test3a->SetLabelSize(0.025, "x");
        
        for(int iStation = 0; iStation < 4; iStation++)
        {
            for(int iEta = 1; iEta <= 4; iEta++)
            {
                std::string binLabel;
                
                binLabel = "MB " + std::to_string(iStation+1);
                h1_test1->GetXaxis()->SetBinLabel((iEta-1)*10 + iStation+1+1, binLabel.c_str());
                
                h1_test1a->GetXaxis()->SetBinLabel((iEta-1)*2*6 + 0*6 + iStation+1+1, binLabel.c_str());
                h1_test1a->GetXaxis()->SetBinLabel((iEta-1)*2*6 + 1*6 + iStation+1+1, binLabel.c_str());
                
                
                binLabel = "i#eta" + std::to_string(iEta);
                h1_test3->GetXaxis()->SetBinLabel(iStation*10 + iEta+1, binLabel.c_str());
                
                binLabel = "i#eta" + std::to_string(iEta) + "/1";
                h1_test3a->GetXaxis()->SetBinLabel(iStation*10 + iEta*2-1+1, binLabel.c_str());
                
                binLabel = "i#eta" + std::to_string(iEta) + "/2";
                h1_test3a->GetXaxis()->SetBinLabel(iStation*10 + iEta*2-0+1, binLabel.c_str());
            }
        }
        
        
        h1_test1->LabelsOption("v", "x");
        h1_test1a->LabelsOption("v", "x");
        
        h1_test2->LabelsOption("v", "x");
        h1_test2a->LabelsOption("v", "x");
        
        h1_test3->LabelsOption("v", "x");
        h1_test3a->LabelsOption("v", "x");
    }
    
    
    void writeData()
    {
        //
        h1_mu_pT->Write();
        h1_mu_eta->Write();
        h1_mu_phi->Write();
        
        h2_mu_eta_vs_phi->Write();
        h2_mu_pT_vs_eta->Write();
        h2_mu_pT_vs_phi->Write();
        
        
        //
        h1_BMTF_mu_deltaPt->Write();
        
        h1_BMTF_mu_deltaEta->Write();
        h1_BMTF_mu_deltaPhi->Write();
        h1_BMTF_mu_deltaR->Write();
        
        h1_BMTF_muMatched_pT->Write();
        h1_BMTF_muMatched_eta->Write();
        h1_BMTF_muMatched_phi->Write();
        
        h1_BMTF_muMatched_deltaEta->Write();
        h1_BMTF_muMatched_deltaPhi->Write();
        
        h2_BMTF_muMatched_eta_vs_phi->Write();
        h2_BMTF_muMatched_pT_vs_eta->Write();
        h2_BMTF_muMatched_pT_vs_phi->Write();
        
        
        //
        h1_BMTF_muNotMatched_pT->Write();
        h1_BMTF_muNotMatched_eta->Write();
        h1_BMTF_muNotMatched_phi->Write();
        
        h2_BMTF_muNotMatched_eta_vs_phi->Write();
        h2_BMTF_muNotMatched_pT_vs_eta->Write();
        h2_BMTF_muNotMatched_pT_vs_phi->Write();
        
        
        //
        h1_MB1_BMTF_deltaPhi->Write();
        
        
        //
        h1_MB1_isoType->Write();
        
        
        //
        h1_isoMB1HO_deltaIphi->Write();
        
        h1_isoMB1HO_mu_deltaPt->Write();
        
        h1_isoMB1HO_muMatched_pT->Write();
        h1_isoMB1HO_muMatched_eta->Write();
        h1_isoMB1HO_muMatched_phi->Write();
        
        h2_isoMB1HO_muMatched_eta_vs_phi->Write();
        h2_isoMB1HO_muMatched_pT_vs_eta->Write();
        h2_isoMB1HO_muMatched_pT_vs_phi->Write();
        
        
        //
        h1_isoMB1HO_muNotMatched_pT->Write();
        h1_isoMB1HO_muNotMatched_eta->Write();
        h1_isoMB1HO_muNotMatched_phi->Write();
        
        h2_isoMB1HO_muNotMatched_eta_vs_phi->Write();
        h2_isoMB1HO_muNotMatched_pT_vs_eta->Write();
        h2_isoMB1HO_muNotMatched_pT_vs_phi->Write();
        
        
        //
        h1_test1->Write();
        h1_test1a->Write();
        
        h1_test2->Write();
        h1_test2a->Write();
        
        h1_test3->Write();
        h1_test3a->Write();
    }
    
    
    void freeMemory()
    {
        //
        delete h1_mu_pT;
        delete h1_mu_eta;
        delete h1_mu_phi;
        
        delete h2_mu_eta_vs_phi;
        delete h2_mu_pT_vs_eta;
        delete h2_mu_pT_vs_phi;
        
        
        //
        delete h1_BMTF_mu_deltaPt;
        
        delete h1_BMTF_mu_deltaEta;
        delete h1_BMTF_mu_deltaPhi;
        delete h1_BMTF_mu_deltaR;
        
        delete h1_BMTF_muMatched_pT;
        delete h1_BMTF_muMatched_eta;
        delete h1_BMTF_muMatched_phi;
        
        delete h1_BMTF_muMatched_deltaEta;
        delete h1_BMTF_muMatched_deltaPhi;
        
        delete h2_BMTF_muMatched_eta_vs_phi;
        delete h2_BMTF_muMatched_pT_vs_eta;
        delete h2_BMTF_muMatched_pT_vs_phi;
        
        
        //
        delete h1_BMTF_muNotMatched_pT;
        delete h1_BMTF_muNotMatched_eta;
        delete h1_BMTF_muNotMatched_phi;
        
        delete h2_BMTF_muNotMatched_eta_vs_phi;
        delete h2_BMTF_muNotMatched_pT_vs_eta;
        delete h2_BMTF_muNotMatched_pT_vs_phi;
        
        
        //
        delete h1_MB1_BMTF_deltaPhi;
        
        
        //
        delete h1_MB1_isoType;
        
        
        //
        delete h1_isoMB1HO_deltaIphi;
        
        delete h1_isoMB1HO_mu_deltaPt;
        
        delete h1_isoMB1HO_muMatched_pT;
        delete h1_isoMB1HO_muMatched_eta;
        delete h1_isoMB1HO_muMatched_phi;
        
        delete h2_isoMB1HO_muMatched_eta_vs_phi;
        delete h2_isoMB1HO_muMatched_pT_vs_eta;
        delete h2_isoMB1HO_muMatched_pT_vs_phi;
        
        
        //
        delete h1_isoMB1HO_muNotMatched_pT;
        delete h1_isoMB1HO_muNotMatched_eta;
        delete h1_isoMB1HO_muNotMatched_phi;
        
        delete h2_isoMB1HO_muNotMatched_eta_vs_phi;
        delete h2_isoMB1HO_muNotMatched_pT_vs_eta;
        delete h2_isoMB1HO_muNotMatched_pT_vs_phi;
        
        
        //
        delete h1_test1;
        delete h1_test1a;
        
        delete h1_test2;
        delete h1_test2a;
        
        delete h1_test3;
        delete h1_test3a;
    }
};


void analyze(InputData_DTNtuple::InputData *input, OutputData *output, OutputData *output_LQ, OutputData *output_HQ);


int main()
{
    std::string process;
    process = "SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO";
    
    // Read phiB vs. pT
    Common::parseCSV_pTlut("ptb12h_Feb2016.lut", &v_phiB, &v_pT);
    
    char sourceFileList[500];
    sprintf(sourceFileList, "sourceFiles/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO.txt");
    printf("Source file list: %s \n", sourceFileList);
    
    std::vector <std::string> v_sourceFileName = {};
    
    // Read source file list
    std::ifstream fileData(sourceFileList);
    std::string line;
    
    while(std::getline(fileData, line))
    {
        v_sourceFileName.push_back(line);
    }
    
    fileData.close();
    
    char outputDir[500];
    sprintf(outputDir, "output/%s", process.c_str());
    
    // Make output directory
    char command[500];
    sprintf(command, "mkdir -p %s", outputDir);
    system(command);
    
    int n = 0;
    // Analyze input files
    for(int iFile = 0; iFile < v_sourceFileName.size(); iFile++)
    {
        n++; if(n > 25) break; 
        std::string inputFileName = v_sourceFileName.at(iFile);
        
        printf("Input file: %s \n", inputFileName.c_str());
        InputData_DTNtuple::InputData *input = new InputData_DTNtuple::InputData(inputFileName.c_str());
        
        char fileNameStripped[500];
        sprintf(fileNameStripped, "%s", \
            (inputFileName.substr(inputFileName.rfind("/")+1, inputFileName.rfind(".root")-inputFileName.rfind("/")-1)).c_str());
        
        char outputFileName[500];
        sprintf(outputFileName, "%s/%s_efficiency.root", outputDir, fileNameStripped);
        
        printf("Output file: %s \n", outputFileName);
        TFile *outputFile = TFile::Open(outputFileName, "RECREATE");
        
        OutputData *output = new OutputData();
        OutputData *output_LQ = new OutputData();
        OutputData *output_HQ = new OutputData();
        
        analyze(input, output, output_LQ, output_HQ);
        
        outputFile->cd();
        output->writeData();
        output->freeMemory();
        
        outputFile->mkdir("LQ");
        outputFile->cd("LQ");
        output_LQ->writeData();
        output_LQ->freeMemory();
        
        outputFile->mkdir("HQ");
        outputFile->cd("HQ");
        output_HQ->writeData();
        output_HQ->freeMemory();
        
        outputFile->Close();
        delete outputFile;
        
        delete output;
        delete output_LQ;
        delete output_HQ;
        
        input->freeMemory();
        delete input;
        
        printf("\n");
    }
    
    
    printf("***** Run complete ***** \n");
    
    return 0;
}


void analyze(InputData_DTNtuple::InputData *input, OutputData *output, OutputData *output_LQ, OutputData *output_HQ)
{
    int nEvent = input->tree->GetEntries();
    
    for(int iEvent = 0; iEvent < nEvent; iEvent++)
    {
        if((iEvent+1) % 1000 == 0 || iEvent+1 == nEvent)
        {
            printf("********** Event %d / %d ********** \n", iEvent+1, nEvent);
            
            fflush(stdout);
        }
        
        
        int entryStatus = input->tree->GetEntry(iEvent);
        
        OutputData *currentOutput = 0;
        
        // Store best DT reco segment in each wh/st/sc
        /*std::vector <int> av_bestDTsegment_index[nWheel][nStation][nSector];
        //int a_bestDTsegment_nHit_phiLocal[nWheel][nStation][nSector];
        
        for(int iWheel = 0; iWheel < nWheel; iWheel++)
        {
            for(int iStation = 0; iStation < nStation; iStation++)
            {
                for(int iSector = 0; iSector < nSector; iSector++)
                {
                    av_bestDTsegment_index[iWheel][iStation][iSector] = {};
                    //a_bestDTsegment_nHit_phiLocal[iWheel][iStation][iSector] = 0;
                }
            }
        }
        
        OutputData *currentOutput = 0;
        
        int nDTsegment = input->v_dtsegm4D_wheel->size();
        
        
        
        for(int iDTsegment = 0; iDTsegment < nDTsegment; iDTsegment++)
        {
            int wheelNumber = input->v_dtsegm4D_wheel->at(iDTsegment);
            int stationNumber = input->v_dtsegm4D_station->at(iDTsegment);
            int sectorNumber = input->v_dtsegm4D_sector->at(iDTsegment);
            
            
            // MB4 sectors 4 (top) and 10 (bottom) are made up of two parts (divided vertically in the middle)
            // sector 4 is 4/1 and sector 13 is 4/2
            // sector 10 is 10/1 and sector 14 is 10/2
            sectorNumber = (sectorNumber > 12)? ((sectorNumber == 13)? 4: 10): sectorNumber;
            
            
            // Convert to array-index
            wheelNumber += 2;
            stationNumber--;
            sectorNumber--;
            
            int nHit_phiLocal = 0;
            int nHit_zLocal = 0;
            
            // Must have phi-projection, and if not MB4, then also z-projection
            if(input->v_dtsegm4D_hasPhi->at(iDTsegment) \
                && (input->v_dtsegm4D_hasZed->at(iDTsegment) || stationNumber+1 == 4))
            {
                nHit_phiLocal = input->v_dtsegm4D_phinhits->at(iDTsegment);
                
                double tan_phiLocal = input->v_dtsegm4D_x_dir_loc->at(iDTsegment) / input->v_dtsegm4D_z_dir_loc->at(iDTsegment);
                double phiLocal = atan(tan_phiLocal) * 180/M_PI;
                
                // Cut on the number of hits in an angular region
                if(nHit_phiLocal >= DTsegment_nHit_phiLocal_min && fabs(phiLocal) < DTsegment_phiLocal_max)
                {
                    av_bestDTsegment_index[wheelNumber][stationNumber][sectorNumber].push_back(iDTsegment);
                    
                    //if(nHit_phiLocal > a_bestDTsegment_nHit_phiLocal[wheelNumber][stationNumber][sectorNumber])
                    //{
                    //    a_bestDTsegment_index[wheelNumber][stationNumber][sectorNumber] = iDTsegment;
                    //    //a_bestDTsegment_nHit_phiLocal[wheelNumber][stationNumber][sectorNumber] = nHit_phiLocal;
                    //}
                }
            }
        }*/
        
        
        // select reco-muons
        std::vector <int> v_selectedMuon_pos;
        std::vector <double> v_selectedMuon_pT;
        std::vector <double> v_selectedMuon_eta;
        std::vector <double> v_selectedMuon_phi;
        
        int nMuon = input->v_Mu_eta->size();
        
        for(int iMuon = 0; iMuon < nMuon; iMuon++)
        {
            // Muon must be Global and Tracker
            //if(!input->v_Mu_isMuGlobal->at(iMuon) || !input->v_Mu_isMuTracker->at(iMuon))
            //{
            //    continue;
            //}
            
            if(!input->v_Mu_isMuTight->at(iMuon))
            {
                continue;
            }
            
            double pT_iMuon = sqrt(pow(input->v_Mu_px->at(iMuon), 2) + pow(input->v_Mu_py->at(iMuon), 2));
            double eta_iMuon = input->v_Mu_eta->at(iMuon);
            double phi_iMuon = input->v_Mu_phi->at(iMuon);
            
            // Muon pT, eta cut
            if(pT_iMuon < mu_pTcut || fabs(eta_iMuon) > mu_etaCut)
            {
                continue;
            }
            
            v_selectedMuon_pos.push_back(iMuon);
            v_selectedMuon_pT.push_back(pT_iMuon);
            v_selectedMuon_eta.push_back(eta_iMuon);
            v_selectedMuon_phi.push_back(phi_iMuon);
            
            // Fill reco-muon quantities
            output->h1_mu_pT->Fill(pT_iMuon);
            output->h1_mu_eta->Fill(eta_iMuon);
            output->h1_mu_phi->Fill(phi_iMuon);
            
            output->h2_mu_pT_vs_eta->Fill(eta_iMuon, pT_iMuon);
            output->h2_mu_pT_vs_phi->Fill(phi_iMuon, pT_iMuon);
            output->h2_mu_eta_vs_phi->Fill(phi_iMuon, eta_iMuon);
            
            int iEta_iMuon = Common::etaToIeta(eta_iMuon);
            int subIeta_iMuon = Common::etaToSubIeta(eta_iMuon, 2);
            
            if(abs(iEta_iMuon) <= 4)
            {
                // Run over LQ (0), HQ (1), LQ+HQ (2)
                for(int iQua = 0; iQua < 3; iQua++)
                {
                    if(iQua == 0)
                    {
                        currentOutput = output_LQ;
                    }
                    
                    else if(iQua == 1)
                    {
                        currentOutput = output_HQ;
                    }
                    
                    else
                    {
                        currentOutput = output;
                    }
                    
                    int stationMask_iMuon = 0;
                    
                    for(int iDTTP = 0; iDTTP < input->v_ltTwinMuxOut_bx->size(); iDTTP++)
                    {
                        int stNum_iDTTP = input->v_ltTwinMuxOut_station->at(iDTTP);
                        int whNum_iDTTP = input->v_ltTwinMuxOut_wheel->at(iDTTP);
                        int scNum_iDTTP = input->v_ltTwinMuxOut_sector->at(iDTTP);
                        
                        // Exclude wheels +-2 of MB1
                        // They are already supported by the CSC
                       /* if(abs(whNum_iDTTP) == 2)
                        {
                            continue;
                        }*/
                        
                        //double pT_iDTTP = Common::getPtFromPhiB((int) input->v_ltTwinMuxOut_phiB->at(iDTTP), &v_phiB, &v_pT);
                        //
                        //if(pT_iDTTP < MB1_pTcut)
                        //{
                        //    continue;
                        //}
                        
                        double phi_iDTTP = Common::globalPhiFromDTphi(input->v_ltTwinMuxOut_phi->at(iDTTP), scNum_iDTTP);
                        
                        int quality = input->v_ltTwinMuxOut_quality->at(iDTTP);
                        
                        bool isLQ = quality > 0 && quality < 4;
                        bool isHQ = quality > 3 && quality < 7;
                        
                        // Check DTTP quality
                        if(!isLQ && !isHQ)
                        {
                            continue;
                        }
                        
                        //if(!isHQ)
                        //{
                        //    continue;
                        //}
                        
                        if(iQua == 0 && isHQ)
                        {
                            continue;
                        }
                        
                        else if(iQua == 1 && isLQ)
                        {
                            continue;
                        }
                        
                        
                        double deltaPhi = phi_iMuon - phi_iDTTP;
                        deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                        deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                        
                        if(fabs(deltaPhi) < 0.1)
                        {
                            currentOutput->h1_test1->Fill((abs(iEta_iMuon)-1)*10 + stNum_iDTTP);
                            currentOutput->h1_test1a->Fill((abs(iEta_iMuon)-1)*2*6 + (subIeta_iMuon-1)*6 + stNum_iDTTP);
                            
                            stationMask_iMuon |= (1 << (stNum_iDTTP-1));
                        }
                    }
                    
                    currentOutput->h1_test2->Fill((abs(iEta_iMuon)-1)*25 + stationMask_iMuon);
                    currentOutput->h1_test2a->Fill((abs(iEta_iMuon)-1)*2*20 + (subIeta_iMuon-1)*20 + stationMask_iMuon);
                    
                    for(int iStation = 0; iStation < 4; iStation++)
                    {
                        if(!(stationMask_iMuon & (1<<iStation)))
                        {
                            currentOutput->h1_test3->Fill(iStation*10 + abs(iEta_iMuon));
                            currentOutput->h1_test3a->Fill(iStation*10 + abs(iEta_iMuon)*2 + subIeta_iMuon-2);
                        }
                    }
                }
            }
        }
        
        
        currentOutput = 0;
        
        // At least 1 reco-muon in the event
        // PROBABLY need to deactivate this for correct fake estimate
        if(!v_selectedMuon_pos.size())
        {
            printf("No reco-muon in the event. \n");
            continue;
        }
        
        
        // BMTF
        int nBMTF = input->v_bmtf_wheel->size();
        std::vector <bool> v_bmtf_isMuMatched(nBMTF, false);
        
        for(int iBMTF = 0; iBMTF < nBMTF; iBMTF++)
        {
            int selectedMu_BMTFmatched_index = -1;
            double deltaR_min = 9999;
            
            double pT_iBMTF = input->v_bmtf_pT->at(iBMTF);
            double eta_iBMTF = input->v_bmtf_eta->at(iBMTF);
            double phi_iBMTF = Common::bmtfGlobalPhiToCmsPhi(input->v_bmtf_globalPhi->at(iBMTF));
            
            // BMTF pT, eta cut
            if(pT_iBMTF < BMTF_pTcut || fabs(eta_iBMTF) > BMTF_etaCut)
            {
                continue;
            }
            
            for(int iMuon = 0; iMuon < v_selectedMuon_pos.size(); iMuon++)
            {
                int muon_pos = v_selectedMuon_pos.at(iMuon);
                
                if(muon_pos < 0)
                {
                    continue;
                }
                
                double deltaEta = eta_iBMTF - input->v_Mu_eta->at(muon_pos);
                
                double deltaPhi = phi_iBMTF - input->v_Mu_phi->at(muon_pos);
                deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                
                double deltaR = sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
                
                if(deltaR < deltaR_min)
                {
                    deltaR_min = deltaR;
                    selectedMu_BMTFmatched_index = iMuon;
                }
            }
            
            output->h1_BMTF_mu_deltaR->Fill(deltaR_min);
            
            // Fill BMTF quantities if mu-matched
            if(deltaR_min < muBMTF_deltaRcut)
            {
                v_bmtf_isMuMatched.at(iBMTF) = true;
                
                output->h1_BMTF_mu_deltaPt->Fill(pT_iBMTF - v_selectedMuon_pT.at(selectedMu_BMTFmatched_index));
                
                output->h1_BMTF_muMatched_pT->Fill(v_selectedMuon_pT.at(selectedMu_BMTFmatched_index));//pT_iBMTF);
                output->h1_BMTF_muMatched_eta->Fill(v_selectedMuon_eta.at(selectedMu_BMTFmatched_index));//eta_iBMTF);
                output->h1_BMTF_muMatched_phi->Fill(v_selectedMuon_phi.at(selectedMu_BMTFmatched_index));//phi_iBMTF);
                
                output->h1_BMTF_muMatched_deltaEta->Fill(eta_iBMTF - v_selectedMuon_eta.at(selectedMu_BMTFmatched_index));
                
                double deltaPhi = phi_iBMTF - v_selectedMuon_phi.at(selectedMu_BMTFmatched_index);
                deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                output->h1_BMTF_muMatched_deltaPhi->Fill(deltaPhi);
                
                output->h2_BMTF_muMatched_pT_vs_eta->Fill(v_selectedMuon_eta.at(selectedMu_BMTFmatched_index), v_selectedMuon_pT.at(selectedMu_BMTFmatched_index));
                output->h2_BMTF_muMatched_pT_vs_phi->Fill(v_selectedMuon_phi.at(selectedMu_BMTFmatched_index), v_selectedMuon_pT.at(selectedMu_BMTFmatched_index));
                output->h2_BMTF_muMatched_eta_vs_phi->Fill(v_selectedMuon_phi.at(selectedMu_BMTFmatched_index), v_selectedMuon_eta.at(selectedMu_BMTFmatched_index));
                
                if(selectedMu_BMTFmatched_index >= 0)
                {
                    v_selectedMuon_pos.at(selectedMu_BMTFmatched_index) = -1;
                }
            }
            
            // Fill BMTF quantities if not mu-matched
            else
            {
                output->h1_BMTF_muNotMatched_pT->Fill(pT_iBMTF);
                output->h1_BMTF_muNotMatched_eta->Fill(eta_iBMTF);
                output->h1_BMTF_muNotMatched_phi->Fill(phi_iBMTF);
                
                output->h2_BMTF_muNotMatched_pT_vs_eta->Fill(eta_iBMTF, pT_iBMTF);
                output->h2_BMTF_muNotMatched_pT_vs_phi->Fill(phi_iBMTF, pT_iBMTF);
                output->h2_BMTF_muNotMatched_eta_vs_phi->Fill(phi_iBMTF, eta_iBMTF);
            }
        }
        
        
        std::vector <int> v_HOTP_isUsed(input->v_hoTPdigi_bits->size(), 0);
        std::vector <int> v_DTTP_isUsed(input->v_ltTwinMuxOut_bx->size(), 0);
        std::vector <int> v_BMTF_isUsed(nBMTF, 0);
        
        
        // MB1
        int nDTTP = input->v_ltTwinMuxOut_bx->size();
        
        for(int iDTTP = 0; iDTTP < nDTTP; iDTTP++)
        {
            int stNum_iDTTP = input->v_ltTwinMuxOut_station->at(iDTTP);
            int whNum_iDTTP = input->v_ltTwinMuxOut_wheel->at(iDTTP);
            int scNum_iDTTP = input->v_ltTwinMuxOut_sector->at(iDTTP);
            
            int bx_iDTTP = input->v_ltTwinMuxOut_bx->at(iDTTP);
            
            if(bx_iDTTP != 0)
            {
                continue;
            }
            
            // MB1 only
            if(stNum_iDTTP != 1)
            {
                continue;
            }
            
            // Exclude wheels +-2 of MB1
            // They are already supported by the CSC
            if(abs(whNum_iDTTP) == 2)
            {
                continue;
            }
            
            double pT_iDTTP = Common::getPtFromPhiB((int) input->v_ltTwinMuxOut_phiB->at(iDTTP), &v_phiB, &v_pT);
            
            if(pT_iDTTP < MB1_pTcut)
            {
                continue;
            }
            
            double phi_iDTTP = Common::globalPhiFromDTphi(input->v_ltTwinMuxOut_phi->at(iDTTP), scNum_iDTTP);
            int iPhi_iDTTP = input->v_ltTwinMuxOut_iPhi->at(iDTTP);
            
            std::string quality_str = "";
            
            int quality = input->v_ltTwinMuxOut_quality->at(iDTTP);
            
            bool isLQ = quality > 0 && quality < 4;
            bool isHQ = quality > 3 && quality < 7;
            
            // Check DTTP quality
            if(!isLQ && !isHQ)
            {
                continue;
            }
            
            //if(!isHQ)
            //{
            //    continue;
            //}
            
            // Select the histograms to write to (LQ or HQ)
            if(isLQ)
            {
                quality_str = "LQ";
                currentOutput = output_LQ;
            }
            
            else if(isHQ)
            {
                quality_str = "HQ";
                currentOutput = output_HQ;
            }
            
            //std::vector <int> v_bestDTsegment_index = a_bestDTsegment_index[whNum+2][stNum-1][scNum-1];
            //
            //if(!v_bestDTsegment_index.size())
            //{
            //    continue;
            //}
            
            //double bestDTsegment_eta = input->v_dtsegm4D_eta->at(bestDTsegment_index);
            //double bestDTsegment_phi = input->v_dtsegm4D_phi->at(bestDTsegment_index);
            
            
            // Check if isolated (isolated = unused by BMTF)
            bool isIsolatedMB1 = true;
            double MB1BMTF_deltaPhi_min = 9999;
            int usedBMTF_index = -1;
            for(int iBMTF = 0; iBMTF < nBMTF; iBMTF++)
            {
                if(v_BMTF_isUsed.at(iBMTF))
                {
                    continue;
                }
                
                // For each track, there are 4 entries (MB1/2/3/4)
                // To get whether the track used MB1, check entries at 0, 4, 8...
                // To get whether the track used MB2, check entries at 1, 5, 9...
                // To get whether the track used MB3, check entries at 2, 6, 10...
                // To get whether the track used MB4, check entries at 3, 7, 11...
                // For MB1, the entry is 1 for HQ, 2 for LQ, and 3 for unused
                int bmtf_trAddress = input->v_bmtf_trAddress->at(4*iBMTF);
                
                double phi_iBMTF = Common::bmtfGlobalPhiToCmsPhi(input->v_bmtf_globalPhi->at(iBMTF));
                
                // Check if BMTF has used MB1 and match quality (?), wheel (?), sector
                if(//((isLQ && bmtf_trAddress == 2) || (isHQ && bmtf_trAddress == 1)) 
                    //&& whNum_iDTTP == input->v_bmtf_wheel->at(iBMTF)
                    (bmtf_trAddress == 1 || bmtf_trAddress == 2)
                    && scNum_iDTTP-1 == input->v_bmtf_processor->at(iBMTF))
                {
                    isIsolatedMB1 = false;
                    
                    double deltaPhi = phi_iBMTF - phi_iDTTP;
                    deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                    deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                    
                    //currentOutput->h1_MB1_BMTF_deltaPhi->Fill(deltaPhi);
                    //
                    //break;
                    
                    if(fabs(deltaPhi) < fabs(MB1BMTF_deltaPhi_min))
                    {
                        MB1BMTF_deltaPhi_min = deltaPhi;
                        usedBMTF_index = iBMTF;
                    }
                }
            }
            
            if(usedBMTF_index >= 0)
            {
                v_BMTF_isUsed.at(usedBMTF_index) = 1;
                currentOutput->h1_MB1_BMTF_deltaPhi->Fill(MB1BMTF_deltaPhi_min);
            }
            
            
            // Old iso-type
            bool isIsolatedMB1_old = true;
            double ijDTTP_deltaPhi_min = 9999;
            int usedDTTP_index = -1;
            for(int jDTTP = 0; jDTTP < nDTTP; jDTTP++)
            {
                int stNum_jDTTP = input->v_ltTwinMuxOut_station->at(jDTTP);
                int whNum_jDTTP = input->v_ltTwinMuxOut_wheel->at(jDTTP);
                int scNum_jDTTP = input->v_ltTwinMuxOut_sector->at(jDTTP);
                
                // MB2/3/4
                if(stNum_jDTTP == 1)
                {
                    continue;
                }
                
                if(v_DTTP_isUsed.at(jDTTP))
                {
                    continue;
                }
                
                double phi_jDTTP = Common::globalPhiFromDTphi(input->v_ltTwinMuxOut_phi->at(jDTTP), scNum_jDTTP);
                
                double deltaPhi = phi_iDTTP - phi_jDTTP;
                deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                
                if(fabs(deltaPhi) < 0.4)// && scNum_jDTTP == scNum_iDTTP)// && whNum_jDTTP == whNum_iDTTP)
                {
                    isIsolatedMB1_old = false;
                    
                    if(fabs(deltaPhi) < fabs(ijDTTP_deltaPhi_min))
                    {
                        ijDTTP_deltaPhi_min = deltaPhi;
                        usedDTTP_index = jDTTP;
                    }
                }
            }
            
            if(usedDTTP_index >= 0)
            {
                v_DTTP_isUsed.at(usedDTTP_index) = 1;
            }
            
            if(isIsolatedMB1_old)
            {
                currentOutput->h1_MB1_isoType->Fill(-2);
            }
            
            if(isIsolatedMB1_old && !isIsolatedMB1)
            {
                currentOutput->h1_MB1_isoType->Fill(-1);
            }
            
            if(isIsolatedMB1_old && isIsolatedMB1)
            {
                currentOutput->h1_MB1_isoType->Fill(0);
            }
            
            if(!isIsolatedMB1_old && isIsolatedMB1)
            {
                currentOutput->h1_MB1_isoType->Fill(1);
            }
            
            if(isIsolatedMB1)
            {
                currentOutput->h1_MB1_isoType->Fill(2);
            }
            
            // Next portion only for isolated MB1
            if(!isIsolatedMB1)
            {
                continue;
            }
            
            
            printf("isoMB1 found: DT index %d, pT %f, phi %f \n", iDTTP, pT_iDTTP, phi_iDTTP);
            
            // HO support
            bool isHOTPmatched = false;
            
            int nearestHOTP_index = -1;
            int MB1HO_deltaIphi_min = 9999;
            
            int nHOTP = input->v_hoTPdigi_bits->size();
            
            for(int iHOTP = 0; iHOTP < nHOTP; iHOTP++)
            {
                // HOTP at SOI only
                if(input->v_hoTPdigi_bits->at(iHOTP) != HOTP_bits_SOI)
                {
                    continue;
                }
                
                if(v_HOTP_isUsed.at(iHOTP))
                {
                    continue;
                }
                
                int iPhi_iHOTP = input->v_hoTPdigi_iPhi->at(iHOTP);
                int iEta_iHOTP = input->v_hoTPdigi_iEta->at(iHOTP);
                
                //if(abs(input->v_hoTPdigi_iEta->at(iHOTP)) != 3)
                //{
                //    continue;
                //}
                
                //if((iPhi_iHOTP+1)%6 == 0 || (iPhi_iHOTP+2)%6 == 0)
                //{
                //    continue;
                //}
                
                int whNum_iHOTP = Common::getWheelFromIeta(input->v_hoTPdigi_iEta->at(iHOTP));
                int scNum_iHOTP = Common::getSectorFromIphi(input->v_hoTPdigi_iPhi->at(iHOTP));
                
                
                int deltaIphi = iPhi_iDTTP - iPhi_iHOTP;
                deltaIphi = (deltaIphi > 36)? (deltaIphi-72): deltaIphi;
                deltaIphi = (deltaIphi < -36)? (deltaIphi+72): deltaIphi;
                
                //int deltaIeta = etaToIeta(bestDTsegment_eta) - input->v_hoTPdigi_iEta->at(iHOTP);
                
                
                // MB1-HO matching
                if(abs(deltaIphi) <= MB1_HO_deltaIphiCut
                    && scNum_iDTTP == scNum_iHOTP
                    && whNum_iDTTP == whNum_iHOTP)// && abs(deltaIeta) <= 1)
                {
                    isHOTPmatched = true;
                    
                    // Store nearest HOTP
                    if(abs(deltaIphi) < abs(MB1HO_deltaIphi_min))
                    {
                        MB1HO_deltaIphi_min = deltaIphi;
                        
                        nearestHOTP_index = iHOTP;
                    }
                }
            }
            
            
            bool MB1HO_isMuMatched = false;
            
            if(isHOTPmatched)
            {
                printf("isoMB1+HO found: HO index %d \n", nearestHOTP_index);
                
                v_HOTP_isUsed.at(nearestHOTP_index) = 1;
                currentOutput->h1_isoMB1HO_deltaIphi->Fill(MB1HO_deltaIphi_min);
                
                int selectedMu_MB1HOmatched_index = -1;
                double deltaR_min = 9999;
                double nearestHOTP_eta = Common::HOiEtaToEta(input->v_hoTPdigi_iEta->at(nearestHOTP_index));
                
                for(int iMuon = 0; iMuon < v_selectedMuon_pos.size(); iMuon++)
                {
                    int muon_pos = v_selectedMuon_pos.at(iMuon);
                    
                    if(muon_pos < 0)
                    {
                        continue;
                    }
                    
                    double deltaEta = nearestHOTP_eta - input->v_Mu_eta->at(muon_pos);
                    double deltaPhi = phi_iDTTP - input->v_Mu_phi->at(muon_pos);
                    double deltaR = sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
                    
                    //if(fabs(deltaEta) < muMB1_deltaEtaCut && fabs(deltaPhi) < muMB1_deltaPhiCut)
                    
                    if(deltaR < deltaR_min)
                    {
                        deltaR_min = deltaR;
                        selectedMu_MB1HOmatched_index = iMuon;
                        
                    }
                }
                
                
                // Fill isoMB1+HO quantities if mu-matched
                if(deltaR_min < muMB1_deltaRcut)
                {
                    printf("isoMB1+HO IS matched to muon. \n");
                    
                    MB1HO_isMuMatched = true;
                    
                    if(selectedMu_MB1HOmatched_index >= 0)
                    {
                        v_selectedMuon_pos.at(selectedMu_MB1HOmatched_index) = -1;
                    }
                    
                    currentOutput->h1_isoMB1HO_mu_deltaPt->Fill(pT_iDTTP - v_selectedMuon_pT.at(selectedMu_MB1HOmatched_index));
                    
                    currentOutput->h1_isoMB1HO_muMatched_pT->Fill(v_selectedMuon_pT.at(selectedMu_MB1HOmatched_index));//pT_iDTTP);
                    currentOutput->h1_isoMB1HO_muMatched_eta->Fill(v_selectedMuon_eta.at(selectedMu_MB1HOmatched_index));//nearestHOTP_eta);
                    currentOutput->h1_isoMB1HO_muMatched_phi->Fill(v_selectedMuon_phi.at(selectedMu_MB1HOmatched_index));//phi_iDTTP);
                    
                    currentOutput->h2_isoMB1HO_muMatched_pT_vs_eta->Fill(v_selectedMuon_eta.at(selectedMu_MB1HOmatched_index), v_selectedMuon_pT.at(selectedMu_MB1HOmatched_index));
                    currentOutput->h2_isoMB1HO_muMatched_pT_vs_phi->Fill(v_selectedMuon_phi.at(selectedMu_MB1HOmatched_index), v_selectedMuon_pT.at(selectedMu_MB1HOmatched_index));
                    currentOutput->h2_isoMB1HO_muMatched_eta_vs_phi->Fill(v_selectedMuon_phi.at(selectedMu_MB1HOmatched_index), v_selectedMuon_eta.at(selectedMu_MB1HOmatched_index));
                }
                // Fill isoMB1+HO quantities if not mu-matched
                else
                {
                    printf("isoMB1+HO is NOT matched to muon. \n");
                    
                    currentOutput->h1_isoMB1HO_muNotMatched_pT->Fill(pT_iDTTP);
                    currentOutput->h1_isoMB1HO_muNotMatched_eta->Fill(nearestHOTP_eta);
                    currentOutput->h1_isoMB1HO_muNotMatched_phi->Fill(phi_iDTTP);
                    
                    currentOutput->h2_isoMB1HO_muNotMatched_pT_vs_eta->Fill(nearestHOTP_eta, pT_iDTTP);
                    currentOutput->h2_isoMB1HO_muNotMatched_pT_vs_phi->Fill(phi_iDTTP, pT_iDTTP);
                    currentOutput->h2_isoMB1HO_muNotMatched_eta_vs_phi->Fill(phi_iDTTP, nearestHOTP_eta);
                }
            }
        }
    }
}
