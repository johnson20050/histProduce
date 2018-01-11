#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include <TH1D.h>
#include <TROOT.h>
#include <TFile.h>
#include <TSystem.h>
#include <TNtupleD.h>
#include <TTree.h>

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h"
#include "histProduce/histProduce/interface/histoMAP.h"
#include "histProduce/histProduce/interface/generalCutList.h"
#include "histProduce/histProduce/interface/tMain.h"
//#include "histProduce/histProduce/interface/tMainLbL0.h"
//#include "histProduce/histProduce/interface/tMainLbTk.h"
//#include "histProduce/histProduce/interface/tMainBs.h"
//#include "histProduce/histProduce/interface/tMainfindParDiff.h"
//#include "histProduce/histProduce/interface/tMainfindIPdiff.h"
//#include "histProduce/histProduce/interface/tMainParPlot.h"
//#include "histProduce/histProduce/interface/tMainfindVtxprobDiff.h"
//#include "histProduce/histProduce/interface/tMainfindFDdiff.h"
//#include "histProduce/histProduce/interface/tMainfindTkTkFDdiff.h"
//#include "histProduce/histProduce/interface/tMainfindLam0FDdiff.h"
//#include "histProduce/histProduce/interface/tMainTkTk.h"
#include "histProduce/histProduce/interface/tMainLam0.h"
//#include "histProduce/histProduce/interface/tMainKshort.h"
//#include "histProduce/histProduce/interface/tMainPV.h"
//#include "histProduce/histProduce/interface/tMainGenInfo.h"
//#include "histProduce/histProduce/interface/tMainTkTkGenParticle.h"
#include "histProduce/histProduce/interface/tMainLam0GenParticle.h"
//#include "histProduce/histProduce/interface/tMainLbTkGenParticle.h"
//#include "histProduce/histProduce/interface/tMainLbL0GenParticle.h"
//#include "histProduce/histProduce/interface/tMainJPsiGenParticle.h"

// create histograms from CMSSW based data.
// use FWLIte to load data.
// this file just write down:
// 1. the argument you should or can input.
// 2. apply general cuts known.
// 3. loop the event.
//
// And the content in the loop is written in histProduce/histProduce/src/hMain????.cc
// every hMain??? decides what to do in each event.
// Normally, create a histogram and fill it. Save it into root file to be ploted.
//
// usage:
//     hCreate filelist=fileList
//
// create TTree.

// initialize static member
//std::vector<generalCutList*>* histMain::_cutLists = NULL;
//std::map<std::string, TH1D*> histMain::hMap;

