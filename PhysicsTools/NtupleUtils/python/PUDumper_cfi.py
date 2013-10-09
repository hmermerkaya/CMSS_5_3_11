import FWCore.ParameterSet.Config as cms

PUDumper = cms.EDAnalyzer(
    "PUDumper",
    MCPileupTag = cms.InputTag("addPileupInfo"),
    mcFlag = cms.untracked.bool (True)
    )

# ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
