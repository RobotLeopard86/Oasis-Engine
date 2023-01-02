Write-Host "Executing premake to generate projects...`n"
global-thirdpartylibs\premake\premake5.exe vs2022
Read-Host -Prompt "`nPress enter to exit..."