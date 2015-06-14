copy /y nul hints0.txt
cd src
for /R %%i in (*.h) do (
	copy ..\hints0.txt + "%%i" ..\hints0.txt
)
cd ..\
type hints0.txt | findstr /v # > hints.txt
del hints0.txt
cls
@echo Done.