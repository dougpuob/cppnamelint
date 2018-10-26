 
Function Exec-Clang-Format-File($filepath)
{
    if (Test-Path $filepath) {
        Start-Process  -FilePath "clang-format.exe" -WindowStyle Hidden -ArgumentList "-style=file", "-i", $filepath
    }
}


Function Exec-Clang-Format-Dir($folderpath)
{
    if ([System.IO.Directory]::Exists($folderpath)) 
    {
        Get-ChildItem  $folderpath -Verbose | ForEach-Object { 
            if ($_.FullName.EndsWith(".c",   "CurrentCultureIgnoreCase") -or
                $_.FullName.EndsWith(".h",   "CurrentCultureIgnoreCase") -or
                $_.FullName.EndsWith(".cc",  "CurrentCultureIgnoreCase") -or
                $_.FullName.EndsWith(".cpp", "CurrentCultureIgnoreCase"))
            {
                ECHO $_.FullName 
                Exec-Clang-Format-File $_.FullName 
            }
        }    
    }
}


echo $Args.Length

# If this script launchs by Right-Click on mouse with PowerShell v5.1.14409.1005, 
# $Args.Length : 2
# $Args[0]     : "-Command"
# $Args[1]     : "if((Get-ExecutionPolicy ) -ne AllSigned) { Set-ExecutionPolicy -Scope Process Bypass }"
$CmdMode = ($Args.Length.Equals(0)) -or
           ($Args.Length.Equals(2)  -and $Args[1].Contains("Get-ExecutionPolicy"))

if ($CmdMode) {
    $path = Resolve-Path -Path ..\Source     
} else {
    $path = Resolve-Path -Path $Args[0]
}

ECHO ("PATH   = " + $path)
Exec-Clang-Format-Dir $path
