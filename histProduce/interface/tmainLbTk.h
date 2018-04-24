#ifndef __tMainLbTk_h__
#define __tMainLbTk_h__
#include "histProduce/histProduce/interface/tmain.h"

class treeMain_LbTk : public treeMain
{
public:
    treeMain_LbTk ( TFileDirectory* d);
    virtual void Process( fwlite::Event* ev ) override;
    virtual void Clear() override;

    // automatically called by constructor.
    virtual void RegTree() override;
    virtual void GetByLabel( fwlite::Event* ev ) override;

    // used for final analysis
    void setBranchAddress( TTree* inputTree );
private:
    const double kaonMass, protonMass, pionMass;
    void getByLabel_BS( fwlite::Event* ev );
    fwlite::Handle< reco::BeamSpot > beamSpotHandle;
    enum dataVarD
    {
        lbtkMass, lbtkFlightDistance2d, lbtkFlightDistanceSig, lbtkVtxprob,
        lbtkMom, lbtkPt,
        tktkPt, tktkMom,
        fake_Lam0Mass, fake_KstarMass, fake_PhiMass, fake_KshortMass,
        fake_LbL0Mass, fake_BdMass   , fake_BsMass, fake_mumupipiMass,
        ptkPt, ptkMom, ptkDEDX_Harmonic, ptkDEDX_pixelHrm, ptkIPt, ptkIPtErr,
        ntkPt, ntkMom, ntkDEDX_Harmonic, ntkDEDX_pixelHrm, ntkIPt, ntkIPtErr,
        totNumD
    };
    enum dataVarI
    {
        totNumI
    };
    // double data to store variables
    double dataD[totNumD];
    // int data to store variables
    int dataI[totNumI];
};
#endif
