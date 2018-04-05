@echo off
echo CUS1
robonav.exe file.txt -u
echo DFS
robonav.exe file.txt -d
echo BFS
robonav.exe file.txt -b
echo CUS2
robonav.exe file.txt -i
echo GBFS
robonav.exe file.txt -g
echo AS
robonav.exe file.txt -a
echo.
echo.
echo.
pause