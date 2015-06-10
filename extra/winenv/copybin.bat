@if EXIST ..\SDLtestVS (
		@xcopy bin ..\SDLtestVS /S /Y /Q
		@echo Done.
	) else (
		@echo.
		@echo Could not find
)