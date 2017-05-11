@echo on

rmdir /S /Q Install

del /F *.log *.wrn *.err

cd viogpudo
call clean.bat
cd ..

