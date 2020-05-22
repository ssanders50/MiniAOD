# MiniAOD\
cmsrel cmssw_10_3_3_patch1\
cd CMSSW_10_3_3_patch1/src\
cmsenv\
git cms-merge-topic -u CmsHI:hiMiniAOD_103X\
\
At this point, remove all .git directories from CMSSW.  This should allow the relevant software to be committed to github.\

