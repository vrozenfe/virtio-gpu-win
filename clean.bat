@echo off
for %%D in (VirtIO viogpu) do (
  pushd %%D
  if exist cleanall.bat (
    call cleanall.bat
  ) else (
    call clean.bat
  )
  popd
)

if exist buildfre_*.log del buildfre_*.log
if exist buildchk_*.log del buildchk_*.log