int main(int argc, char* argv[])
{
    // ----------------------------------------------------------------------
    // First Part:
    //
    //  * enable the AutoLibraryLoader
    //  * book the histograms of interest
    //  * open the input files
    // ----------------------------------------------------------------------

    // load framework libraries
    gSystem->Load( "libFWCoreFWLite" );
    AutoLibraryLoader::enable();

    // check default path {{{
    std::string sysPath = std::string( getenv("CMSSW_BASE") );
    try
    {
        if ( sysPath == "" )
            throw "----- error, you need to setup CMSSW envirnment! -----";
    }
    catch ( const char* e )
    { printf( "%s", e ); }
    // check default path end }}}

    // parser setting {{{
    // initialize command line parser
    optutl::CommandLineParser parser ("Analyze FWLite Histograms");

    parser.addOption("testFile",optutl::CommandLineParser::kString,"test input file, recommend to use fileList_cfi.py to put files","");
    parser.addOption("fileList",optutl::CommandLineParser::kString,"input the python file records file list.","fileList");
    parser.addOption("configFile",optutl::CommandLineParser::kString,"the plot options recorded in python file","histogramPlotParameter");
    // set defaults for testFile is assigned
    parser.integerValue ("maxEvents"  ) = -1;
    parser.integerValue ("outputEvery") = -1;
    parser.stringValue  ("outputFile" ) = "histTestOutput.root";

    // parse arguments
    parser.parseArguments (argc, argv);

    // deal with python file path
    const std::string configFile = parser.stringValue("configFile");
    const std::string listFile   = parser.stringValue("fileList");
    const std::string dPath      = "/src/histProduce/histProduce/python/";
    const std::string confPython = sysPath+dPath+configFile+"_cfi.py";
    const std::string fOptPython = sysPath+dPath+listFile+"_cfi.py";
    // load IO option from python file. default is fileList_cfi.py
    const edm::ParameterSet& ioOption = edm::readPSetsFrom(fOptPython.c_str())->getParameter<edm::ParameterSet>("process");
    const edm::ParameterSet& runSetting = ioOption.getParameter<edm::ParameterSet>("runSetting");
    const edm::ParameterSet& inputFileNames = ioOption.getParameter<edm::ParameterSet>("inputFiles");
    const std::vector<std::string>& fileNames = inputFileNames.getParameter< std::vector<std::string> >("fileNames");
    int maxEvents_          = runSetting.getParameter<int>("maxEvents");
    unsigned outputEvery_   = runSetting.getParameter<unsigned>("outEvery");
    std::string outputFile_ = runSetting.getParameter<std::string>("outName");

    // load cut configuration from python file. default is histogramCutParameter_cfi.py
    //const edm::ParameterSet& cutOption = edm::readPSetsFrom(confPython.c_str())->getParameter<edm::ParameterSet>("process");
    //const std::vector<edm::ParameterSet>& runSetting_ = cutOption.getParameter< std::vector<edm::ParameterSet> >("cutSet");
    // parser setting end }}}

    // input files
    std::vector<std::string> inputFiles_;

    // if inputFile not set, use python file : fileList_cfi.py
    if ( parser.stringValue("testFile").empty() )
        inputFiles_ = fileNames;
    else
    {
        // only if testFile is set, parameters from parser valid
        inputFiles_.push_back( parser.stringValue("testFile") );
        outputFile_ = parser.stringValue("outputFile");
        maxEvents_ = parser.integerValue("maxEvents");
        outputEvery_ = parser.integerValue("outputEvery");
    }

    // book a root file to store data.
    fwlite::TFileService fs = fwlite::TFileService(outputFile_.c_str());
    TFileDirectory dir = fs.mkdir("lbSpecificDecay");


    using namespace myCut;
    // general cut applied
    std::vector<generalCutList*> cutLists;
    //cutLists.push_back( new           vtxprobCut(0.15,-99. ) );
    cutLists.push_back( new              massCut(5.0 ,  6.0) );
    cutLists.push_back( new            cosa2dCut(0.99      ) );
    cutLists.push_back( new                ptCut(15  ,-99. ) );
    cutLists.push_back( new flightDist2DSigmaCut( 2., -99. ) );
    treeMain::setCutList( &cutLists );

    // set main code.
    std::vector<treeMain*> mainCode;
    //mainCode.push_back( new treeMain_TkTk(&dir) );
    mainCode.push_back( new treeMain_Lam0(&dir) );
    //mainCode.push_back( new treeMain_Kshort(&dir) );
    //mainCode.push_back( new treeMain_LbTk(&dir) );
    //mainCode.push_back( new treeMain_LbL0(&dir) );
    //mainCode.push_back( new treeMain_Bs(&dir) );
    //mainCode.push_back( new treeMain_findParDiff(&dir) );
    //mainCode.push_back( new treeMain_findIPdiff(&dir) );
    //mainCode.push_back( new treeMain_findVtxprobDiff(&dir) );
    //mainCode.push_back( new treeMain_ParPlot(&dir) );
    //mainCode.push_back( new treeMain_findFlightDistanceDiff(&dir) );
    //mainCode.push_back( new treeMain_findTkTkFlightDistanceDiff(&dir) );
    //mainCode.push_back( new treeMain_findLam0FlightDistanceDiff(&dir) );
    //mainCode.push_back( new treeMain_PV(&dir) );
    //mainCode.push_back( new treeMain_GenInformation(&dir) );
    //mainCode.push_back( new treeMain_JPsiGenParticle(&dir) );
    mainCode.push_back( new treeMain_Lam0GenParticle(&dir) );
    //mainCode.push_back( new treeMain_TkTkGenParticle(&dir) );
    //mainCode.push_back( new treeMain_LbTkGenParticle(&dir) );
    //mainCode.push_back( new treeMain_LbL0GenParticle(&dir) );

    int ievt=0;
    for ( const auto& file : inputFiles_ )
    {
        bool terminateLoop = false;
        TFile* inFile = TFile::Open( ("file://"+file).c_str() );
        if( !inFile ) continue;
        // ----------------------------------------------------------------------
        // Second Part:
        //
        //  * loop the events in the input file
        //  * receive the collections of interest via fwlite::Handle
        //  * fill the histograms
        //  * after the loop close the input file
        // ----------------------------------------------------------------------
        fwlite::Event ev(inFile);
        for(ev.toBegin(); !ev.atEnd(); ++ev, ++ievt)
        {
	        //edm::EventBase const & event = ev;
	        // break loop if maximal number of events is reached
	        if(maxEvents_>0 ? ievt+1>maxEvents_ : false)
            { terminateLoop = true; break; }
	        // simple event counter
            if ( outputEvery_ > 0 )
                if ( ievt > 0 && ievt%outputEvery_ == 0 )
            {
                printf( "\r  processing event: %i", ievt );
                fflush( stdout );
            }


            for ( const auto& _main : mainCode )
                _main->Process( &ev );


        }
        inFile->Close();
        if ( terminateLoop ) break;
        // break loop if maximal number of events is reached:
        // this has to be done twice to stop the file loop as well
    }

    for ( auto& cut : cutLists )
        delete cut;
    for ( auto& _main : mainCode )
    {
        _main->Clear();
        delete _main;
    }

    printf("\n");
    return 0;
}