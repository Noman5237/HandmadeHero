
pushd W:\HandmadeHero\build
gcc -g ..\src\win32.c -o win32.exe -luser32
popd

Write-Host "Build Finished." -ForegroundColor DarkCyan

