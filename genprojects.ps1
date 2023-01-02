function pause ($message)
{
    if ($psISE)
    {
        Add-Type -AssemblyName System.Windows.Forms
        [System.Windows.Forms.MessageBox]::Show("$message")
    }
    else
    {
        Write-Host "$message" -ForegroundColor Yellow
        $x = $host.ui.RawUI.ReadKey("NoEcho,IncludeKeyDown")
    }
}

Write-Host "Executing premake to generate projects...`n"
global-thirdpartylibs\premake\premake5.exe vs2022
pause "`nPress any key to exit..."