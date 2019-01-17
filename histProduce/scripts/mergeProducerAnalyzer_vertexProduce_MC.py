#!/usr/bin/env cmsRun
import FWCore.ParameterSet.Config as cms

process = cms.Process("myVertexingProcedure")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")


process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)

process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring(
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058.20.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058.21.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058.22.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058.23.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058.24.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058.25.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058.26.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058.27.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058.28.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058.29.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_00.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_01.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_02.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_03.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_04.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_05.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_06.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_07.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_08.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_09.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_10.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_11.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_12.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_13.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_14.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_15.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_16.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_17.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_18.root",
"file:///home/ltsai/Data/mcStep3_LbTJPsipK_13TeV_withoutPileUp_180524/BPH-RunIISpring16DR80-00058_19.root",
),

        duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_2016LegacyRepro_v3', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_ReReco_EOY17_v1', '')



# preselect pat muon and pat tracks
process.load('vertexProducer.PreselectFilter.FilterConf9_cfi')


# # remove MC dependence
# from PhysicsTools.PatAlgos.tools.coreTools import *
# removeMCMatching(process, names=['All'], outputModules=[] )

# load EDproducer from my part. vertexing jpsi, 2tks and finally combine them to 4 tracks
process.load('vertexProducer.vertexProducer.tktkVertexingProducer_cfi')
process.load('vertexProducer.vertexProducer.mumuVertexingProducer_cfi')
process.load('vertexProducer.vertexProducer.fourTracksFromVCCProducer_cfi')

# define for producer out
process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('vertexProducer_BdRemoved.root'),
    outputCommands = cms.untracked.vstring(
        "drop *",
        "keep *_mumuVertexingProducer_*_myVertexingProcedure",
        "keep *_tktkVertexingProducer_*_myVertexingProcedure",
        "keep *_fourTracksFromVCCProducer_*_myVertexingProcedure",
        "keep *_generalV0Candidates_*_RECO",
        "keep *_offlineBeamSpot_*_RECO",
        "keep *_offlinePrimaryVertices_*_RECO",
        "keep *_genParticles__HLT",
        "keep *_TriggerResults__HLT",
    ),
    SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('myfilterpath') )
)


# used for EDAnalyzer output 
# cms.outputModules is disabled for delete the output of EDProducer
process.TFileService = cms.Service('TFileService',
  fileName = cms.string('tree_VertexProducer.root'),
  closeFileFast = cms.untracked.bool(True)
)
process.VertexCompCandAnalyzer = cms.EDAnalyzer('VertexCompCandAnalyzer',
    pL0BCandsLabel = cms.string("fourTracksFromVCCProducer:pL0B:myVertexingProcedure"),
    nL0BCandsLabel = cms.string("fourTracksFromVCCProducer:nL0B:myVertexingProcedure"),
    LbL0CandsLabel = cms.string("fourTracksFromVCCProducer:LbL0:myVertexingProcedure"),
    LbLoCandsLabel = cms.string("fourTracksFromVCCProducer:LbLo:myVertexingProcedure"),
    HLTRecordLabel = cms.string("TriggerResults::HLT"),
    MCReserveLabel = cms.string("genParticles::HLT"),
      bsPointLabel = cms.string("offlineBeamSpot::RECO")
)


process.myfilterpath = cms.Path(

    # for CMSSW9
      process.myMuonsSequence
    * process.myTrackSequence

    # for CMSSW8
    # * process.selectedMuons
    # * process.selectedTracks
    * process.tktkVertexingProducer
    * process.mumuVertexingProducer
    * process.fourTracksFromVCCProducer

    * process.VertexCompCandAnalyzer
)

process.e = cms.EndPath(process.out)