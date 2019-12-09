
pushd W:\HandmadeHero\build
gcc -g -std=c99 -Wall -Wextra ..\src\win32.c -o win32.exe -luser32 -lgdi32
popd

Write-Host "Build Finished." 

