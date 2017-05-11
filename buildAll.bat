@echo off
for %%D in (VirtIO viogpu) do (
  pushd %%D
  call buildAll.bat
  if errorlevel 1 goto :eof
  popd
)
