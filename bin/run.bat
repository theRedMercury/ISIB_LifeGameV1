@ECHO OFF
echo ==================================
echo  ISIB WATCHDOG CONTROL LIFE GAME
echo.
echo  Created by Masson Nicolas
echo        2015-2016
echo ==================================

start ISIB_LifeGameV1.exe
SET var=0

:loop
FOR /F "tokens=2" %%b IN ('TASKLIST /FI "IMAGENAME eq ISIB_LifeGameV1.exe" /FI "STATUS eq NOT RESPONDING" ') do (SET var=%%b)

if  not  "%var%" ==  "No" (
	TASKKILL /F /PID %var%  /T > nul
	timeout 1 > nul
	start ISIB_LifeGameV1.exe
	SET var=0
)

timeout 5 > nul
goto loop


