# ifndef Common_H
# define Common_H


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


namespace Common
{
    void parseCSV_pTlut(std::string fileName, std::vector <int> *v_phiB, std::vector <double> *v_pT)
    {
        std::ifstream data(fileName);
        std::string line;
        std::vector <std::vector <std::string> > parsedCsv;
        
        while(std::getline(data, line))
        {
            // Skip comments (start with #)
            if(line.at(0) == '#')
            {
                continue;
            }
            
            std::stringstream lineStream(line);
            std::string cell;
            std::vector <std::string> parsedRow;
            
            while(std::getline(lineStream, cell, ','))
            {
                parsedRow.push_back(cell);
            }
            
            parsedCsv.push_back(parsedRow);
            
            v_phiB->push_back(std::stoi(parsedRow.at(0)));
            v_pT->push_back(std::stof(parsedRow.at(1)) * 0.5);
            
            //printf("phiB %d, pT %f \n", v_phiB[v_phiB.size()-1], v_pT[v_pT.size()-1]);
        }
    }
    
    
    double getPtFromPhiB(int phiB, std::vector <int> *v_phiB, std::vector <double> *v_pT)
    {
        for(int iPhiB = 0; iPhiB < v_phiB->size(); iPhiB++)
        {
            if(v_phiB->at(iPhiB) == phiB)
            {
                return v_pT->at(iPhiB);
            }
        }
        
        return -1;
    }
    
    
    double globalPhiFromDTphi(double phi, int secNum)
    {
        // secNum must be [1, 12]
        double globalPhi = phi / 4096.0;
        globalPhi += M_PI / 6 * (secNum - 1);
        
        if(globalPhi > M_PI)
        {
            globalPhi -= M_PI * 2;
        }
        
        return globalPhi;
    }
    
    
    double bmtfGlobalPhiToCmsPhi(int phi)
    {
        // [0, 576] to [-pi, pi]
        
        double cmsPhi = 2*M_PI*phi/576;
        
        if(cmsPhi > M_PI)
        {
            cmsPhi -= M_PI * 2;
        }
        
        return cmsPhi;
    }
    
    
    int getSectorFromIphi(int iPhi)
    {
        // iPhi must be [1-72]
        // Returns sector [1-12]
        
        int secNum = (iPhi-1+2) % 72;
        
        secNum = (int) (secNum/6.0 + 1);
        
        return secNum;
    }
    
    
    int getWheelFromIeta(int iEta)
    {
        // Returns [-2, 2]
        
        if(iEta < -10)
        {
            return -2;
        }
        
        if(iEta < -4 && iEta > -11)
        {
            return -1;
        }
        
        if(iEta < 5 && iEta > -5)
        {
            return 0;
        }
        
        if(iEta > 4 && iEta < 11)
        {
            return 1;
        }
        
        if(iEta > 10)
        {
            return 2;
        }
        
        return -99;
    }
    
    
    double HOiEtaToEta(int iEta)
    {
        // Eta segmentation in HO is 2*pi/72 = ~0.087
        double dEta = 2*M_PI/72;
        
        double sign = (iEta < 0) ? -1: 1;
        
        // Take the mean eta
        double eta = (fabs(iEta)-1 + fabs(iEta)) / 2 * dEta;
        eta *= sign;
        
        return eta;
    }
}


# endif
