import FWCore.ParameterSet.Config as cms

HLTrigResultsDumper = cms.EDAnalyzer("HLTrigResultsDumper",
    HLTriggerResults = cms.InputTag("TriggerResults","","HLT"),
    HLTPaths = cms.vstring('HLT_Mu3', 'HLT_Mu5', 'HLT_Mu9')   # provide list of HLT paths (or patterns) you want
)

# ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 


